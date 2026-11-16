# CSCI 1260 GUIs and Events Lab

**Name:**
**Section:** 002
**Language:** C++

## How to run

```
cmake -S . -B build              sets up the build folder (once)
cmake --build build              builds the program (after every change)
./build/gui_events_lab           opens the window
./build/gui_events_lab check     prints the lab check
```

If CMake cannot find Qt, tell it where Qt is installed, for example
`cmake -S . -B build -DCMAKE_PREFIX_PATH="$(brew --prefix qt)"` on a Mac.
With Visual Studio on Windows, the program is `build\Debug\gui_events_lab.exe`.

## What I did not finish

(Write "Nothing" if all four parts match the expected output.)
