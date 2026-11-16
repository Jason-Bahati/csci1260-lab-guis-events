#pragma once

#include <string>
#include <vector>

#include "CoffeeBar.h"

// PickupScreen: a subscriber. It listens for OrderReady and keeps the
// lines the screen above the counter would show, like "Ready: #1 Ada".
//
// Part B. Write Connect and OnOrderReady along with the Session 1 demo.
class PickupScreen
{
public:
    // Given. A copy of the lines on the screen, oldest first.
    std::vector<std::string> Lines() const;

    // Subscribe OnOrderReady to the bar's OrderReady event.
    void Connect(CoffeeBar& bar);

private:
    std::vector<std::string> lines;

    // Runs every time the bar raises OrderReady.
    void OnOrderReady(const void* sender, const OrderEventArgs& e);
};
