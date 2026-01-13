#pragma once
#include <thread>
#include <atomic>
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

        void processLog()
        {
            while (running)
            {
                auto trade = queue.pop();
                if (trade)
                {
                    std::cout << "[TRADE] Maker:" << trade->maker_id
                              << " Taker:" << trade->taker_id
                              << " Price:" << trade->price
                              << " Qty:" << trade->quantity << "\n";
                }
                else
                {
                    // Yield to save CPU cycles when queue is empty
                    std::this_thread::yield();
                }
            }
            // Drain queue on shutdown
            while (auto trade = queue.pop())
            {
                std::cout << "[TRADE] Maker:" << trade->maker_id << " ... \n";
            }
        }

    public:
        // Initialize buffer size
        TradeLogger(size_t buffer_size = 1024)
            : queue(buffer_size), running(true)
        {
            loggerThread = std::thread(&TradeLogger::processLog, this);
        }

        ~TradeLogger()
        {
            running = false;
            if (loggerThread.joinable())
            {
                loggerThread.join();
            }
        }

        void logTrade(const Trade &trade)
        {
            // If queue is full, we busy-wait (spin).
            // In a real HFT engine, you might pre-allocate a larger buffer to avoid this.
            while (!queue.push(trade))
            {
                std::this_thread::yield();
            }
        }
    };

}