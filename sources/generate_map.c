/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwidaha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:21:34 by nwidaha           #+#    #+#             */
/*   Updated: 2019/06/18 21:42:00 by nwidaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"
#include "errors.h"
#include <stdlib.h>

t_point					new_point(int x, int y, t_map *map)
{
	t_point	point;
	int		index;

	index = get_index_element(x, y, map->width);
	point.x = x;
	point.y = y;
	point.z = map->coordinates_array[index];
	point.color = (map->colors_array[index] == -1) ?
		get_default(point.z, map) : map->colors_array[index];
	return (point);
}

static	void			free_str_split_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

static	t_coordinate	*new_coordinates(char *string)
{
	t_coordinate	*coordinate;
	char			**all_coords;

	if (!(coordinate = (t_coordinate *)ft_memalloc(sizeof(t_coordinate))))
		print_error(ERROR_MAP_READING);
	if (!(all_coords = ft_strsplit(string, ',')))
		print_error(ERROR_MAP_READING);
	if (!ft_isnumber(all_coords[0], 10))
		print_error(ERROR_MAP_READING);
	if (all_coords[1] && !ft_isnumber(all_coords[1], 16))
		print_error(ERROR_MAP_READING);
	coordinate->z = ft_atoi(all_coords[0]);
	coordinate->color = all_coords[1] ? ft_atoi_base(all_coords[1], 16) : -1;
	coordinate->next = NULL;
	free_str_split_array(all_coords);
	return (coordinate);
}

static	void			parse(char **coordinates_line,
								t_coordinate **coordinates_stack, t_map *map)
{
	int width;

	width = 0;
	while (*coordinates_line)
	{
		push(coordinates_stack, new_coordinates(*(coordinates_line++)));
		width++;
	}
	if (map->height == 0)
		map->width = width;
	else if (map->width != width)
		print_error(ERROR_MAP);
}

int						read_map_by_line(const int fd,
										t_coordinate **coordinates_stack,
										t_map *map)
{
	char	*line;
	int		result;
	char	**coordinates_line;

	while ((result = get_next_line(fd, &line)) == 1)
	{
		if (!(coordinates_line = ft_strsplit(line, ' ')))
			print_error(ERROR_MAP_READING);
		parse(coordinates_line, coordinates_stack, map);
		free_str_split_array(coordinates_line);
		ft_strdel(&line);
		map->height++;
	}
	if (!(*coordinates_stack))
		print_error(ERROR_MAP);
	return (result);
}
