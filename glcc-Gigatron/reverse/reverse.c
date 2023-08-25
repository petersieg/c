// Adapted from: https://www.rosettacode.org/wiki/Number_reversal_game#C
// 03/2019 peter.sieg2@gmx.de

//#define GIGATRON

#ifdef GIGATRON
#include <conio.h>
#else
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#endif

int check_array(int *arr, int len)
{
    int i;
    for (i=--len; i>2; i--)
    {
        if(arr[i]!=(arr[i-1]+1))
            return 0;
    }
    return 1;
}

void do_flip(int *list, int length, int num)
{
    //Flip a part on an array
    int swap;
    int i;
    for(i=2;i<--num;i++)
    {
        swap=list[i];
        list[i]=list[num];
        list[num]=swap;
    }
}
 
void shuffle_list(int *list, int len)
{
    //We'll just be swapping 100 times. Could be more/less. Doesn't matter much.
    int n=50;
    int a=0;
    int b=0;
    int buf = 0;
    int i;

    i=len-2;
    while(n--)
    {
        //for(i=2;i<11;i++)printf("%d ",list[i]); printf("\n");
        //Get random locations and swap
        a = 2+rand()%i; 
        b = 2+rand()%i; 
        buf = list[a];
        list[a] = list[b];
        list[b] = buf;
        
        //do_flip(list, len, rand()%len);
    }
    // "shuffled to ordered state" fix:
    if (check_array(list, len)) shuffle_list (list, len);
}
 
void main()
{
    int list[11] = {0,0,1,2,3,4,5,6,7,8,9};
    int tries=0;
    unsigned int i;
    unsigned int seed = 0;
    int input;

#ifdef GIGATRON
    printf("Wait a bit, then press key\n");
    while (!kbhit()) seed++;
    //Random enough for common day use..
    srand(seed); input = getch();
#else
    srand(time(NULL));//
#endif
    printf("Number Reversal Game. Typea number to flip the first n numbers.\n");
    printf("Win by sorting the numbers in ascending order.\n");
    printf("Anything besides numbers  are ignored.\n");
    printf(" |1_2_3_4_5_6_7_8_9|\n");
    shuffle_list(list,11);
 
 
    while(!check_array(list, 11))
    {
        printf("\n%d:", tries);
        for(i=2;i<11;i++)printf("%d ",list[i]);
        printf(" ?: ");
        while(1)
        {
            //Just keep asking for proper input
#ifdef GIGATRON
            input = getche() - 48;
            //scanf("%d", &input);
#else
            scanf("%d", &input);
#endif
            if(input>1&&input<10)
                break;
 
            printf("\n%d - Please enter a number between 2 and 9: ", (int)input);
        }
        tries++;
        input +=2;
        do_flip(list, 11, input);
    }
    printf("Hurray! You solved it in %d moves!\n", tries);
}


