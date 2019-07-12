/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates_stack.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwidaha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:25:02 by nwidaha           #+#    #+#             */
/*   Updated: 2019/06/18 18:22:10 by nwidaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include "libft.h"
#include <errors.h>

int				get_index_element(int x, int y, int width)
{
	return (y * width + x);
}

void			push(t_coordinate **coordinates, t_coordinate *new)
{
	if (coordinates)
	{
		if (new)
		{
			new->next = *coordinates;
		}
		*coordinates = new;
	}
}

t_coordinate	*pop(t_coordinate **coordinates)
{
	t_coordinate *top;

	top = NULL;
	if (coordinates && *coordinates)
	{
		top = *coordinates;
		*coordinates = (*coordinates)->next;
	}
	return (top);
}

void			create_stack(t_coordinate **coordinates, t_map *map)
{
	t_coordinate	*coordinate;
	ssize_t			i;
	size_t			array_size;

	array_size = map->width * map->height * sizeof(int);
	if (!(map->coordinates_array = (int *)ft_memalloc(array_size)))
		print_error(ERROR_CONVERSION_TO_ARR);
	if (!(map->colors_array = (int *)ft_memalloc(array_size)))
		print_error(ERROR_CONVERSION_TO_ARR);
	i = map->width * map->height - 1;
	while ((coordinate = pop(coordinates)) && i >= 0)
	{
		map->coordinates_array[i] = coordinate->z;
		map->colors_array[i] = coordinate->color;
		if (coordinate->z > map->max_z)
			map->max_z = coordinate->z;
		if (coordinate->z < map->min_z)
			map->min_z = coordinate->z;
		i--;
		free(coordinate);
	}
	map->range_z = map->max_z - map->min_z;
}
