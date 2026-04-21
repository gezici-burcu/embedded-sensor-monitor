#include "../include/app.h"

#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

/**
 * Entry point of the embedded assignment simulation.
 *
 * This file initializes the application and runs the main loop.
 * One loop iteration represents one 1-second sampling period.
 */

int main(void)
{
    srand((unsigned int)time(NULL));

    app_init();

    while (1)
    {
        app_run_cycle();

#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
    }

    return 0;
}