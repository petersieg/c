// Adapted from: https://www.rosettacode.org/wiki/Number_reversal_game#C
// 03/2019 peter.sieg2@gmx.de

#include <stdio.h>

void shuffle_list(int *list, int len)
{
    //We'll just be swapping 100 times. Could be more/less. Doesn't matter much.
    int n=100;
    int a=0;
    int b=0;
    int buf = 0;
    //Random enough for common day use..
    srand(time(NULL));
    while(n--)
    {
        //Get random locations and swap
        a = rand()%len;
        b = rand()%len;
        buf = list[a];
        list[a] = list[b];
        list[b] = buf;
    }
    // "shuffled to ordered state" fix:
    if (check_array(list, len)) shuffle_list (list, len);
}
 
void do_flip(int *list, int length, int num)
{
    //Flip a part on an array
    int swap;
    int i=0;
    for(i;i<--num;i++)
    {
        swap=list[i];
        list[i]=list[num];
        list[num]=swap;
    }
}
 
int check_array(int *arr, int len)
{
    while(--len)
    {
        if(arr[len]!=(arr[len-1]+1))
            return 0;
    }
    return 1;
}


void main()
{
    printf("Number Reversal Game. Type a number to flip the first n numbers.\n");
    printf("Win by sorting the numbers in ascending order.\n");
    printf("Anything besides numbers are ignored.\n");
    printf("\t  |1__2__3__4__5__6__7__8__9|\n");
    int list[9] = {1,2,3,4,5,6,7,8,9};
    shuffle_list(list,9);
 
    int tries=0;
    unsigned int i;
    int input;
 
    while(!check_array(list, 9))
    {
        ((tries<10) ? printf("Round %d :  ", tries) : printf("Round %d : ", tries));
        for(i=0;i<9;i++)printf("%d  ",list[i]);
        printf("  Gimme that number: ");
        while(1)
        {
            //Just keep asking for proper input
            scanf("%d", &input);
            if(input>1&&input<10)
                break;
 
            printf("\n%d - Please enter a number between 2 and 9: ", (int)input);
        }
        tries++;
        do_flip(list, 9, input);
    }
    printf("Hurray! You solved it in %d moves!\n", tries);
}


