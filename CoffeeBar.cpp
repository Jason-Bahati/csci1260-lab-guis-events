#include "CoffeeBar.h"

#include <stdexcept>

#include "NotFinished.h"

// Given. How many orders are in line right now.
int CoffeeBar::GetWaitingCount() const
{
    return static_cast<int>(waiting.size());
}

// Given. A copy of the line, oldest first. A std::queue only shows its
// front, so this copies the whole queue and empties the copy one order
// at a time.
std::vector<Order> CoffeeBar::Waiting() const
{
    std::vector<Order> orders;
    std::queue<Order> line = waiting;
    while (!line.empty())
    {
        orders.push_back(line.front());
        line.pop();
    }
    return orders;
}

// Build the order, put it in line, then announce it. Return the order.
Order CoffeeBar::Place(const std::string& customer, const std::string& drink)
{
    // TODO: Part A, demo
    throw NotFinished();
}

// Take the oldest order out of line, then announce it. Return the order.
// Refuse with a std::runtime_error when nothing is waiting.
Order CoffeeBar::FinishNext()
{
    // TODO: Part A, demo. Then Exercise 1: announce AllCaughtUp when
    // the order you just finished was the last one in line.
    throw NotFinished();
}
