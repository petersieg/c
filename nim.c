/*
Absolut simple Kosmos Logikus NIM simulation - siehe Anleitung dazu.
Logik Matrix wird mittels simuliertem Eprom (mem[]) abgebildet. Schalter s0..s9 = Adressleitungen A0..A9 (10 bits; 0..1023) und 
Taster = A10 (bit 11=1024). Es wird also ein 2kB Eprom simuliert. Die Lampen l0..l7 sind die Ausgänge/Werte im Eprom.
Es sind hier nur 8 bit realisiert (Eprom like) anstatt auch wieder 10 wie beim Original (das könnte man auch noch ändern).
Wie 'damals' die PLA durch Eproms ersetzt wurden bei C64 & Co.
Im Gegensatz zu dem original Spiel verlaufen die Lampen/Led's und die Schalter nicht von links nach rechts mit 0..9 aufsteigend, 
sondern Eprom/Binär like 9..0 von links nach rechts absteigend (das könnte man auch noch ändern).
 
(c) 2017 Peter.Sieg1@gmx.de - under GPL V2
*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

char mem[2048];

void save() {
   FILE* fp;
   if( (fp = fopen("rom.bin", "wb")) != NULL ) {
      fwrite(mem, 1, 2048, fp);
      fclose(fp);
   }
}

int main() 
{
  
   char adrstr[12];
   char valstr[9];
   char ad=32;
   int adr=0; //holds address for mem[]
   int val=0; //holds value at mem[adr]
   int t0=0;
   int t1=0;
   int t2=0;
   int t3=0;
   int t4=0;
   int t5=0;
   int t6=0;
   int t7=0;
   int t8=0;
   int t9=0;
   int tt=0;
   int i;

   for (i=0; i<2048; i++) mem[i]=0;

   //setup some values within mem[]
   mem[1024+0] = 2;		//Led 1
   mem[1024+1] = 1;		//Led 0
   mem[1024+3] = 1;		//Led 0
   mem[1024+7] = 4;		//Led 2
   mem[1024+15] = 2;		//Led 1
   mem[1024+31] = 1;		//Led 0
   mem[1024+63] = 1;		//Led 0
   mem[1024+127] = 4 + 128;	//Led 2 + 7 = Verloren
   mem[1024+255] = 2 + 128;	//Led 1 + 7 = Verloren
   mem[1024+511] = 1 + 128;	//Led 0 + 7 = Verloren
   mem[1023] = 64;		//Led 6 = Gewonnen

   printf("Enter: 0..9 to toggle switch 0..9, t=tast, x=exit\n");
   while (ad != 'x') {
      if (ad == 's') save();
      val = mem[adr];
      for (i = 7; i >= 0; i--)
	 valstr[7-i] = '0' + ((val >> i) & 0x1);
      valstr[8] = 0;      

      for (i = 10; i >= 0; i--)
	 adrstr[10-i] = '0' + ((adr >> i) & 0x1);
      adrstr[11] = 0;      
      printf("\nMSG=     -    VG---321");
      printf("\nLED=     -    76543210");
      printf("\nVAL=%4d -    %s:",val, valstr);
      printf("\nINP=%4d - %s:\n",adr, adrstr);
      ad = getchar();
      switch (ad) {
        case '0': if (t0 == 0) t0 = 1; else t0 = 0; break;
        case '1': if (t1 == 0) t1 = 1; else t1 = 0; break;
        case '2': if (t2 == 0) t2 = 1; else t2 = 0; break;
        case '3': if (t3 == 0) t3 = 1; else t3 = 0; break;
        case '4': if (t4 == 0) t4 = 1; else t4 = 0; break;
        case '5': if (t5 == 0) t5 = 1; else t5 = 0; break;
        case '6': if (t6 == 0) t6 = 1; else t6 = 0; break;
        case '7': if (t7 == 0) t7 = 1; else t7 = 0; break;
        case '8': if (t8 == 0) t8 = 1; else t8 = 0; break;
        case '9': if (t9 == 0) t9 = 1; else t9 = 0; break;
        case 't': if (tt == 0) tt = 1; else tt = 0; break;
      }
      adr = (t0 * 1) + (t1 * 2) + (t2 * 4) + (t3 * 8) + (t4 * 16) + (t5 * 32) + (t6 * 64) + (t7 * 128) + (t8 * 256) + (t9 * 512) + (tt * 1024);
      //printf("Char: %c, %d\n",ad,ad);
   }

   return 0;

}

