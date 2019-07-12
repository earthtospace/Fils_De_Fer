/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwidaha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:09:19 by nwidaha           #+#    #+#             */
/*   Updated: 2019/06/18 21:26:17 by nwidaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "math.h"
#include "keys.h"

static	void	isometric(int *x, int *y, int z)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

t_point			project(t_point p, t_environment *fdf)
{
	p.x *= fdf->camera->zoom;
	p.y *= fdf->camera->zoom;
	p.z *= fdf->camera->zoom / fdf->camera->z_divisor;
	p.x -= (fdf->map->width * fdf->camera->zoom) / 2;
	p.y -= (fdf->map->height * fdf->camera->zoom) / 2;
	if (fdf->camera->projection == ISOMETRIC)
	{
		isometric(&p.x, &p.y, p.z);
	}
	p.x += (WIDTH - MENU_DIALOGUE_WIDTH) / 2 +
		fdf->camera->offset_x + MENU_DIALOGUE_WIDTH;
	p.y += (HEIGHT + fdf->map->height * fdf->camera->zoom) / 2 +
		fdf->camera->offset_y;
	return (p);
}

void			change_projection_type(int key, t_environment *fdf)
{
	fdf->camera->alpha = 0;
	fdf->camera->beta = 0;
	fdf->camera->gamma = 0;
	if (key == KEY_PARALLEL)
		fdf->camera->projection = PARALLEL;
	else if (key == KEY_ISO)
	{
		fdf->camera->projection = ISOMETRIC;
	}
	create(fdf->map, fdf);
}
