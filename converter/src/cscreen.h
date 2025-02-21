/**
 * cscreen.h
 * Title: Interface for screen class
 * Description: Class to print program welcome screen
 * Author: David Kopelent
*/

#ifndef CSCREEN
#define CSCREEN
#include <iostream>
#include <string>
using namespace std;

class CScreen {
public:
    /**
     * Print welcome sign when program is launched
     */
    void printWelcomeMenu(void);
};
#endif
