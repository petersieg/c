
#include <stdio.h>

int main()
{
    const unsigned char arecibo[] = {

 0b00000010,0b10101000,0b00000000
,0b00101000,0b00101000,0b00001000
,0b10001000,0b10001001,0b01100100
,0b10101010,0b10101010,0b01001000
,0b00000000,0b00000000,0b00000000
,0b00000000,0b00001100,0b00000000
,0b00000000,0b00110100,0b00000000
,0b00000000,0b00110100,0b00000000
,0b00000000,0b01010100,0b00000000
,0b00000000,0b01111100,0b00000000
,0b00000000,0b00000000,0b00000000
,0b11000011,0b10001100,0b00110000
,0b10000000,0b00000011,0b00100000
,0b11010001,0b10001100,0b00110100
,0b11111011,0b11101111,0b10111110
,0b00000000,0b00000000,0b00000000
,0b00010000,0b00000000,0b00000100
,0b00000000,0b00000000,0b00000000
,0b00001000,0b00000000,0b00000010
,0b11111000,0b00000000,0b00111110
,0b00000000,0b00000000,0b00000000
,0b11000011,0b00001110,0b00110000
,0b10000000,0b10000000,0b00100000
,0b11010000,0b11000111,0b00110100
,0b11111011,0b11101111,0b10111110
,0b00000000,0b00000000,0b00000000
,0b00010000,0b00110000,0b00000100
,0b00000000,0b00110000,0b00000000
,0b00001000,0b00110000,0b00000010
,0b11111000,0b00110000,0b00111110
,0b00000000,0b00110000,0b00000000
,0b00100000,0b00010000,0b00001000
,0b00010000,0b00110000,0b00010000
,0b00001100,0b00110000,0b00100000
,0b00000011,0b00010000,0b11000000
,0b00000000,0b00110011,0b00000000
,0b00000011,0b00010000,0b11000000
,0b00001100,0b00110000,0b00100000
,0b00010000,0b00100000,0b00010000
,0b00100000,0b00110000,0b00001000
,0b01000000,0b00110000,0b00001000
,0b01000000,0b00010000,0b00010000
,0b00100000,0b00100000,0b00100000
,0b00010000,0b00000000,0b11000000
,0b00001100,0b00000011,0b00000000
,0b00100011,0b10101100,0b00000000
,0b00100000,0b00100000,0b00000000
,0b00100000,0b11111000,0b00000000
,0b00100001,0b01110100,0b10110110
,0b00000010,0b01110010,0b01111110
,0b10111000,0b01110000,0b01101110
,0b00000000,0b01010000,0b01110110
,0b00100000,0b01010000,0b01111110
,0b00100000,0b01010000,0b01100000
,0b00100000,0b11011000,0b00000000
,0b00000000,0b00000000,0b00000000
,0b00111000,0b00100000,0b00000000
,0b00111010,0b10001010,0b10101010
,0b00111000,0b00000010,0b10101000
,0b00000000,0b00000010,0b10000000
,0b00000000,0b11111000,0b00000000
,0b00000011,0b11111110,0b00000000
,0b00001110,0b00000011,0b10000000
,0b00011000,0b00000000,0b11000000
,0b00110100,0b00000001,0b01100000
,0b01100110,0b00000011,0b00110000
,0b01000101,0b00000101,0b00010000
,0b01000100,0b10001001,0b00010000
,0b00000100,0b01010001,0b00000000
,0b00000100,0b00100001,0b00000000
,0b00000100,0b00000001,0b00000000
,0b00000001,0b00101000,0b00000000
,0b01111001,0b11110100,0b11110000
};

    int c,d,i = 0,j,p,x = 0,y = 0;

	
    while (i<sizeof(arecibo))
    {   
        unsigned char digit = arecibo[i];
        i++;
        printf(",0x%02x",digit);
        if ((i % 3) == 0) printf("\n");
    }
    
    return 0;
}
