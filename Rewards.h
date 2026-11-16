#pragma once

#include <map>
#include <string>

#include "CoffeeBar.h"

// Rewards: a subscriber that is also a publisher. It counts finished drinks
// for each customer and announces FreeDrinkEarned on every third one.
//
// Exercise 2. Write Connect and a private handler named OnOrderReady.
class Rewards {
  public:
    static const int DrinksPerReward = 3;

    // Given. Raise it with the same OrderEventArgs the bar sent you.
    Event<OrderEventArgs> FreeDrinkEarned;

    // Given. How many finished drinks this customer has, or 0 for a new
    // customer.
    int DrinksFor(const std::string& customer) const;

    // Subscribe your handler to the bar's OrderReady event.
    void Connect(CoffeeBar& bar);

  private:
    std::map<std::string, int> drinks;

    // TODO: Exercise 2. Declare your handler here:
    void OnOrderReady(const void* sender, const OrderEventArgs& e);
};
