#include "helperFunctions.h"

int generateRandomInt(int min, int max){
    return (rand()%(max+1-min)) + min;
}

void refreshTotals(){
    mvwprintw(totalswin,2,1,"Total entered: %d",enteredTotal);
    mvwprintw(totalswin,3,1,"Total left: %d", leftTotal);
    wrefresh(totalswin);
}