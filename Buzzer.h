#pragma once

#include <string>
#include <vector>

#include "CoffeeBar.h"

// Buzzer: a subscriber that can also stop listening. It records the
// messages a customer's phone would show, like
// "Buzz: Ada, your latte is ready."
//
// Part B. Write Connect, Disconnect, and OnOrderReady along with the
// Session 1 demo.
class Buzzer
{
public:
    // Given. A copy of the messages, oldest first.
    std::vector<std::string> Messages() const;

    // Subscribe OnOrderReady to the bar's OrderReady event and keep the ticket.
    void Connect(CoffeeBar& bar);

    // Unsubscribe with the same ticket that subscribed.
    void Disconnect(CoffeeBar& bar);

private:
    std::vector<std::string> messages;

    // Given. The ticket subscribe hands back, saved so Disconnect can return it.
    int ticket = 0;

    // Runs every time the bar raises OrderReady, until Disconnect.
    void OnOrderReady(const void* sender, const OrderEventArgs& e);
};
