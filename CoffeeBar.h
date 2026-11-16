#pragma once

#include <queue>
#include <string>
#include <vector>

#include "Event.h"
#include "Order.h"
#include "OrderEventArgs.h"

// CoffeeBar: the publisher. It takes orders, makes them in the order they
// arrived, and announces what happened. It never knows who is listening.
//
// Part A. Write Place and FinishNext along with the Session 1 demo.
// Raising AllCaughtUp inside FinishNext is Exercise 1.
class CoffeeBar
{
public:
    // Given. Raised after an order joins the line.
    Event<OrderEventArgs> OrderPlaced;

    // Given. Raised after an order leaves the line, ready for pickup.
    Event<OrderEventArgs> OrderReady;

    // Given. Raised after the last waiting order is finished. Exercise 1.
    // No details to send, so raise it with EmptyArgs().
    Event<EmptyArgs> AllCaughtUp;

    // Given. How many orders are in line right now.
    int GetWaitingCount() const;

    // Given. A copy of the line, oldest first, so callers can show it
    // but not change it.
    std::vector<Order> Waiting() const;

    // Build the order, put it in line, then announce it. Return the order.
    Order Place(const std::string& customer, const std::string& drink);

    // Take the oldest order out of line, then announce it. Return the order.
    // Refuse with a std::runtime_error when nothing is waiting.
    Order FinishNext();

private:
    std::queue<Order> waiting;
    int nextNumber = 1;
};
