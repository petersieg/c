/*
* pi-in-hex.c
*
* Copyright (c) 2014, Swapnajit Mitra. All rights reserved.
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
* MA 02110-1301 USA
*/
/* 
 *  This program is modified from David H Bailey's original C 
 *  program piqpr8.c to generate HEX digits of pi from a given location.
 *  The original program is freely available from various internet 
 *  locations, including the original source: 
 *     
 *  The contribution of the original source is greatly acknowledged. 
 *  - Swapnajit 02/27/2014
 */  

/*  
    This program implements the BBP algorithm to generate a few hexadecimal
    digits beginning immediately after a given position id, or in other words
    beginning at position id + 1.  On most systems using IEEE 64-bit floating-
    point arithmetic, this code works correctly so long as d is less than
    approximately 1.18 x 10^7.  If 80-bit arithmetic can be employed, this limit
    is significantly higher.  Whatever arithmetic is used, results for a given
    position id can be checked by repeating with id-1 or id+1, and verifying 
    that the hex digits perfectly overlap with an offset of one, except possibly
    for a few trailing digits.  The resulting fractions are typically accurate 
    to at least 11 decimal digits, and to at least 9 hex digits.  
*/

/*  David H. Bailey     2006-09-08 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NHX 16

main(int argc, char **argv)
{
  double pid, s1, s2, s3, s4;
  double series (int m, int n);
  void ihex (double x, int m, char c[]);
  int id = 0; /* id is the digit position. Digits generated follow immediately after id. */
  /*int id = 1000000;*/ /* id is the digit position. Digits generated follow immediately after id. */
  char chx[NHX];

  long long int nhx = 10;
  int cmd;
  int verbose = 0;

  if (argc == 1) {
     fprintf (stderr, "Default bit position is %d and number of hex digits are %d.\n", id, nhx);
  } else { // argc > 1
     for (cmd=1; cmd<argc; cmd++) { 
        if ((strcmp(argv[cmd], "--start")== 0) || (strcmp(argv[cmd], "-s")== 0)) { 
           id = atoi(argv[++cmd]);
	} else if ((strcmp(argv[cmd], "--nHexDigits")== 0) || (strcmp(argv[cmd], "-n")== 0)) { 
           nhx = atoi(argv[++cmd]) ;
	} else if ((strcmp(argv[cmd], "--verbose")== 0) || (strcmp(argv[cmd], "-v")== 0)) { 
           verbose = 1;
	} else if ((strcmp(argv[cmd], "--help")== 0) || (strcmp(argv[cmd], "-h")== 0)) { 
           help();
        } else { 
           fprintf (stderr, "Illegal option %s.\n", argv[cmd]);
	   exit (2);
	}
     }

     if (verbose) {
        fprintf (stderr, "Set bit position is %d and number of hex digits are %d.\n", id, nhx);
     }
  }

  do { 
     s1 = series (1, id);
     s2 = series (4, id);
     s3 = series (5, id);
     s4 = series (6, id);
     pid = 4. * s1 - 2. * s2 - s3 - s4;
     pid = pid - (int) pid + 1.;
     ihex (pid, NHX, chx);
     
     if (verbose) { 
        printf (" position = %i\n fraction = %.15f \n hex digits =  %10.10s\n", id, pid, chx);
     } else { 
        printf ("%10.10s", chx);
     }
     nhx -= 10;
     id += 10;
     if (verbose) {
        fprintf (stderr, "\nSet bit position is %d and number of hex digits left are %d.\n", id, nhx);
     }
  } while (nhx>0); 
  if (!verbose) printf ("\n");
}

int help () { 

/*  Help menu. Exits after completing. */

   fprintf (stderr, "Usage: piqpr8 [--help|-h]|[--verbose|-v] [--start|-s idPosition] [--nHexDigits|-n numHexDigits]\n");
   fprintf (stderr, "where:\n");
   fprintf (stderr, "\tidPosition  : the program start listing idPosition+1 after \'.\'. Default is 1\n");
   fprintf (stderr, "\tnumHexDigits: the number of hex digit the program lists. Default is 16.\n");
   exit (2) ; 
}

void ihex (double x, int nhx, char chx[])

/*  This returns, in chx, the first nhx hex digits of the fraction of x. */

{
  int i;
  double y;
  char hx[] = "0123456789ABCDEF";

  y = fabs (x);

  for (i = 0; i < nhx; i++){
    y = 16. * (y - floor (y));
    chx[i] = hx[(int) y];
  }
}

double series (int m, int id)

/*  This routine evaluates the series  sum_k 16^(id-k)/(8*k+m) 
    using the modular exponentiation technique. */

{
  int k;
  double ak, eps, p, s, t;
  double expm (double x, double y);
#define eps 1e-17

  s = 0.;

/*  Sum the series up to id. */

  for (k = 0; k < id; k++){
    ak = 8 * k + m;
    p = id - k;
    t = expm (p, ak);
    s = s + t / ak;
    s = s - (int) s;
  }

/*  Compute a few terms where k >= id. */

  for (k = id; k <= id + 100; k++){
    ak = 8 * k + m;
    t = pow (16., (double) (id - k)) / ak;
    if (t < eps) break;
    s = s + t;
    s = s - (int) s;
  }
  return s;
}

double expm (double p, double ak)

/*  expm = 16^p mod ak.  This routine uses the left-to-right binary 
    exponentiation scheme. */

{
  int i, j;
  double p1, pt, r;
#define ntp 25
  static double tp[ntp];
  static int tp1 = 0;

/*  If this is the first call to expm, fill the power of two table tp. */

  if (tp1 == 0) {
    tp1 = 1;
    tp[0] = 1.;

    for (i = 1; i < ntp; i++) tp[i] = 2. * tp[i-1];
  }

  if (ak == 1.) return 0.;

/*  Find the greatest power of two less than or equal to p. */

  for (i = 0; i < ntp; i++) if (tp[i] > p) break;

  pt = tp[i-1];
  p1 = p;
  r = 1.;

/*  Perform binary exponentiation algorithm modulo ak. */

  for (j = 1; j <= i; j++){
    if (p1 >= pt){
      r = 16. * r;
      r = r - (int) (r / ak) * ak;
      p1 = p1 - pt;
    }
    pt = 0.5 * pt;
    if (pt >= 1.){
      r = r * r;
      r = r - (int) (r / ak) * ak;
    }
  }

  return r;
}
