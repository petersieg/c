//#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "match.h"
#include "reach.h"

#define bool int
#define false 0
#define true 1

bool executeOpen(void)
{
   OBJECT *obj = reachableObject("what you want to open", params[0]);
   if (obj != NULL) (*obj->open)();
   return true;
}

bool executeClose(void)
{
   OBJECT *obj = reachableObject("what you want to close", params[0]);
   if (obj != NULL) (*obj->close)();
   return true;
}

bool executeLock(void)
{
   OBJECT *obj = reachableObject("what you want to lock", params[0]);
   if (obj != NULL) (*obj->lock)();
   return true;
}

bool executeUnlock(void)
{
   OBJECT *obj = reachableObject("what you want to unlock", params[0]);
   if (obj != NULL) (*obj->unlock)();
   return true;
}
