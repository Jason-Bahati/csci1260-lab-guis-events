#pragma once

#include <string>

// Order: one drink for one customer. The coffee bar numbers each order.
// A blank name or a blank drink is refused with a std::invalid_argument,
// which is the "throw close to the problem" rule from the exceptions lecture.
class Order
{
public:
    // Checks the name and the drink, then saves all three values.
    Order(int number, const std::string& customer, const std::string& drink);

    // The number the coffee bar gave this order.
    int GetNumber() const;

    // The customer's name, with no spaces at either end.
    std::string GetCustomer() const;

    // The drink, with no spaces at either end.
    std::string GetDrink() const;

    // The order as text, like "#1 Ada, latte".
    std::string ToString() const;

private:
    int number;
    std::string customer;
    std::string drink;

    // True when the text is empty or only spaces. C# calls this IsNullOrWhiteSpace.
    static bool IsBlank(const std::string& text);

    // The text with the spaces at both ends removed. C# calls this Trim.
    static std::string Trim(const std::string& text);
};
