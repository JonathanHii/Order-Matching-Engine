#include <iostream>
#include "orderbook.hpp"

using namespace engine;

int main()
{
    OrderBook ob;

    std::cout << "Test Starting!" << std::endl;

    // Add resting Sell orders (Asks)
    std::cout << "Adding Sell Order 1: 10 units @ 105" << std::endl;
    ob.addOrder({1, Side::Sell, 105, 10});

    std::cout << "Adding Sell Order 2: 10 units @ 110" << std::endl;
    ob.addOrder({2, Side::Sell, 110, 10});

    // Add a Buy order (should rest)
    std::cout << "Adding Buy Order 3: 5 units @ 100" << std::endl;
    ob.addOrder({3, Side::Buy, 100, 5});

    // Add a Buy order that CROSSES the spread (Should match)
    // It wants 12 units at up to 106.
    // It should take all 10 units from Order 1 (at 105) and then rest 2 units at 106.
    std::cout << "Adding Buy Order 4: 12 units @ 106 (Matching Aggressor)" << std::endl;
    ob.addOrder({4, Side::Buy, 106, 12});

    // Test Cancellation
    // Let's cancel that resting Buy order at 100.
    std::cout << "Cancelling Order 3" << std::endl;
    ob.cancelOrder(3);

    // Test Partial Fill from the other side
    // Order 4 is resting 2 units at 106. Let's hit it with a small sell.
    std::cout << "Adding Sell Order 5: 1 unit @ 106" << std::endl;
    ob.addOrder({5, Side::Sell, 106, 1});

    std::cout << "Test Complete: No crashes detected" << std::endl;

    return 0;
}