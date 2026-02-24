#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // usleep()

#define CHAR_DELAY_US 20000     // 20 ms Zeichenverzögerung
#define LINE_DELAY_US 300000    // 300 ms Zeilenverzögerung

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ascii-file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "Error: %s fopen\n", argv[1]);
        return EXIT_FAILURE;
    }

    int ch;

    while ((ch = fgetc(fp)) != EOF) {

        if ((ch == '\r') || (ch == '\n')) {
            // CR + LF ausgeben
            putchar('\r');
            putchar('\n');
            fflush(stdout);
            usleep(LINE_DELAY_US);
        } else {
            putchar(ch);
            fflush(stdout);
            usleep(CHAR_DELAY_US);
        }
    }

    fclose(fp);
    return EXIT_SUCCESS;
}
