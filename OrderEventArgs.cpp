#include "OrderEventArgs.h"

#include "NotFinished.h"

// Part A. Write the constructor along with the Session 1 demo.

// Saves the order so every handler can read it.
// C++ has to copy the order into its field in the member initializer list
// (the ": order(order)" line), so that line is given.
OrderEventArgs::OrderEventArgs(const Order& order)
    : order(order)
{
    // TODO: Part A, demo. Delete this throw when the demo reaches it.

}

// Given. The order this event is about.
const Order& OrderEventArgs::GetOrder() const
{
    return order;
}
