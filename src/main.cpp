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