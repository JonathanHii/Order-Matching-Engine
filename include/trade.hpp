#pragma once
#include "types.hpp"

namespace engine {
    struct Trade {
        OrderID maker_id;
        OrderID taker_id;
        Price price;
        Quantity quantity;
    };
}