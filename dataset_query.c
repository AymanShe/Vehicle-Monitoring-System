#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void delay(int seconds)
{
    int milli_sec = 1000 * seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_sec)
    {
        // wait
    }
}

const char *getfield(char *line, int num, int delayValue)
{
    const char *tok;
    for (tok = strtok(line, ";"); tok && *tok; tok = strtok(NULL, ";\n"))
    {
        if (!--num)
        {
            delay(delayValue);
            return tok;
        }
    }
    return NULL;
}

int main()
{
    FILE *stream = fopen("C:\\Users\\Gabriel Karras\\Documents\\COEN320\\dataset.csv", "r");

    char line[1024];
    while (fgets(line, 1024, stream))
    {
        char *tmp = strdup(line);
        printf("My field would be %s\n", getfield(tmp, 3, 1));
        free(tmp);
    }

    return 0;
}
