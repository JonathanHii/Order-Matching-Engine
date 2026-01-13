#pragma once
#include <thread>
#include <atomic>
#include <fstream> 
#include <string>
#include <iostream>
#include "lock_free_queue.hpp"
#include "trade.hpp"

namespace engine
{

    class TradeLogger
    {
    private:
        LockFreeQueue<Trade> queue;
        std::atomic<bool> running;
        std::thread loggerThread;
        std::ofstream file; // File stream handler

        void processLog()
        {
            while (running)
            {
                auto trade = queue.pop();
                if (trade)
                {
                    writeTrade(*trade);
                }
                else
                {
                    std::this_thread::yield();
                }
            }

            // Drain queue on shutdown to ensure no logs are lost
            while (auto trade = queue.pop())
            {
                writeTrade(*trade);
            }
        }

        // Helper to keep formatting consistent
        void writeTrade(const Trade &trade)
        {
            if (file.is_open())
            {
                file << "[TRADE] Maker:" << trade.maker_id
                     << " Taker:" << trade.taker_id
                     << " Price:" << trade.price
                     << " Qty:" << trade.quantity << "\n"; 
            }
        }

    public:
        // Update constructor to accept filename
        TradeLogger(const std::string &filename, size_t buffer_size = 1024)
            : queue(buffer_size), running(true)
        {
            file.open(filename, std::ios::out | std::ios::trunc);

            if (!file.is_open())
            {
                std::cerr << "[ERROR] Could not open log file: " << filename << "\n";
            }

            loggerThread = std::thread(&TradeLogger::processLog, this);
        }

        ~TradeLogger()
        {
            running = false;
            if (loggerThread.joinable())
            {
                loggerThread.join();
            }
            if (file.is_open())
            {
                file.close();
            }
        }

        void logTrade(const Trade &trade)
        {
            while (!queue.push(trade))
            {
                std::this_thread::yield();
            }
        }
    };
}