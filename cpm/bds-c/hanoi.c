/* Turm von Hanoi */

main()
{
    int n;

    printf("Anzahl der Scheiben: ");
    scanf("%d",&n);
    printf("\nStart\n");
    hanoi(n, 'A', 'B', 'C');
    printf("Stop\n");
}

hanoi(n, a, b, c)
int n, a, b, c;
{
    if (n > 1) hanoi(n-1,a,c,b);
    printf("Scheibe %d von %c nach %c.\n", n, a, c);  
    if (n > 1) hanoi(n-1,b,a,c);
}
