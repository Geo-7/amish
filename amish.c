#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

#define PROJECT_NAME "amish"
#define AMISH_READ_BUFFER 10
void amish_loop(void);
char *amish_line(void);
void amish_parse(char *);
void ls(void);
int main(int argc, char **argv)
{
    if (argc != 1)
    {
        printf("%s takes no arguments.\n", argv[0]);
        return 1;
    }
    printf("Amish shell started %s.\n", PROJECT_NAME);
    amish_loop();
    return 0;
}

void amish_loop(void)
{
    char *line;

    while (1)
    {
        printf("#>");
        line = amish_line();
        amish_parse(line);
    }
}

void amish_parse(char *line)
{
    if (strcmp(line, "ls") == 0)
    {
        ls();
    }
    else
    {
        printf("Command not found %s\n" , line);
    }
}
char *amish_line(void)
{
    char c;
    int buffsize = AMISH_READ_BUFFER;
    char *buffer = malloc(buffsize * sizeof(char));
    int position = 0;
    while (1)
    {
        c = getchar();
        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;
        if(position>= buffsize){
            buffsize += AMISH_READ_BUFFER;
            buffer = realloc(buffer , buffsize);
        }
    }
}

void ls(void)
{
    DIR *cd;
    struct dirent *cfiles;
    cd = opendir("./");
    while ((cfiles = readdir(cd)))
        puts(cfiles->d_name);
    (void)closedir(cd);
}