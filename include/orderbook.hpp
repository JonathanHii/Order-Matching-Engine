// orderbook.hpp
#pragma once
#include <map>
#include <unordered_map>
#include <list>
#include "order.hpp"

namespace engine
{
    class OrderBook
    {
    private:
        // Bids: Descending (highest price first)
        // Asks: Ascending (lowest price first)
        std::map<Price, std::list<Order>, std::greater<Price>> bids;
        std::map<Price, std::list<Order>> asks;

        // The Lookup Table: Direct access to any order for O(1) cancellation
        // Maps OrderID -> Iterator to the order's position in the list
        using OrderIter = std::list<Order>::iterator;
        std::unordered_map<OrderID, OrderIter> order_map;

    public:
        void addOrder(const Order &order);
        void cancelOrder(OrderID id);
    };
}

/*
To get this compiling and functional, 
you need to implement addOrder in src/orderBook.cpp.
*/