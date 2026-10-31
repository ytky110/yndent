#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "1.0"
#define DEFAULT_N 4

void indent(int n, int opt_tab);
int parse_arg(int argc, char **argv, int *opt_tab);
void help(void);
void version(void);

int main(int argc, char **argv)
{
    int i, n;
    int c, c2;
    int opt_tab = 0;

    n = parse_arg(argc, argv, &opt_tab);
    if (n == -1)
        return 0;

    if ((c = getchar()) != EOF)
        indent(n, opt_tab);
        ungetc(c, stdin);

    while ((c = getchar()) != EOF) {
        putchar(c);
        if (c != '\n')
            continue;

        c2 = getchar();
        if (c2 == EOF)
            break;
        if (ungetc(c2, stdin) == EOF)
            break;
        indent(n, opt_tab);
    }

    return 0;
}

void indent(int n, int opt_tab)
{
    int i;

    for (i = n; i; i--)
        putchar(opt_tab ? '\t' : ' ');
}

int parse_arg(int argc, char **argv, int *opt_tab)
{
    int i, n = DEFAULT_N;

    if (argc < 2)
        return n;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0
        || strcmp(argv[i], "-h") == 0) {
            help();
            return -1;
        } else if (strcmp(argv[i], "--version") == 0
        || strcmp(argv[i], "-v") == 0) {
            version();
            return -1;
        } else if (strcmp(argv[i], "--tab") == 0
        || strcmp(argv[i], "-t") == 0) {
            *opt_tab = 1;
        } else if (strcmp(argv[i], "--space") == 0
        || strcmp(argv[i], "-s") == 0) {
            *opt_tab = 0;
        } else {
            n = atoi(argv[i]);
        }
    }

    return n;
}

void help(void)
{
    printf(
    "usage: yndent [OPTION] [NUM]\n"
    "   or  yndent (--help|--version)\n"
    "\nIndent input of NUM (default 4 space)\n"
    "\nOptions:\n"
    "    -s  --space     use space instead tab (default)\n"
    "    -t  --tab       use tab instead space\n"
    );
}

void version(void)
{
    printf(
    "yndent %s\n", VERSION
    );
}
