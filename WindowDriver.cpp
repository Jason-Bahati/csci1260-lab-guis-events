#include "WindowDriver.h"

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>

#include "NotFinished.h"

// Keeps the window and lets it settle. The window is never shown: Qt can
// type into and click a hidden window, and showing it during the check
// would only print warnings.
WindowDriver::WindowDriver(QWidget& window)
    : window(window)
{
    Flush();
}

// Replaces the text in a QLineEdit, the same as a person typing it.
void WindowDriver::Type(const std::string& name, const std::string& text)
{
    Find<QLineEdit>(name)->setText(QString::fromStdString(text));
    Flush();
}

// Clicks a QPushButton. A disabled button ignores the click, as on screen.
void WindowDriver::Click(const std::string& name)
{
    QPushButton* button = Find<QPushButton>(name);
    if (button->isEnabled())
    {
        button->click();
    }
    Flush();
}

// True when the control is enabled, false when it is disabled.
bool WindowDriver::IsEnabled(const std::string& name)
{
    return Find<QWidget>(name)->isEnabled();
}

// The text a QLabel or QLineEdit is showing, or (blank).
std::string WindowDriver::Text(const std::string& name)
{
    QWidget* control = Find<QWidget>(name);
    QString text = "";
    QLabel* label = qobject_cast<QLabel*>(control);
    QLineEdit* box = qobject_cast<QLineEdit*>(control);
    if (label != nullptr)
    {
        text = label->text();
    }
    else if (box != nullptr)
    {
        text = box->text();
    }
    std::string result = text.toStdString();
    if (result.empty())
    {
        result = "(blank)";
    }
    return result;
}

// The items in a QListWidget, joined with " | ", or (empty).
std::string WindowDriver::Items(const std::string& name)
{
    QListWidget* list = Find<QListWidget>(name);
    std::string result = "";
    for (int row = 0; row < list->count(); row++)
    {
        if (row > 0)
        {
            result += " | ";
        }
        result += list->item(row)->text().toStdString();
    }
    if (list->count() == 0)
    {
        result = "(empty)";
    }
    return result;
}

// A control that does not exist yet means that part is not finished.
// findChild returns nullptr when no child of type T has that object name.
template <typename T>
T* WindowDriver::Find(const std::string& name)
{
    T* control = window.findChild<T*>(QString::fromStdString(name));
    if (control == nullptr)
    {
        std::string kind = T::staticMetaObject.className();
        throw NotFinished("The window has no " + kind + " named " + name + ".");
    }
    return control;
}

// Lets the window finish any work the last action queued up.
void WindowDriver::Flush()
{
    QApplication::processEvents();
}
