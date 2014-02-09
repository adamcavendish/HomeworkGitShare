// Standard
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Set project
#include "configs.h"
#include "globals.h"
#include "HelperFunctions.h"

int main(void)
{
    processGlobals();
    startCommandLine();
    destroyGlobals();

    return 0;
}//main

