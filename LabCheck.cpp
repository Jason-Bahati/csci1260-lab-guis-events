#include "LabCheck.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>

#include <QtGlobal>

#include "Buzzer.h"
#include "CoffeeBar.h"
#include "MainWindow.h"
#include "NotFinished.h"
#include "PickupScreen.h"
#include "Rewards.h"
#include "WindowDriver.h"

// The check runs when you ask for it, and always on GitHub,
// because the GitHub machine has no screen to open a window on.
bool LabCheck::ShouldRun(int argc, char* argv[])
{
    bool asked = argc > 1 && std::string(argv[1]) == "check";
    bool onGitHub = qEnvironmentVariable("GITHUB_ACTIONS") == "true";
    return asked || onGitHub;
}

// Prints the heading, then runs the four parts in order.
void LabCheck::Run()
{
    std::cout << "=== CSCI 1260 GUIS AND EVENTS LAB ===" << std::endl;
    std::cout << std::endl;
    RunPart("Part A: the coffee bar announces", PartA);
    std::cout << std::endl;
    RunPart("Part B: listeners", PartB);
    std::cout << std::endl;
    RunPart("Part C: the window", PartC);
    std::cout << std::endl;
    RunPart("Part D: buttons that know when they can work", PartD);
}

// A part you have not finished prints one line instead of stopping
// the whole program, so the other parts still run.
void LabCheck::RunPart(const std::string& title, std::function<void()> part)
{
    std::cout << title << std::endl;
    try
    {
        part();
    }
    catch (const NotFinished&)
    {
        std::cout << "  Not finished yet." << std::endl;
    }
}

// ---------- Session 1: events with no window ----------

// Part A: places and finishes orders while the check listens.
void LabCheck::PartA()
{
    CoffeeBar bar;
    std::vector<std::string> placed;
    std::vector<std::string> ready;
    int caughtUp = 0;

    // The check is a subscriber too. It writes down what it hears,
    // and how long the line was at the moment it heard it.
    bar.OrderPlaced.subscribe([&](const void* sender, const OrderEventArgs& e)
    {
        placed.push_back("#" + std::to_string(e.GetOrder().GetNumber())
                         + " (waiting " + std::to_string(bar.GetWaitingCount()) + ")");
    });
    bar.OrderReady.subscribe([&](const void* sender, const OrderEventArgs& e)
    {
        ready.push_back("#" + std::to_string(e.GetOrder().GetNumber())
                        + " (waiting " + std::to_string(bar.GetWaitingCount()) + ")");
    });
    bar.AllCaughtUp.subscribe([&](const void* sender, const EmptyArgs& e)
    {
        caughtUp++;
    });

    Line("Place Ada, latte:", bar.Place("Ada", "latte").ToString());
    Line("Place Ben, mocha:", bar.Place("Ben", "mocha").ToString());
    Line("Place a blank name:", Refused([&]() { bar.Place("  ", "chai"); }));
    Line("OrderPlaced heard:", Join(placed, ", "));
    Line("FinishNext:", bar.FinishNext().ToString());
    Line("AllCaughtUp heard:", Times(caughtUp));
    Line("FinishNext:", bar.FinishNext().ToString());
    Line("AllCaughtUp heard:", Times(caughtUp));
    Line("OrderReady heard:", Join(ready, ", "));
    Line("FinishNext when empty:", Refused([&]() { bar.FinishNext(); }));
}

// Part B: the pickup screen, the buzzer, and the rewards listen.
void LabCheck::PartB()
{
    CoffeeBar bar;
    PickupScreen screen;
    Buzzer buzzer;
    screen.Connect(bar);
    buzzer.Connect(bar);

    bar.Place("Ada", "latte");
    bar.Place("Ben", "mocha");
    bar.Place("Cy", "chai");
    bar.FinishNext();
    buzzer.Disconnect(bar);
    bar.FinishNext();
    bar.FinishNext();

    std::cout << "  Pickup screen:" << std::endl;
    for (const std::string& line : screen.Lines())
    {
        std::cout << "    " << line << std::endl;
    }
    std::cout << "  Buzzer, disconnected after #1:" << std::endl;
    for (const std::string& message : buzzer.Messages())
    {
        std::cout << "    " << message << std::endl;
    }

    std::cout << "  Rewards, Cy orders three times:" << std::endl;
    CoffeeBar shop;
    Rewards rewards;
    std::vector<std::string> earned;
    rewards.Connect(shop);
    rewards.FreeDrinkEarned.subscribe([&](const void* sender, const OrderEventArgs& e)
    {
        earned.push_back(e.GetOrder().GetCustomer() + " on #" + std::to_string(e.GetOrder().GetNumber()));
    });

    shop.Place("Cy", "latte");
    shop.Place("Ada", "mocha");
    shop.Place("Cy", "chai");
    shop.Place("Cy", "latte");
    while (shop.GetWaitingCount() > 0)
    {
        shop.FinishNext();
    }
    InnerLine("Drinks for Ada, Cy:", std::to_string(rewards.DrinksFor("Ada")) + " " + std::to_string(rewards.DrinksFor("Cy")));
    InnerLine("FreeDrinkEarned heard:", earned.empty() ? "nothing" : Join(earned, ", "));
}

// ---------- Session 2: the window, driven with no screen ----------

// Part C: places two orders and finishes both through the window.
void LabCheck::PartC()
{
    MainWindow mainWindow;
    WindowDriver window(mainWindow);

    window.Type("CustomerBox", "Ada");
    window.Type("DrinkBox", "latte");
    window.Click("PlaceButton");
    Line("Place Ada, latte:", window.Items("WaitingList"));
    Line("Boxes after Place:", window.Text("CustomerBox") + " " + window.Text("DrinkBox"));

    window.Type("CustomerBox", "Ben");
    window.Type("DrinkBox", "mocha");
    window.Click("PlaceButton");
    Line("Place Ben, mocha:", window.Items("WaitingList"));

    window.Click("ReadyButton");
    Line("Click Ready:", window.Items("PickupList"));
    window.Click("ReadyButton");
    Line("Click Ready again:", window.Items("PickupList"));
    Line("Waiting list:", window.Items("WaitingList"));
    Line("Status:", window.Text("StatusText"));
}

// Part D: checks when each button is enabled, then earns a free drink.
void LabCheck::PartD()
{
    MainWindow mainWindow;
    WindowDriver window(mainWindow);

    Line("Place enabled, boxes empty:", tf(window.IsEnabled("PlaceButton")));
    window.Type("CustomerBox", "Cy");
    Line("Place enabled, name only:", tf(window.IsEnabled("PlaceButton")));
    window.Type("DrinkBox", "latte");
    Line("Place enabled, name and drink:", tf(window.IsEnabled("PlaceButton")));
    Line("Ready enabled, none waiting:", tf(window.IsEnabled("ReadyButton")));
    window.Click("PlaceButton");
    Line("Ready enabled, one waiting:", tf(window.IsEnabled("ReadyButton")));

    window.Type("CustomerBox", "Cy");
    window.Type("DrinkBox", "chai");
    window.Click("PlaceButton");
    window.Type("CustomerBox", "Cy");
    window.Type("DrinkBox", "mocha");
    window.Click("PlaceButton");
    window.Click("ReadyButton");
    window.Click("ReadyButton");
    window.Click("ReadyButton");
    Line("Ready enabled, all finished:", tf(window.IsEnabled("ReadyButton")));
    Line("Reward text:", window.Text("RewardText"));
}

// ---------- helpers ----------

// Prints one result line: the label padded to 32 characters, then the value.
void LabCheck::Line(const std::string& label, const std::string& value)
{
    std::cout << "  " << std::left << std::setw(32) << label << value << std::endl;
}

// Prints one indented result line: the label padded to 30 characters.
void LabCheck::InnerLine(const std::string& label, const std::string& value)
{
    std::cout << "    " << std::left << std::setw(30) << label << value << std::endl;
}

// "1 time" for one, "N times" for any other count.
std::string LabCheck::Times(int count)
{
    return count == 1 ? "1 time" : std::to_string(count) + " times";
}

// "True" or "False", spelled the way C# prints a bool.
std::string LabCheck::tf(bool value)
{
    return value ? "True" : "False";
}

// The items with the separator between each pair.
std::string LabCheck::Join(const std::vector<std::string>& items, const std::string& separator)
{
    std::string result = "";
    for (size_t index = 0; index < items.size(); index++)
    {
        if (index > 0)
        {
            result += separator;
        }
        result += items[index];
    }
    return result;
}

// Runs one request and reports whether the class refused it.
// NotFinished is not caught here, so it still reaches RunPart.
std::string LabCheck::Refused(std::function<void()> request)
{
    std::string result = "accepted";
    try
    {
        request();
    }
    catch (const std::invalid_argument& ex)
    {
        result = "refused: " + std::string(ex.what());
    }
    catch (const std::runtime_error& ex)
    {
        result = "refused: " + std::string(ex.what());
    }
    return result;
}
