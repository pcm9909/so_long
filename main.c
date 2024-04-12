#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd;
    char *line;
    int height = 0;
    int width = 0;
    char *join;
    char **map;
    if (argc == 2)
    {
        if (ft_strncmp(ft_strchr(argv[1], '.'),".ber",4) == 0)
        {
           fd = open(argv[1], O_RDONLY);
           line = get_next_line(fd);
           width = ft_strlen(line);
           while (line)
           {
                line = get_next_line(fd);
                height++;
           }
           printf("h %d w %d\n", height, width);
        }
    }
    else 
        printf("input Err\n");
}