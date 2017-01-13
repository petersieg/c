#include<stdio.h>
#include<time.h>
 
main()
{
    srand(time(NULL));
    int g1, g2, g3, g4,turn,exact,near;
    int c1,c2,c3,c4 = 0;
    c1 = rand() %9 + 1;
c2:
    c2 = rand() %9 + 1;
    if (c1 == c2) goto c2;
c3:
    c3 = rand() %9 + 1;
    if (c2 == c3) goto c3;
c4:
    c4 = rand() %9 + 1;
    if (c3 == c4) goto c4;

    /*printf("Answer is: %d %d %d %d\n",c1,c2,c3,c4);*/
    exact = 0;
    near = 0;
    for (turn = 1; turn <= 10; turn++)
    {       
        printf("Turn %d\nPlease enter each number separated by spaces!\n",turn);
        printf("Please enter your guess (e.g. 1 5 3 4):\n");
        scanf("%d %d %d %d",&g1,&g2,&g3,&g4);
         
        if (g1==c1)
        exact++;
        else if (g1==c2||g1==c3||g1==c4)
        near++;
         
        if (g2==c2)
        exact++;
        else if (g2==c1||g2==c3||g2==c4)
        near++;
         
        if (g3==c3)
        exact++;
        else if (g3==c1||g3==c2||g3==c4)
        near++;
         
        if (g4==c4)
        exact++;
        else if (g4==c1||g4==c2||g4==c3)
        near++;
         
        printf("Number of Exact Match: %d\n",exact);
        printf("Number of Near Match: %d\n\n",near);
         
        if (exact==4)
        {
          printf("You break the code by trying %d time(s)\n",turn);
          printf("Game Over!");
          turn = 10;
        }
        else
        {
          exact = 0;
          near = 0;
        }
         
        if (turn==10 && exact!=4)
        {
          printf("You fail to break the code!\n");
          printf("Game Over!");
          printf("\nAnswer is: %d %d %d %d\n",c1,c2,c3,c4);
        }
    }   
}