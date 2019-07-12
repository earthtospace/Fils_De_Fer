/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwidaha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:43:12 by nwidaha           #+#    #+#             */
/*   Updated: 2019/06/18 18:03:32 by nwidaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "colors.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <libft.h>

double	percentage(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int		get_default(int z, t_map *map)
{
	double	percent;

	percent = percentage(map->min_z, map->max_z, z);
	if (percent < 0.2)
		return (COLOR_LIME);
	else if (percent < 0.4)
		return (COLOR_RACE_CAR_RED);
	else if (percent < 0.6)
		return (COLOR_ORANGE);
	else if (percent < 0.8)
		return (COLOR_LIGHT_PURPLE);
	else
		return (COLOR_ELECTRIC);
}

int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int		get_color(t_point current,
		t_point start, t_point end, t_point delta)
{
	int		red;
	int		green;
	int		blue;
	double	percent;

	if (current.color == end.color)
		return (current.color);
	if (delta.x > delta.y)
		percent = percentage(start.x, end.x, current.x);
	else
		percent = percentage(start.y, end.y, current.y);
	red = get_light((start.color >> 16) & 0xFF,
					(end.color >> 16) & 0xFF,
					percent);
	green = get_light((start.color >> 8) & 0xFF,
					(end.color >> 8) & 0xFF,
					percent);
	blue = get_light(start.color & 0xFF,
					end.color & 0xFF,
					percent);
	return ((red << 16) | (green << 8) | blue);
}
