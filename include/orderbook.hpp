#pragma once
#include <map>
#include <unordered_map>
#include <list>
#include <string> // Added
#include "order.hpp"
#include "trade_logger.hpp"
#include "trade.hpp"

namespace engine
{
    class OrderBook
    {
    private:
        TradeLogger logger;

        std::map<Price, std::list<Order>, std::greater<Price>> bids;
        std::map<Price, std::list<Order>> asks;

        using OrderIter = std::list<Order>::iterator;
        std::unordered_map<OrderID, OrderIter> order_map;

    public:
        // Initialize logger with a filename
        OrderBook(const std::string& filename = "trades.log") 
            : logger(filename, 4096) {} 

        void addOrder(const Order &order);
        void cancelOrder(OrderID id);
    };
}