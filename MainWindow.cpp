#include "MainWindow.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <stdexcept>

// Builds the window, then subscribes to everything it needs to hear.
MainWindow::MainWindow()
{
    BuildControls();

    // TODO: Part C, demo. Subscribe to bar.OrderPlaced.

    // TODO: Exercise 3. Subscribe to bar.OrderReady and bar.AllCaughtUp.

    // TODO: Part D, demo. Connect textChanged on both boxes to a handler,
    // then set the buttons for an empty window.

    // TODO: Exercise 4. Connect a Rewards object to the bar and
    // subscribe to its FreeDrinkEarned event.
}

// Builds every control on the window. C# keeps this part in MainWindow.axaml.
void MainWindow::BuildControls()
{
    setWindowTitle("Corner Cup");
    resize(560, 430);

    QVBoxLayout* page = new QVBoxLayout(this);
    page->setContentsMargins(20, 20, 20, 20);
    page->setSpacing(12);

    QLabel* title = new QLabel("Corner Cup");
    title->setStyleSheet("font-size: 24px; font-weight: bold;");
    page->addWidget(title);

    // TODO: Part C, demo. Build the rest of the window here, between the
    // title and the stretch. Give each control the object name the check
    // looks for with setObjectName, and connect each button's clicked
    // signal to its click handler.

    page->addStretch();
}

// Write the click handlers, the event handlers, and the helper
// methods below this line. Declare each one in MainWindow.h too.
