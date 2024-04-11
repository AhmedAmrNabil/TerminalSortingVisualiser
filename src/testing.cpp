#include <stdio.h>
#include <termios.h>

#include <iostream>

#include "Visualiser/Visualiser.h"

static struct termios old, newConfig;

/* Initialize new terminal i/o settings */
void initTermios(int echo) {
    tcgetattr(0, &old);                       /* grab old terminal i/o settings */
    newConfig = old;                          /* make new settings same as old settings */
    newConfig.c_lflag &= ~ICANON;             /* disable buffered i/o */
    newConfig.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
    tcsetattr(0, TCSANOW, &newConfig);        /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) {
    tcsetattr(0, TCSANOW, &old);
}
char getch(int echo) {
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

void printMenu() {
    cout << "\033[J\033[2J\033[3J\033[H";
    cout << "======= Sorting Algorithm Visualizer =======" << endl
         << endl;
    cout << "Main Menu:" << endl
         << endl
         << "[1]   Visualize Quick Sort" << endl
         << "[2]   Visualize Bubble Sort" << endl
         << "[3]   Visualize Merge Sort" << endl
         << "[4]   Visualize Alternate Merge Sort" << endl
         << "[5]   Visualize Insertion Sort" << endl
         << "[ESC] Exit" << endl;
};




int main() {
    char c;
    Visualiser visual;
    SORTS sort;
    bool validOption;
    do {
        printMenu();
        c = getch(0);
        validOption = false;
        switch (c) {
            case '1':
                sort = Quick;
                validOption = true;
                break;
            case '2':
                sort = Bubble;
                validOption = true;
                break;
            case '3':
                sort = Merge;
                validOption = true;
                break;
            case '4':
                sort = AltMerge;
                validOption = true;
                break;
            case '5':
                sort = Insertion;
                validOption = true;
                break;
            case 27:
                cout << "\033[HExited.";
                return 0;
        }
        if (validOption) {
            initTermios(0);
            visual.sort(sort);
            cout << "Press Any Key to continue" << endl;
            getchar();
            resetTermios();
        }
    } while (c != 27);
    return 0;
}