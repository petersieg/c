#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*************************************************************************************************/
/* Conversion-functions */
typedef unsigned char byte, *buffer;

/*************************************************************************************************/
int main(int argc, char *argv[])
{
    FILE* fp;
    if(argc > 1)
    {
        buffer buff;
        int idx = (-1);
        unsigned int bytes_readed = 0;

        if( (fp = fopen(argv[1], "rb")) == NULL )
        {
           puts("[!]Problem with opening the file.");
           exit;
        }
        else
           puts("File has been opened successfully.\n");

        /* Finds the file size, allocates memory for the buffer and copies the file within the buffer (faster processing) */
        unsigned int fp_size;
        fseek(fp, 0, SEEK_END);
        fp_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        buff = calloc(fp_size, sizeof(byte));
        fread(buff, sizeof(byte), fp_size, fp);
        fclose(fp);
        
        while( ++idx <= fp_size )
        {
            byte current = buff[idx];

            //printf("%05u;'%04X;'%02X\n", bytes_readed, bytes_readed, current);
		 printf("    vipMemory[pc++] = 0x%02X;\n", current);

            bytes_readed++;
        }
        free(buff);
    }

}
