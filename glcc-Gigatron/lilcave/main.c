//#include <stdbool.h>
#include <stdio.h>
#include "parsexec.h"

#define bool int
#define false 0
#define true 1

static char input[100] = "look around";

static bool getInput(void)
{
   printf("\n--> ");
   return fgets(input, sizeof input, stdin) != NULL;
}

int main()
{
   printf("Welcome to Little Cave Adventure.\n");
   while (parseAndExecute(input) && getInput());
   printf("\nBye!\n");
   return 0;
}
