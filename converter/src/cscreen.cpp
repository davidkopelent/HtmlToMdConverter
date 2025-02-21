/**
 * cscreen.cpp
 * Title: Screen class implementation
 * Author: David Kopelent
 */

#include "config.h"
#include "cscreen.h"
using namespace std;

void CScreen::printWelcomeMenu(void) {
    int length = WELCOME_SCREEN_TEXT.length();
    int paramA = 2*(length/4-1) + length;
    int paramB = length/4-1;
    cout << " " << string(paramA, '-') << "\n|" << string(paramA, ' ') 
        << "|\n|" << string(paramB, ' ') << WELCOME_SCREEN << string(paramB, ' ') << "|\n|" 
        << string(paramA, ' ') << "|\n" << " " << string(paramA, '-') << " " << endl;
}
