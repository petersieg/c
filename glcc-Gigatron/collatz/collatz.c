/* collatz sequence 
   see: https://en.wikipedia.org/wiki/Collatz_conjecture
   (C) 2023 P.Sieg - CC-BY-SA

x,n: number to sequence
  c: count sequence
  h: highest value in sequence for x,n

*/

#define NTIMES 1000

void main()
{
    unsigned long x,n,c,h,l,ul = 0;
    printf("Enter starting value (>=5): ");
    scanf("%lu",&l);
    if (l < 5) l = 5;				 /* l=lower starting value */
	ul = l + NTIMES;				 /* ul=upper limit value */
    printf("\n"); 					 /* next line */
	
    for (n=l; n<=ul; n++) {
      x = n;
      c = 0;
      h = 0;
      do {
      	if ((x % 2) == 0) x = x / 2; /* if number is equal then div 2 */
      	else x = x * 3 + 1;          /* if number is not equal then times 3 plus 1 */
      	c++;						 /* increase counter */
      	if (x > h) h = x;			 /* update highest number */
      	printf("n=%ld - c=%ld - h=%ld\r",n,c,h);
      } while (x > 1);
      printf("\n"); /* next number in new line */
    }
}

