/* fibonacci numbers */

#define NTIMES 5
#define NUMBER 24

main()
{
    int i;
    unsigned value, fib();

    printf("%d Iterationen\n",NTIMES);
    for (i=0; i<NTIMES; i++) value = fib(NUMBER);
    printf("fib(%d) = %u.\n",NUMBER,value);
    exit(0);
}

unsigned fib(x)
int x;
{
    if (x>2) return(fib(x-1)+fib(x-2));
    return(1);
}

