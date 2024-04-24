#include "so_long.h"

void *ft_realloc(void *ptr, size_t size)
{
    void *new_ptr;

    if (ptr == NULL)
        return (malloc(size));
    if (!size)
        return (ptr);
    new_ptr = malloc(size);
    ft_memcpy(new_ptr, ptr, size);
    free(ptr);
    return (new_ptr);
}

void    read_map(t_vars *p, char *filename)
{
    int fd;
    char *line;

    p->height = 0;
    fd = open(filename, O_RDONLY);
    if (fd == -1) 
        exit_error("File does not exist\n");
    p-> map = (char **)malloc(sizeof(char *));
    while ((line = get_next_line(fd)) > 0)
    {
        p->map[p->height] = ft_strdup(line);
        free(line);
        p->height++;
        p->map = (char **)ft_realloc(p->map, (p->height + 1) * sizeof(char *));
    }
    p->map[p->height] = NULL;
}
