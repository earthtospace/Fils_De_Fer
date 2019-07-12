/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwidaha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 16:36:50 by nwidaha           #+#    #+#             */
/*   Updated: 2019/06/18 21:19:58 by nwidaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"
#include "colors.h"

static	void	create_pixel(t_environment *fdf,
		int x, int y, int color)
{
	int	i;

	if (x > MENU_DIALOGUE_WIDTH && x < WIDTH && y > 0 && y < HEIGHT)
	{
		i = (x * fdf->bits_per_pixel / 8) + (y * fdf->size_line);
		fdf->data_address[i] = color;
		fdf->data_address[++i] = color >> 8;
		fdf->data_address[++i] = color >> 16;
	}
}

static	void	create_line(t_point f, t_point s, t_environment *fdf)
{
	t_point		delta;
	t_point		sign;
	t_point		cur;
	int			error[2];

	delta.x = FT_ABS(s.x - f.x);
	delta.y = FT_ABS(s.y - f.y);
	sign.x = f.x < s.x ? 1 : -1;
	sign.y = f.y < s.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	cur = f;
	while (cur.x != s.x || cur.y != s.y)
	{
		create_pixel(fdf, cur.x, cur.y, get_color(cur, f, s, delta));
		if ((error[1] = error[0] * 2) > -delta.y)
		{
			error[0] -= delta.y;
			cur.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

static	void	create_background(t_environment *fdf)
{
	int *image;
	int i;

	ft_bzero(fdf->data_address, WIDTH * HEIGHT * (fdf->bits_per_pixel / 8));
	image = (int *)(fdf->data_address);
	i = 0;
	while (i < HEIGHT * WIDTH)
	{
		image[i] = (i % WIDTH < MENU_DIALOGUE_WIDTH)
								? MENU_BACKGROUND : BACKGROUND;
		i++;
	}
}

void			create(t_map *map, t_environment *fdf)
{
	int x;
	int y;

	create_background(fdf);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x != fdf->map->width - 1)
				create_line(project(new_point(x, y, map), fdf),
						project(new_point(x + 1, y, map), fdf), fdf);
			if (y != fdf->map->height - 1)
				create_line(project(new_point(x, y, map), fdf),
						project(new_point(x, y + 1, map), fdf), fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
	mlx_string_put(fdf->mlx, fdf->window, 30, y += 20, TXT_CLR, "How to Use:");
	mlx_string_put(fdf->mlx, fdf->window, 30, y += 30, TXT_CLR, "Projection:");
	mlx_string_put(fdf->mlx, fdf->window, 30, y += 25, TXT_CLR, "Iso - I");
	mlx_string_put(fdf->mlx, fdf->window, 30, y += 25, TXT_CLR, "Paralel - P");
}
