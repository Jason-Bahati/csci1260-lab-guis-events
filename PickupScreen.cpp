#include "PickupScreen.h"

#include "NotFinished.h"
#include <string>

// Given. A copy of the lines on the screen, oldest first.
std::vector<std::string> PickupScreen::Lines() const
{
    return lines;
}

// Subscribe OnOrderReady to the bar's OrderReady event.
void PickupScreen::Connect(CoffeeBar& bar)
{
    // TODO: Part B, demo
    bar.OrderReady.subscribe(
        [this](auto sender, const auto& e) { OnOrderReady(sender, e); });
}

// Runs every time the bar raises OrderReady.
void PickupScreen::OnOrderReady(const void* sender, const OrderEventArgs& e)
{
    // TODO: Part B, demo

    lines.push_back("Ready: #" + std::to_string(e.GetOrder().GetNumber()) +
                    " " + e.GetOrder().GetCustomer());
}
