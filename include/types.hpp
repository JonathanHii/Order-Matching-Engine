// types.hpp
#pragma once
#include <cstdint>

namespace engine
{
    // Scaling factor: 4 decimal places (e.g., 100 is stored as 1 000 000)
    constexpr int64_t PRICE_SCALAR = 10'000;

    using Price = int64_t;
    using Quantity = int64_t;
    using OrderID = uint64_t;

    enum class Side : uint8_t
    {
        Buy,
        Sell
    };

    // to convert double to fixed-point
    inline Price to_internal_price(double p)
    {
        return static_cast<Price>(p * PRICE_SCALAR);
    }
}