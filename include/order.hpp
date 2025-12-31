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
        Price price;
        Quantity quantity;
        Side side;

        Order(OrderID id, Price p, Quantity q, Side s)
            : id(id), price(p), quantity(q), side(s) {}
    };
}