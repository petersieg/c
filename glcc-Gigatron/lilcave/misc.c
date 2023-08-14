//#include <stdbool.h>
#include <stdio.h>
#include "object.h"
#include "misc.h"

#define bool int
#define false 0
#define true 1

bool isHolding(OBJECT *container, OBJECT *obj)
{
   return validObject(obj) && obj->location == container;
}

OBJECT *getPassage(OBJECT *from, OBJECT *to)
{
   if (from != NULL && to != NULL)
   {
      OBJECT *obj;
      for (obj = objs; obj < endOfObjs; obj++)
      {
         if (isHolding(from, obj) && obj->prospect == to)
         {
            return obj;
         }
      }
   }
   return NULL;
}

DISTANCE getDistance(OBJECT *from, OBJECT *to)
{
   return to == NULL                               ? distUnknownObject :
          !validObject(to)                         ? distNotHere :
          to == from                               ? distSelf :
          isHolding(from, to)                      ? distHeld :
          isHolding(to, from)                      ? distLocation :
          isHolding(from->location, to)            ? distHere :
          isHolding(from, to->location)            ? distHeldContained :
          isHolding(from->location, to->location)  ? distHereContained :
          getPassage(from->location, to) != NULL   ? distOverthere :
                                                     distNotHere;
}

OBJECT *actorHere(void)
{
   OBJECT *obj;
   for (obj = objs; obj < endOfObjs; obj++)
   {
      if (isHolding(player->location, obj) && obj != player &&
          obj->health > 0)
      {
         return obj;
      }
   }
   return NULL;
}

int listObjectsAtLocation(OBJECT *location)
{
   int count = 0;
   OBJECT *obj;
   for (obj = objs; obj < endOfObjs; obj++)
   {
      if (obj != player && isHolding(location, obj))
      {
         if (count++ == 0)
         {
            printf("%s:\n", location->contents);
         }
         printf("%s\n", obj->description);
      }
   }
   return count;
}
