#include "HelperFunctions.h"
// Standard
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
// Set Project
#include "configs.h"
#include "globals.h"
#include "arrayset/arrayset.h"
#include "linklistset/linklistset.h"

void
processGlobals() {
    flag = chooseArrayOrLink();
    setA = ArraySet_create(25);
    setB = ArraySet_create(25);
    result = ArraySet_create(50);
    lsetA = LinkListSet_create();
    lsetB = LinkListSet_create();
    lresult = LinkListSet_create();
}//processGlobals()

void
destroyGlobals() {
    ArraySet_destroy(setA);
    ArraySet_destroy(setB);
    ArraySet_destroy(result);
    LinkListSet_destroy(lsetA);
    LinkListSet_destroy(lsetB);
    LinkListSet_destroy(lresult);
}//destroyGlobals()

int
getLine(char * str, int maxnum) {
    int count = 0;
    while(count < maxnum) {
        *str = getchar();
        if(*str == '\n' || *str == '\0' || *str == EOF) {
            *str = '\0';
            break;
        } else {
            ++str;
            ++count;
        }//if-else
    }//while
    return count;
}//getLine(str, maxnum)

void
startCommandLine() {
	// infinite loop to read-in commands
	while(1) {
		printHelpMenu();
		enum Command command = processCommandLine();
        switch(command) {
            case CMD_IA:
                processCMD_IA();
                break;
            case CMD_DA:
                processCMD_DA();
                break;
            case CMD_IB:
                processCMD_IB();
                break;
            case CMD_DB:
                processCMD_DB();
                break;
            case CMD_OU:
                processCMD_OU();
                break;
            case CMD_OI:
                processCMD_OI();
                break;
            case CMD_OD:
                processCMD_OD();
                break;
            case CMD_Q:
                processCMD_Q();
                break;
            default:
                // code should never get here.
                assert(0 && "Logic error in `startCommandLine` function");
                break;
        }//switch
	}//while
}//startCommandLine()

int
chooseArrayOrLink() {
    int ret = 0;
    char buffer[80];
    int value = 0;
    while(1) {
        printf("Use Array List or Linked List?\n"
                "1. Array List\n"
                "2. Linked List\n"
                "Input 1 or 2 to choose.\n");
        ret = scanf("%d", &value);
        macro_UNUSED(ret);
        getLine(buffer, 80);
        if(value == 1 || value == 2)
            return value;
    }//while
    assert(0 && "Logic error in `chooseArrayOrLink` function");
    exit(EXIT_FAILURE);
}//chooseArrayOrLink()

void
printHelpMenu() {
	printf(
		"Menu:\n"
		"IA: Insert into Set A      DA: Delete from Set A\n"
		"IB: Insert into Set B      DB: Delete from Set B\n"
		"OU: Union                  OI: Intersection\n"
		"OD: Difference             Q: Quit\n"
	);
}//printHelpMenu()

enum Command
processCommandLine() {
    const int maxnum = 80;
    char command[maxnum];

    while(1) {
        printf("Enter Command ===> ");
        int readin_num = getLine(command, maxnum);
        // if read-in nothing, repeat
        if(readin_num == 0)
            continue;

        // strncmp(A, B, n) compares A and B to see whether 2 strings
        // are the same, it they are same, return 0
        if(strncmp(command, "IA", maxnum) == 0)
            return CMD_IA;
        if(strncmp(command, "DA", maxnum) == 0)
            return CMD_DA;
        if(strncmp(command, "IB", maxnum) == 0)
            return CMD_IB;
        if(strncmp(command, "DB", maxnum) == 0)
            return CMD_DB;
        if(strncmp(command, "OU", maxnum) == 0)
            return CMD_OU;
        if(strncmp(command, "OI", maxnum) == 0)
            return CMD_OI;
        if(strncmp(command, "OD", maxnum) == 0)
            return CMD_OD;
        if(strncmp(command, "Q", maxnum) == 0)
            return CMD_Q;

        // if nothing matches, indicates that it was a wrong command
        printf("Command not right\n");
        printHelpMenu();
    }//while
    // code should never get here
    assert(0 && "Logic error in `processCommandLine()` function");
    return CMD_Q;
}//processCommandLine()

void
processCMD_IA() {
    char buffer[80];
    int value = 0;
    int ret = 0;
    printf("Enter Value   ===> ");
    ret = scanf("%d", &value);
    macro_UNUSED(ret);
    getLine(buffer, 80);
    
    if(flag == 1) {
        ret = ArraySet_insert(setA, value);
        if(ret == 0)
            printf("Element is already inside. Insersion not executed.\n");
        ArraySet_printall(setA);
    } else {
        ret = LinkListSet_insert(lsetA, value);
        if(ret == 0)
            printf("Element is already inside. Insersion not executed.\n");
        LinkListSet_printall(lsetA);
    }//if-else
}//processCMD_IA()

void
processCMD_DA() {
    int ret = 0;
    char buffer[80];
    int value = 0;
    printf("Enter Value   ===> ");
    ret = scanf("%d", &value);
    macro_UNUSED(ret);
    getLine(buffer, 80);

    if(flag == 1) {
        ret = ArraySet_delete(setA, value);
        if(ret == 0)
            printf("Element not found. Deletion not executed.\n");
        ArraySet_printall(setA);
    } else {
        ret = LinkListSet_delete(lsetA, value);
        if(ret == 0)
            printf("Element not found. Deletion not executed.\n");
        LinkListSet_printall(lsetA);
    }//if-else
}//processCMD_DA()

void
processCMD_IB() {
    int ret = 0;
    char buffer[80];
    int value = 0;
    printf("Enter Value   ===> ");
    ret = scanf("%d", &value);
    macro_UNUSED(ret);
    getLine(buffer, 80);

    if(flag == 1) {
        ret = ArraySet_insert(setB, value);
        if(ret == 0)
            printf("Element is already inside. Insersion not executed.\n");
        ArraySet_printall(setB);
    } else {
        ret = LinkListSet_insert(lsetB, value);
        if(ret == 0)
            printf("Element is already inside. Insersion not executed.\n");
        LinkListSet_printall(lsetB);
    }//if-else
}//processCMD_IB()

void
processCMD_DB() {
    int ret = 0;
    char buffer[80];
    int value = 0;
    printf("Enter Value   ===> ");
    ret = scanf("%d", &value);
    macro_UNUSED(ret);
    getLine(buffer, 80);
    
    if(flag == 1) {
        ret = ArraySet_delete(setB, value);
        if(ret == 0)
            printf("Element not found. Deletion not executed.\n");
        ArraySet_printall(setB);
    } else {
        ret = LinkListSet_delete(lsetB, value);
        if(ret == 0)
            printf("Element not found. Deletion not executed.\n");
        LinkListSet_printall(lsetB);
    }//if-else
}//processCMD_DB()

void
processCMD_OU() {
    if(flag == 1) {
        ArraySet_union(result, setA, setB);
        ArraySet_printall(result);
    } else {
        LinkListSet_union(lresult, lsetA, lsetB);
        LinkListSet_printall(lresult);
    }//if-else
}//processCMD_OU()

void
processCMD_OI() {
    if(flag == 1) {
        ArraySet_intersect(result, setA, setB);
        ArraySet_printall(result);
    } else {
        LinkListSet_intersect(lresult, lsetA, lsetB);
        LinkListSet_printall(lresult);
    }//if-else
}//processCMD_OI()

void
processCMD_OD() {
    if(flag == 1) {
        ArraySet_diff(result, setA, setB);
        ArraySet_printall(result);
    } else {
        LinkListSet_diff(lresult, lsetA, lsetB);
        LinkListSet_printall(lresult);
    }//if-else
}//processCMD_OD()

void
processCMD_Q() {
    printf("Goodbye!\n");
    exit(EXIT_SUCCESS);
}//processCMD_Q()

