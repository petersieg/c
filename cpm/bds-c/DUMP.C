/* Beispiel fuer Anwendung der formatierten Ausgabe
** (c) RS 17.05.1991
*/
#include	<bdscio.h>
#define		MAXSIZE	16
#define		PAGELEN	20
#define		FROMFILE 1
#define 	BUFFSIZE 128
#define         MODE 0

FILE	*source;		/* fuer Filedump */
char	*address;		/* fuer Speicherdump */
int	sourceflag;
char    counter,buffer[BUFFSIZE];
char    lines;
char	c;

main(argc, argv)
	int	argc;
	char	*argv[];
{
	int	i, k, val;
	char	string[MAXSIZE+1];

        address=0;
        sourceflag=0;

        puts("\014");

	setup(argc, argv);

	c='\n';
	
	do{   if ( c == 0x20 ) lines=1;
		else { 
		 	puts("\014");
			lines=PAGELEN;
		     }
	
		for(k=0; k<lines; k++){
			printf("  %04x  |  ", address);
			for (i=0; i<MAXSIZE; i++, address++){
				val = nextvalue();
				printf("%02x ", val);
				string[i] = (val<32 || val>127)? '.' :val;
			}
			string[MAXSIZE] = '\0';
			printf("   %s\n", string);
		}
		if ( c == '\n' ) 
		printf("\n  --continue--	Space = Line / Enter = Page\n");

		c=getchar();
	}while(c == '\n'  || c == 0x20 );
}

setup(argc, argv)
	int	argc;
	char	*argv[];
{
	printf("*** %sdump ***\n\n", (argc>1)? "File" : "Speicher");
	if(argc > 1){
				/* benutze "r+b" in Turbo-C */
		if((source = open(argv[1], MODE )) == -1 ){
			printf("can't open %s\n", argv[1]);
			exit(-1);
		}
		sourceflag = FROMFILE;
	}
	else{
		printf("Startwert(hex):\t");
		scanf("%x", &address);
	}
}

int	nextvalue()
{
	char	wert;

	if(sourceflag == FROMFILE){
           if(counter==0){
                counter=127; 
		if(read(source,buffer,1) == 0 ) exit(0);
		}	
                wert=*(buffer+128-counter);
		counter--;
	}
	else	wert = *address;
	return(wert);
}
