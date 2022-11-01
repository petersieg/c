/* Quick sort */

#define MAX 5000
#define MOD 0x8000
#define A   8391
#define C   8813

int seed;

int buffer[MAX];

main()
{
    int i, temp;

    seed = 7;
    printf("Filling array\n");
    for (i=0; i<MAX; i++) {
        temp = random(MOD);
        if (temp < 0) temp = (-temp);
        buffer[i] = temp;
/*      printf("%7d ",temp); */
    }
    printf("\nArray full\nStarting sort\n");
    quick(0,MAX-1,buffer);

/*  for (i=0; i<MAX; i++) {
        if (i%8==0) printf("\n");
        else printf(" ");
        printf("%7d",buffer[i]);
    }
*/  printf("Stop\n");
    exit(0);
}

quick(low, high, base)
int low, high, base[];
{
    int i, j, x, temp;
/*  register i; in quickr.c */

    if (low < high) {
        for (i=low,j=high,x=base[high];i<j;) {
            while(i<j && base[i]<=x) i++;
            while(j>i && base[j]>=x) j--;
            if (i<j) {
                temp = base[i];
                base[i] = base[j];
                base[j] = temp;
            }
        }
        temp = base[i];
        base[i] = base[high];
        base[high] = temp;
        quick(low,i-1,base);
        quick(i+1,high,base);
    }
}

random(size)
int size;
{
    seed = seed*A + C;
    return(seed%size);
}

