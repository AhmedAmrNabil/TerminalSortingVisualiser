#ifndef UI_H
#define UI_H
#include <stdio.h>
#include <termios.h>

#include <iostream>

#include "Visualiser/Visualiser.h"
static struct termios old, newConfig;
class UI {
    void initTermios(int echo) {
        tcgetattr(0, &old);
        newConfig = old;
        newConfig.c_lflag &= ~ICANON;
        newConfig.c_lflag &= echo ? ECHOE : ~ECHOE;
        tcsetattr(0, TCSANOW, &newConfig);
    }



    void resetTermios(void) {
		newConfig = old;
		newConfig.c_lflag |= ICANON;
		newConfig.c_lflag |= ECHOE;
        tcsetattr(0, TCSANOW, &newConfig);
    }

   public:
    UI() {
        initTermios(0);
    }
    char getch(int echo) {
        char ch;
        initTermios(echo);
        ch = getchar();
        resetTermios();
        return ch;
    }
    int sortMenu() {
        char c;
        do {
            std::cout << "\033[J\033[2J\033[3J\033[H\033[?25l"
                      << "======= Sorting Algorithm Visualizer =======\n"
                      << "Main Menu:\n"
                      << "[1]   Visualize Quick Sort\n"
                      << "[2]   Visualize Heap Sort\n"
                      << "[3]   Visualize Merge Sort\n"
                      << "[4]   Visualize Alternate Merge Sort\n"
                      << "[5]   Visualize Insertion Sort\n"
                      << "[6]   Visualize Bubble Sort\n"
                      << "[ESC] Exit\n";
            c = getch(0);
            if (c == 27) return -1;
        } while (((c - '1') > SORTS::SIZE - 2) || ((c - '1') < 0));
        return c - '1';
    }
    int delayMenu() {
        resetTermios();
        std::cout << "\033[J\033[2J\033[3J\033[H\033[?25h"
                  << "Enter sorting Delay(ms): ";
        int x;
        cin >> x;

        initTermios(0);
        return x;
    }
    void exit() {
        std::cout << "\033[J\033[2J\033[3J\033[H\033[?25hExited.";
    }
};

#endif