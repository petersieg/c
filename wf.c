#include <stdio.h>
#include <ctype.h>
#include <string.h>
/*
 *  WORDFIND
 *  Mon Oct 26 10:00:50 1992 -- Scott R. Turner
 *
 *  Build word search type puzzles.
 *
 */

/*
 *  The wordfind square.
 *
 */
#define MAXX 20
#define MAXY 20
char wfs[MAXX][MAXY];

/*
 *  The word list.
 *
 */
#define MAXWORDS 1000
#define MAXWORDLEN 20
#define MAXCLUELEN 50
int numwords = 0;
char wl[MAXWORDS][MAXWORDLEN];
char clues[MAXWORDS][MAXCLUELEN];
int used[MAXWORDS];

/*
 *  Global Options
 *
 *  -h        Horizontal
 *  -v        Vertical
 *  -d        Diagonal
 *  -b        Backwards
 *
 *  -r        Random selections from wordlist
 *
 *  -x <num>  Horizontal size of puzzle
 *  -y <num>  Vertical size of puzzle
 *
 *  -t <str>  Title of puzzle
 *  -p        Don't print words to find below puzzle
 *  -c        print clues instead of words
 *
 *  -f <file> Word list
 *
 */
int backwards = 0;
int randselect = 0;
int xsize = 15, ysize = 15;
char title[80] = "W*O*R*D F*I*N*D";
int printwords = 1, printclues = 0;
char wordfile[80] = "words";

/*
 *  First column is horizontal offset.
 *  Second column is vertical offset.
 *
 */
int dirs[8][2] = {{1,0},
                 {0,1},
                 {1,1},
                 {1,-1},
                 {-1,0},
                 {0,-1},
                 {-1,-1},
                 {-1,1}};
/*
 *  Which directions are permitted?
 *
 */
int permitted[8] = {0,0,0,0,0,0,0,0};

main (argc, argv)
char *argv[];
{
        char s;
       int i,j;
       FILE *wf;

        while (--argc > 0) {
         argv++;
         if ((*argv)[0] == '-') {
           s = (*argv)[1];
           switch (s) {
           case 'a':
             for(i=0;i<8;i++) permitted[i] = 1;
             break;
           case 'h':
             permitted[0] = 1;
             break;
           case 'v':
             permitted[1] = 1;
             break;
           case 'd':
             permitted[2] = 1;
             permitted[3] = 1;
             break;
           case 'b':
             backwards = 1;
             break;
           case 'r':
             randselect = 1;
             break;
           case 'p':
             printwords = 0;
             break;
           case 'c':
             printclues = 1;
             break;
           case 'x':
             xsize = atoi((*++argv));
             if (xsize > 20) xsize = 20;
             if (xsize < 1) xsize = 1;
             argc--;
             break;
           case 'y':
             ysize = atoi((*++argv));
             if (ysize > 20) ysize = 20;
             if (ysize < 1) ysize = 1;
             argc--;
             break;
           case 't':
             (void) strcpy(title,(*++argv));
             argc--;
             break;
           case 'f':
             (void) strcpy(wordfile,(*++argv));
             argc--;
             break;
           default:
             fprintf(stderr,"Unknown option: %c\n",s);
             fprintf(stderr,"Options:\n");
             fprintf(stderr,"   -h (Permit horizontal placement)\n");
             fprintf(stderr,"   -v (Permit vertical placement)\n");
             fprintf(stderr,"   -d (Permit diagonal placement)\n");
             fprintf(stderr,"   -b (Permit backwards placement)\n");
             fprintf(stderr,"   -a (Permit all placements)\n");
             fprintf(stderr,"   -r (Select randomly from wordlist)\n");
             fprintf(stderr,"   -x <num> (Specify width of puzzle)\n");
             fprintf(stderr,"   -y <num> (Specify height of puzzle)\n");
             fprintf(stderr,"   -t <title> (Specify title of puzzle)\n");
             fprintf(stderr,"   -p (Don't print words below the puzzle)\n");
             fprintf(stderr,"   -c (Print clues instead of the words used)\n")
;
             fprintf(stderr,"   -f <file> (Specify word list file)\n");
             exit(1);
           };
         } else {
           (void) strcpy(wordfile,(*argv));
         };
        };

       /*
        *  Do default placements?
        *
        */
       j = 0;
       for(i=0;i<8;i++) j += permitted[i];
       if (!j) {
         permitted[0] = 1;
         permitted[1] = 1;
         permitted[2] = 1;
       };

       /*
        *  Backwards check.
        *
        */
       if (backwards)
         for(i=0;i<4;i++) permitted[i+4] = permitted[i];

       /*
        *  See if we can read the word file.
        *
        */
       if ((wf = fopen(wordfile,"r")) == NULL) {
         fprintf(stderr,"Unable to open wordfile: %s.\n",wordfile);
         fprintf(stderr,"Specify correct wordfile with -f.\n");
         exit(-1);
       };
       /*
        *  Word file consists of a word, a space and the remainder of the
        *  line, which is the "clue".
        *
        */
       while(fscanf(wf,"%s",wl[numwords]) != EOF) {
         fgets(clues[numwords],MAXCLUELEN,wf);
         for(i=strlen(clues[numwords])-1;isspace(clues[numwords][i]);i--)
           clues[numwords][i] = 0;
         numwords++;
       };
       for(i=0;i<numwords;i++) used[i] = 0;

       /*
        *  Print the title, centered.
        *
        */
       for(i=0;i<((80-strlen(title))/2);i++) putchar(' ');
       printf("%s\n\n",title);

       /*
        *  Initialize.
        *
        */
       for(i=0;i<xsize;i++)
         for(j=0;j<ysize;j++) wfs[i][j] = 0;

       /*
        *  Now for each word in the wordlist, try to place the word
        *  somewhere in the puzzle.
        *
        */
       srandom(time(0));
       if (randselect) {
         for(i=0;i<numwords;i++) {
           j = random(0)%numwords;
           while (used[j]) {
             j = (j+1)%numwords;
           };
           placeword(j);
         }
       } else {
         for(i=0;i<numwords;i++) placeword(i);
       };

       /*
        *  Now go through and fill in all the spaces in the board.
        *
        */
       fillboard();

       /*
        *  Print the board out.
        *
        */
       printboard();

       /*
        *  Print out the words to be found.
        *
        */
       print_words();
}

/*
 * Placeword
 *
 * Using the available options, try to place the current word in the
 * puzzle.  Return 0 if unable to do so.
 *
 */
int placeword(word)
     int word;
{
  int tried[8];
  int i,x,y,start_dir,start_x,start_y;


  /*
   *  Initialize the directions we've tried.
   *
   */
  for(i=0;i<8;i++) tried[i] = !permitted[i];

  /*
   *  Start somewhere randomly and then cycle around until you get
   *  back to your starting point or you manage to place the word.
   *
   */
  i = start_dir = random(0)%8;
  do {
    if (!tried[i]) {
      tried[i] = 1;
      /*
       *  Pick a random starting spot somewhere on the board and start
       *  trying this direction from that spot.
       *
       */
      y = start_y = random(0)%ysize;
      do {
       x = start_x = random(0)%xsize;
       do {
         if (try(x,y,i,word,0)) {
           try(x,y,i,word,1);
           goto success;
         };
         x=(x+1)%xsize;
       } while (x != start_x);
       y=(y+1)%ysize;
      } while (y != start_y);
    };
    i=(i+1)%8;
  } while (i != start_dir);
  used[word] = -1;
  return(0);
 success:
  used[word] = 1;
  return(1);
}

/*
 *  TRY
 *
 *  Try placing a word in a given location in a given direction.
 *
 */
int try(x,y,dir,word,place)
     int x,y,dir,word,place;
{
  int len;
  int cnt;

  /*
   *  The length of the word can be used to rule out some places
   *  immediately.
   *
   */
  len = strlen(wl[word]);
  if (dirs[dir][0] == 1 && (len + x) > xsize) return(0);
  if (dirs[dir][0] == -1 && (len - 1) > x) return(0);
  if (dirs[dir][1] == 1 && (len + y) > ysize) return(0);
  if (dirs[dir][1] == -1 && (len - 1) > y) return(0);

  /*
   *  Otherwise, we have to try to place the word.
   *
   */
  for(cnt=0;cnt<len;cnt++) {
    if (wfs[x][y] != 0 && wfs[x][y] != wl[word][cnt]) {
      return(0);
    };
    if (place) wfs[x][y] = wl[word][cnt];
    x += dirs[dir][0];
    y += dirs[dir][1];
  };
  return(1);
};

/*
 *  Printboard
 *
 *  Print the board.
 *
 */
int printboard()
{
  int i,j,prefix;

  prefix = (76-(xsize*2))/2;

  putchar('\n');
  for(i=0;i<prefix;i++) putchar(' ');
  putchar('+');
  for(i=0;i<xsize;i++) {
    putchar('-');
    putchar('-');
  };
  putchar('-');
  putchar('+');
  putchar('\n');
  for(j=0;j<ysize;j++) {
    for(i=0;i<prefix;i++) putchar(' ');
    putchar('|');
    putchar(' ');
    for(i=0;i<xsize;i++) {
      if (wfs[i][j] == 0) putchar(' ');
      else putchar(toupper(wfs[i][j]));
      putchar(' ');
    };
    putchar('|');
    putchar('\n');
  };
  for(i=0;i<prefix;i++) putchar(' ');
  putchar('+');
  for(i=0;i<xsize;i++) {
    putchar('-');
    putchar('-');
  };
  putchar('-');
  putchar('+');
  putchar('\n');
};

/*
 *  Fillboard
 *
 *  Fill the spaces in the board with letters chosen randomly from the
 *  words we used.
 *
 */
int fillboard()
{
  int word,spot;
  int i,j;

  for(i=0;i<xsize;i++)
    for(j=0;j<ysize;j++)
      if (wfs[i][j] == 0) {
       do {
         word = random(0)%numwords;
       } while (used[word] == -1);
       spot = random(0)%strlen(wl[word]);
       wfs[i][j] = wl[word][spot];
      };
};

/*
 *  Printwords
 *
 *  Print out the words actually in the puzzle.
 *
 */
int print_words()
{
  int i, cnt;

  cnt = 0;
  for(i=0;i<numwords;i++)
    if (used[i] == 1) {
      if (!(cnt%4)) putchar('\n');
      cnt++;
      if (printclues)
       printf("%-20s",clues[i]);
      else
       printf("%-20s",wl[i]);
    };
  putchar('\n');
  putchar('\n');
};
