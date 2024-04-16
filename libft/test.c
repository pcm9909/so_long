#include "./libft/libft.h"
#include <stdio.h>

int main()
{
    char *a;
    a = ft_strchr("abcd\0", 'b');
    printf("%s", a);
}