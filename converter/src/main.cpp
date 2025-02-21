#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include "cscreen.h"
#include "creader.h"
using namespace std;

CReader reader;

void signalHandler(int signum) {
    reader.clean();
    exit(signum);
}

int main(void) {
    signal(SIGTERM, signalHandler);
    signal(SIGINT, signalHandler);

    CScreen screen;
    screen.printWelcomeMenu();

    if (!reader.processInput())
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
