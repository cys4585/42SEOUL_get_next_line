#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd1 = open("file1", O_RDONLY);
    // int     fd2 = open("file2", O_RDONLY);
    // int     fd3 = open("file3", O_RDONLY);

    char    *str1;
    // char    *str2;
    // char    *str3;

    while (1)
    {
        str1 = get_next_line(fd1);
        // str2 = get_next_line(fd2);
        // str3 = get_next_line(fd3);
        // if (str1 == NULL && str2 == NULL && str3 == NULL)
        if (str1 == NULL)
            break ;
        printf("#main while#\nstr1:%s\n#main while#\n\n", str1);
        // printf("str2:%s\n", str2);
        // printf("str3:%s\n", str3);
    }
    return (0);
}