#include "Order.h"

#include <cctype>
#include <stdexcept>

// Checks the name and the drink, then saves all three values.
Order::Order(int number, const std::string& customer, const std::string& drink)
{
    if (IsBlank(customer))
    {
        throw std::invalid_argument("Customer name is required.");
    }
    if (IsBlank(drink))
    {
        throw std::invalid_argument("Drink is required.");
    }
    this->number = number;
    this->customer = Trim(customer);
    this->drink = Trim(drink);
}

// The number the coffee bar gave this order.
int Order::GetNumber() const
{
    return number;
}

// The customer's name, with no spaces at either end.
std::string Order::GetCustomer() const
{
    return customer;
}

// The drink, with no spaces at either end.
std::string Order::GetDrink() const
{
    return drink;
}

// The order as text, like "#1 Ada, latte".
std::string Order::ToString() const
{
    return "#" + std::to_string(number) + " " + customer + ", " + drink;
}

// True when the text is empty or only spaces.
bool Order::IsBlank(const std::string& text)
{
    return Trim(text).empty();
}

// The text with the spaces at both ends removed. std::isspace needs an
// unsigned char, so each character is converted before it is tested.
std::string Order::Trim(const std::string& text)
{
    size_t first = 0;
    while (first < text.size() && std::isspace(static_cast<unsigned char>(text[first])))
    {
        first++;
    }
    size_t last = text.size();
    while (last > first && std::isspace(static_cast<unsigned char>(text[last - 1])))
    {
        last--;
    }
    return text.substr(first, last - first);
}
