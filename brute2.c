/*--- brute1.c ------------------------------ Listing 4-1 -----
 * Simple brute search with no optimization.
 * Easy to write but slow to execute.
 *
 *  #define DRIVER to have a command-line version compiled.
 *-----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define driver 1    /* if defined, runs test routine */

/*---------------------------------------------------
 * Search for string in text. Return pointer to first
 * instance of string, or NULL at end of text.
 *-------------------------------------------------*/
char * BruteSearch(const char * text, const char * string)
{
    int len = strlen(string);

    /* the table. "static" assures its initialized to '\0's */
    static char lookup[UCHAR_MAX + 1];
    lookup[0] = 1;  /* EOT process */
    lookup[(unsigned char)(*string)] = 2;   /* a match */

    for ( ; ; text++)
    {
        switch(lookup[(unsigned char)(*text)])
        {
            case 0:
                break;      /* it's not EOF or a match */
            case 1:
                return (NULL);      /* EOF */
            case 2:
                if (strncmp(string + 1, text + 1, len - 1) == 0)
                    return ((char *)text);      /* a match */
                break;
            default:    /* good coding to include default */
                break;
        }
    }

}

/*-------------------------------------------------------------
 * The main driver: accepts a string to search for and 
 * a filename from the command line. It then searches
 * through the first 10,000 chars of the file and prints
 * the first 30 characters of the first match, if any,
 * and then quits.
 *------------------------------------------------------------*/
#ifdef DRIVER

int main(int argc, char * argv[])
{
    char *search_for, *filename,
        *site;
    FILE *fin;
    char *buffer;

    if (argc < 3)
    {
        fprintf(stderr, "Error! Usage: BRUTE1 string filename\n");
        return (EXIT_FAILURE);
    }
    else
    {
        search_for = argv[1];
        filename = argv[2];
    }

    if ((fin = fopen(filename, "rt")) == NULL)
    {
        fprintf(stderr, "Error: Cannot open %s\n", filename);
        return (EXIT_FAILURE);
    }
    
    buffer = (char *)calloc(1, 10001);
    if (buffer = NULL)
    {
        fprintf(stderr, "Error! Cannot allocate buffer space.\n");
        return (EXIT_FAILURE);
    }

    fread(buffer, 10000, 1, fin);

    site = BruteSearch(buffer, search_for);

    if (site == NULL)
        printf("%s NOT found\n", argv[1]);
    else
    {
        char solution[31];
        strncpy(solution, site, 30);
        solution[30] = '\0';

        printf("\nFound:\n%s\n", solution);
    }

    fclose(fin);
    return (EXIT_SUCCESS);
}
#endif
