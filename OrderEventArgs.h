#pragma once

#include "Order.h"

// OrderEventArgs: the details that travel with an order event.
// Every handler receives one of these as its e parameter.
class OrderEventArgs
{
public:
    // Saves the order so every handler can read it.
    explicit OrderEventArgs(const Order& order);

    // The order this event is about.
    const Order& GetOrder() const;

private:
    Order order;
};
