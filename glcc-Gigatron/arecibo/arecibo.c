// found at: https://codegolf.stackexchange.com/questions/182924/output-the-arecibo-message
// Just converted to plain c and line break after 23 chars
// converted into simple Gigatron art demo - changes (c) 2024 Peter Sieg CC-BY-SA
/*
  As an Explanation (Marc Bender): 
  I concatenated the 73 lines of sample output given to one long line. 
  I encoded them in hexadecimal where the bit order is msbfirst (using this program:
  https://github.com/Marc-Bender/longBinaryStreamToHex/releases/download/addedErrorCode-4/longBinaryStreamToHex.exe) 
  I shortened the Output of that by about 70 hexadecimal Digits by using the letters 'G'-'Z' as a sign to repeat 
  the last Digit for a certain amount of times (Z = 2more times, Y = 3more times …) 
*/

//#include <stdio.h>
//#include <iostream>
//using namespace std;
#include <gigatron/sys.h>
//#include <gigatron/console.h>

void drawPixel(int x, int y, int color)
{
    screenMemory[y][x] = color;
}

int main()
{
    const char arecibo[]="02A800505012Y595Y240U180YD0Y1A0Y540YF80V61C618800321A3186BEFBEF80X10Y40W20YFC001F0X1861C620200868639AFBEFBE0W40C0100180Z83003F0607C00C001008041030101860400C430Z19800310C018604040804101804403008802020808080800600C030047580080800107C002174B604E4FEE1C1B80283B20507E40A0C08360U3820Z751554E00AA0Z140ZF80Z7FC00380E00C0060340160CC06611414422448804510Z8420010040Z940079F4F0";
    int c,d,i = 0,j,p,x = 0,y = 0;

	//_console_setup();
    //_console_reset(0x3f00);
    _console_clear((char*)0x800, 0x00,120);  /* simple clear screen - 0x00 is the background color */
    
    for (;;)
    {
    for (p=0;p<6;p++) // p = x offset times 24 pixels
    {
	//d = rand() % 63; // random color offset
	d = SYS_Random() & 63; // random color offset
	// Instead of "SYS_Random() % 63", try "SYS_Random() & 63" to avoid importing the division code.
	
    while (i<sizeof(arecibo)-1)
    {   
        char digit = arecibo[i];
        int count=0;
        if (digit >= '0' & digit <= '9')
        {
            digit -= '0';
        }
        else if (digit>='A'& digit<='F')
        {
            digit -=  'A'-10;
        }
        else if (digit > 'F'&digit<='Z')
        {
            //digit does not contain any valid hex digit in this case
            count = 'Z' - digit+1; //digit = Z means repeat 2 more times...
            digit = arecibo[i - 1];
        }
        for (count=count; count >= 0; count--)
        {
            for (j = 0; j<4; j++)
            {
                //cout << (int)(((digit)&(8 >> j))>0);
                //printf("%d",(int)(((digit)&(8 >> j))>0));
                c = (int)(((digit)&(8 >> j))>0);
                drawPixel(x+(p*24),y,c+d);
                x++;
                if (x > 22) {
                  //printf("\n");
                  x = 0;
                  y++;
                }
            }
        }
        i++;
    }
    i=0; // reset string index
    x=0; y=0;
    } // for (p=0;p<6;p++)
    for (d=0; d < 16384; d++); // dirty delay
    } // for (;;)
    
    return 0;
}

