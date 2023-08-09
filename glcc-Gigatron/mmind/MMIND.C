/* simple text mode mastermind game for lccwin-32
   compiled also without any changes under cc65 6502 cross compiler
   www.cc65.org
   (c) 2002-2006 Peter Sieg, Rabishauerstr.9, D-37603 Holzminden,
   peter.sieg1@gmx.de
   program under GNU GPL
   greeting to my family: Heike, Robin and Janis
*/


#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <gigatron/console.h>

#define WORD int


/*-------------------------------------------------------------------
// Main programm
//-----------------------------------------------------------------*/

void main()
{
   unsigned ret;
   WORD a;
   WORD statusm,apid;
   char ad;
   int bv;
   char ch[20],my[20];
   WORD done;
   WORD i,j,count,offcnt;
   WORD z1,z2,z3,z4; /* 4 digits for my 4-digit char array */
   WORD echo_xy[4];

   count = 1; offcnt = 0; done = 0;
   /* create random 4-digit string in char array my */
   /* strcpy(my,"1234"); */

   srand((unsigned int)time());
   /*
   srand1("Random seed generation.. wait.. hit a key.");
   ad = getchar();
   */
   z1 = (rand() % 9) + 1; /* 1..9 */
   do { z2 = (rand() % 9) + 1; } while (z2==z1);
   do { z3 = (rand() % 9) + 1; } while ((z3==z1) || (z3==z2));
   do { z4 = (rand() % 9) + 1; } while ((z4==z1) || (z4==z2) || (z4==z3));
   my[0] = z1+48; /* int 1..9 + ascii(48)='0' => '1'..'9' */
   my[1] = z2+48;
   my[2] = z3+48;
   my[3] = z4+48;
   my[4] = 0;     /* terminate string */

   mincprintf("Guess my 4-digit number...(%s); 0000 to abort.\n","****");
   /* insert my to see code */
   do {
     mincprintf("\nGuess %d:",count+offcnt*10);
     console_readline(ch,20);
     ch[4] = 0;
     if (strcmp("0000",ch)==0) done = 2; /* give up */
     if (strcmp(my,ch)==0) done = 1; /* success; code broken */
     /* check how near guess it and print hint */
     /* for right digit at  right position print # */
     /* for right digit but wrong position print + */
     if (done==0) {
       for (i=0;i<4;i++) {
         if (ch[i]==my[i]) mincprintf("# ");
         else for (j=0;j<4;j++) if (ch[i]==my[j]) mincprintf("+ ");
       }
     }
     count++;
     if (count==11) {
       count = 1;
       offcnt++;
     }
   } while (done==0);
   if (done==1)
     mincprintf("\n\nYou broke the code!");
   else
     mincprintf("\n\nYou gave up..");
   mincprintf("\nPress return to exit.");
   ad = console_getkey();
   exit(0);
}

