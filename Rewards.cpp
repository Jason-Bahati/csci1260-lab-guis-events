#include "Rewards.h"

#include "NotFinished.h"

// Given. How many finished drinks this customer has, or 0 for a new customer.
int Rewards::DrinksFor(const std::string& customer) const
{
    int count = 0;
    if (drinks.count(customer) > 0)
    {
        count = drinks.at(customer);
    }
    return count;
}

// Subscribe your handler to the bar's OrderReady event.
void Rewards::Connect(CoffeeBar& bar)
{
    // TODO: Exercise 2
    throw NotFinished();
}

// TODO: Exercise 2. Write the handler here. Add one to the customer's
// count, and when the count reaches a multiple of DrinksPerReward,
// raise FreeDrinkEarned.
