#include <orderbook.hpp>
#include "types.hpp"

namespace engine
{
    void OrderBook::addOrder(const Order &order)
    {
        Order remainingOrder = order;

        if (remainingOrder.side == Side::Buy) // look in Asks map
        {
            auto it = asks.begin();
            while (it != asks.end() && remainingOrder.quantity > 0 &&
                   it->first <= remainingOrder.price)
            {
                auto &orderList = it->second;
                auto listIt = orderList.begin();

                while (listIt != orderList.end() && remainingOrder.quantity > 0)
                {
                    auto matchQty = std::min(listIt->quantity, remainingOrder.quantity);
                    // execute Trade here

                    remainingOrder.quantity -= matchQty;
                    listIt->quantity -= matchQty;

                    if (listIt->quantity == 0)
                    {
                        order_map.erase(listIt->id);
                        listIt = orderList.erase(listIt);
                    }
                    else
                    {
                        ++listIt;
                    }
                }
                if (orderList.empty())
                {
                    it = asks.erase(it); // erase returns the next valid map iterator
                }
                else
                {
                    ++it;
                }
            }
        }
        else // Sell look in Bid map
        {
            auto it = bids.begin();
            while (it != bids.end() && remainingOrder.quantity > 0 &&
                   it->first >= remainingOrder.price)
            {
                auto &orderList = it->second;
                auto listIt = orderList.begin();

                while (listIt != orderList.end() && remainingOrder.quantity > 0)
                {
                    auto matchQty = std::min(listIt->quantity, remainingOrder.quantity);
                    // execute Trade here
                    remainingOrder.quantity -= matchQty;
                    listIt->quantity -= matchQty;

                    if (listIt->quantity == 0)
                    {
                        order_map.erase(listIt->id);
                        listIt = orderList.erase(listIt);
                    }
                    else
                    {
                        ++listIt;
                    }
                }
                if (orderList.empty())
                {
                    it = bids.erase(it); // erase returns the next valid map iterator
                }
                else
                {
                    ++it;
                }
            }
        }

        if (remainingOrder.quantity > 0)
        {
            if (remainingOrder.side == Side::Buy)
            {
                auto &list = bids[remainingOrder.price];
                list.push_back(remainingOrder);
                order_map[remainingOrder.id] = std::prev(list.end());
            }
            else
            {
                auto &list = asks[remainingOrder.price];
                list.push_back(remainingOrder);
                order_map[remainingOrder.id] = std::prev(list.end());
            }
        }
    }

    void OrderBook::cancelOrder(OrderID id)
    {
        // lookup from oredrmap getting the iteratro
        auto it = order_map.find(id);
        if (it == order_map.end())
            return;

        OrderIter listIt = it->second;
        Price price = listIt->price;
        Side side = listIt->side;

        if (side == Side::Buy)
        {
            bids[price].erase(listIt);
            if (bids[price].empty())
            {
                bids.erase(price);
            }
        }
        else
        {
            asks[price].erase(listIt);
            if (asks[price].empty())
            {
                asks.erase(price);
            }
        }

        order_map.erase(it);
    }

}