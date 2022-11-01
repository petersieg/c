/* Sieb des Eratosthenes */

#define TRUE      1
#define FALSE     0
#define SIZE   8190
#define NTIMES   10

char flags[SIZE+1];

main()
{
    int i, prime, k, count, iter;
/*  char flags[SIZE+1]; in siebl.c */

    printf("%d Iterationen\n",NTIMES);
    for (iter=0; iter<NTIMES; iter++) {
        count = 0;
        for (i=0; i<=SIZE; i++) flags[i] = TRUE;
        for (i=0; i<=SIZE; i++)
            if (flags[i]) {
                prime = i + i + 3;
             /* printf("%d\n",prime); */
                for (k=i+prime; k<=SIZE; k+=prime) flags[k] = FALSE;
                count++;
            }
    }
    printf("last prime: %d, %d prim numbers\n",prime,count);
    exit(0);
}

