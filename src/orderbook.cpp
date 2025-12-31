#include <orderbook.hpp>
#include "types.hpp"

namespace engine
{
    void OrderBook::addOrder(const Order &order)
    {
        // two scenarios:
            // Matching if the order can be field immidelty
            // Resting if there is quantity left over.
            
        // Identify opposite side
            // If buy look in Asks map
            // If sell look in Bid map
            // will get list of order at each price

        // Iterate though opposite map
            // For a Buy order, the Ask Price must be <= Buy Price.
            // For a Sell order, the Bid Price must be >= Sell Price.
            // Get Match quantiy min of both orders
            // update quantities subtracting
            // Generate possible Trade and record.  will record later but 
            // clean up delete order if quantity 0 delete from list and ordermap
        
        // If order still has quantity > 0
            // Add order to its side of the book
            // Make sure to insert OrderId and iterator into map for O(1) cancellation
    }

    void OrderBook::cancelOrder(OrderID id)
    {
        // lookup from oredrmap getting the iteratro

        // Get the details and delete from list in that map
        // erase id from order_map
    }

}