/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:58:45 by chunpark          #+#    #+#             */
/*   Updated: 2024/04/25 18:15:22 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	min_size;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
		return (NULL);
	new_ptr = malloc(new_size);
	if (new_ptr)
	{
		if (old_size < new_size)
			min_size = old_size;
		else
			min_size = new_size;
		ft_memcpy(new_ptr, ptr, min_size);
		free(ptr);
	}
	return (new_ptr);
}

void	read_map(t_vars *p, char *filename)
{
	char	*line;
	int		fd;

	p->height = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_error("File does not exist\n");
	p->map = (char **)malloc(sizeof(char *));
	line = get_next_line(fd);
	while (line > 0)
	{
		p->map[p->height] = ft_strdup(line);
		free(line);
		p->height++;
		p->map = (char **)ft_realloc(p->map, \
				p->height * sizeof(char *), (p->height + 1) * sizeof(char *));
		line = get_next_line(fd);
	}
	p->map[p->height] = NULL;
}
