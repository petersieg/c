// Adapted from: https://www.rosettacode.org/wiki/Number_reversal_game#C
// 03/2019 peter.sieg2@gmx.de

//#include <stdio.h>
#include <gigatron/console.h>

void shuffle_list(int *list, int len)
{
    //We'll just be swapping 100 times. Could be more/less. Doesn't matter much.
    int n=100;
    int a=0;
    int b=0;
    int buf = 0;
    //Random enough for common day use..
    srand(time());
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
    int list[9] = {1,2,3,4,5,6,7,8,9};
    int tries=0;
    unsigned int i;
    int input;

    printf("Number Reversal Game. Type a number to flip the first n numbers.\n");
    printf("Win by sorting the numbers in ascending order.\n");
    printf("Anything besides numbers are ignored.\n");
    printf(" |1_2_3_4_5_6_7_8_9|\n");
    shuffle_list(list,9);
 
 
    while(!check_array(list, 9))
    {
        ((tries<10) ? printf("%d:", tries) : printf("%d:", tries));
        for(i=0;i<9;i++)printf("%d ",list[i]);
        printf(" ?: ");
        while(1)
        {
            //Just keep asking for proper input
            //scanf("%d", &input);
            input = console_waitkey() - 48;
            if(input>1&&input<10)
                break;
 
            printf("\n%d - Please enter a number between 2 and 9: ", (int)input);
        }
        tries++;
        do_flip(list, 9, input);
    }
    printf("Hurray! You solved it in %d moves!\n", tries);
}


