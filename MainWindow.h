#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QWidget>

#include "CoffeeBar.h"

// MainWindow: the code behind the window. It shows the coffee bar and asks
// it to do things. Every decision about orders stays in CoffeeBar.
//
// Part C and Part D are written along with the Session 2 demos.
// Exercise 3 and Exercise 4 are yours.
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    // Builds the window, then subscribes to everything it needs to hear.
    MainWindow();

private:
    CoffeeBar bar;

    // TODO: Part C, demo. Add a pointer field for each control here.
    // The handout lists every control and the exact object name the check
    // looks for. A name that is spelled differently is a control the check
    // cannot find.

    // TODO: Exercise 4. Add a Rewards field (and #include "Rewards.h").

    // Builds every control on the window. C# keeps this part in MainWindow.axaml.
    void BuildControls();

    // Declare the click handlers, the event handlers, and the helper
    // methods below this line.
};
