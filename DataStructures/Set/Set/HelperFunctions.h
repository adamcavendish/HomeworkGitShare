#pragma once

#include "configs.h"

/**
 * @brief this macro is used to indicate that the `ident` variable is not used
 */
#define macro_UNUSED(ident) (void)ident

/**
 * @brief getline function read-in a line from stdin
 * @param str buffer starting address
 * @param maxnum the maximum number of characters to read-in
 * @return the number of characters actually read-in
 */
int
getLine(char * str, int maxnum);

void
processGlobals();

void
destroyGlobals();

/**
 * @brief start the command-line interaction
 */
void
startCommandLine();

int
chooseArrayOrLink();

/**
 * @brief print the help menu
 */
void
printHelpMenu();

/**
 * @brief process the commandline
 * @return the command parsed
 */
enum Command
processCommandLine();

void
processCMD_IA();

void
processCMD_DA();

void
processCMD_IB();

void
processCMD_DB();

void
processCMD_OU();

void
processCMD_OI();

void
processCMD_OD();

void
processCMD_Q();








