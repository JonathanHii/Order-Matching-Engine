// order.hpp
#pragma once
#include "types.hpp"

namespace engine
{
    // make struct 64 bytes, starts it at multiple of 64 in memory
    // storing in a linked list so only one cache pull dont' want overlap
    struct alignas(64) Order
    {
        OrderID id;
        Side side;
        Price price;
        Quantity quantity;

        Order(OrderID id, Side s, Price p, Quantity q)
            : id(id), side(s), price(p), quantity(q) {}
    };
}