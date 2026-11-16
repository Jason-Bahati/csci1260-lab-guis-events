#include "Buzzer.h"

#include "NotFinished.h"

// Given. A copy of the messages, oldest first.
std::vector<std::string> Buzzer::Messages() const
{
    return messages;
}

// Subscribe OnOrderReady to the bar's OrderReady event and keep the ticket.
void Buzzer::Connect(CoffeeBar& bar)
{
    // TODO: Part B, demo
    throw NotFinished();
}

// Unsubscribe with the same ticket that subscribed.
void Buzzer::Disconnect(CoffeeBar& bar)
{
    // TODO: Part B, demo
    throw NotFinished();
}

// Runs every time the bar raises OrderReady, until Disconnect.
void Buzzer::OnOrderReady(const void* sender, const OrderEventArgs& e)
{
    // TODO: Part B, demo
    throw NotFinished();
}
