// #include <stdio.h>
// #include <iostream>
// #include <termios.h>

// #include "Visualiser/Visualiser.h"

// static struct termios old, newConfig;

// /* Initialize new terminal i/o settings */
// void initTermios(int echo) {
//     tcgetattr(0, &old);                       /* grab old terminal i/o settings */
//     newConfig = old;                          /* make new settings same as old settings */
//     newConfig.c_lflag &= ~ICANON;             /* disable buffered i/o */
//     newConfig.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
//     tcsetattr(0, TCSANOW, &newConfig);        /* use these new terminal i/o settings now */
// }

// /* Restore old terminal i/o settings */
// void resetTermios(void) {
//     tcsetattr(0, TCSANOW, &old);
// }
// char getch(int echo) {
//     char ch;
//     initTermios(echo);
//     ch = getchar();
//     resetTermios();
//     return ch;
// }

// void printMenu() {
//     cout << "\033[J\033[2J\033[3J\033[H";
//     cout << "======= Sorting Algorithm Visualizer =======" << endl
//          << endl;
//     cout << "Main Menu:" << endl
//          << endl
//          << "[1]   Visualize Quick Sort" << endl
//          << "[2]   Visualize Heap Sort" << endl
//          << "[3]   Visualize Merge Sort" << endl
//          << "[4]   Visualize Alternate Merge Sort" << endl
//          << "[5]   Visualize Insertion Sort" << endl
//          << "[6]   Visualize Bubble Sort" << endl
//          << "[ESC] Exit" << endl;
// };

// int main() {
//     char c;
//     Visualiser visual;
//     SORTS sort;
//     bool validOption;
//     do {
//         printMenu();
//         c = getch(0);
//         validOption = false;
//         if (c - '1' < SORTS::SIZE && c != 27) validOption = true;
//         if (validOption) {
//             initTermios(0);
//             visual.sort(SORTS(c - '1'));
//             cout << "Press Any Key to continue" << endl;
//             getchar();
//             resetTermios();
//         }
//     } while (c != 27);
//     cout << "\033[HExited.";
//     return 0;
// }

#include "UI.h"

int main() {
    UI ui;
    int sort;
    Visualiser v;
    int delay;
    do {
        sort = ui.sortMenu();
        if(sort == -1){
            ui.exit();
            return 0;
        }
        delay = ui.delayMenu();
        if(delay < 0)delay = 0;
        v.setDelay(delay);
        v.sort(SORTS(sort));
        cout << "Sorting done. Press any key to go back";
        ui.getch(0);
        ui.getch(0);
    } while (sort != -1);
    
    return 0;
}