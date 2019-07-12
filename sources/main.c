/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwidaha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 12:49:09 by nwidaha           #+#    #+#             */
/*   Updated: 2019/06/20 13:31:51 by nwidaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <mlx.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errors.h>
#include <errno.h>
#include <colors.h>

int				main(int argc, char **argv)
{
	int				y;
	int				fd;
	t_environment	*fdf_environment;
	t_map			*map;
	t_coordinate	*coordinates;

	y = 0;
	errno = 0;
	coordinates = NULL;
	if (argc == 2)
	{
		if (!((fd = open(argv[1], O_RDONLY)) >= 0))
			print_error(ERROR_MAP);
		map = create_map();
		if (read_map_by_line(fd, &coordinates, map) == -1)
			print_error(ERROR_MAP_READING);
		fdf_environment = create_fdf_environment(map);
		create_stack(&coordinates, map);
		fdf_environment->camera = create_camera(fdf_environment);
		create(fdf_environment->map, fdf_environment);
		setup(fdf_environment);
		mlx_loop(fdf_environment->mlx);
	}
	print_error(ERROR_USAGE);
	return (0);
}

t_map			*create_map(void)
{
	t_map	*map;

	if (!(map = (t_map *)ft_memalloc(sizeof(t_map))))
		print_error(ERROR_MAP_INIT);
	map->width = 0;
	map->height = 0;
	map->coordinates_array = NULL;
	map->colors_array = NULL;
	map->min_z = FT_INT_MAX;
	map->max_z = FT_INT_MIN;
	map->range_z = 0;
	return (map);
}

t_environment	*create_fdf_environment(t_map *map)
{
	t_environment	*fdf_e;

	if (!(fdf_e = (t_environment *)ft_memalloc(sizeof(t_environment))))
		print_error(ERROR_FDF_INIT);
	if (!(fdf_e->mlx = mlx_init()))
		print_error(ERROR_FDF_INIT);
	if (!(fdf_e->window = mlx_new_window(fdf_e->mlx, WIDTH, HEIGHT, "FdF")))
		print_error(ERROR_FDF_INIT);
	if (!(fdf_e->img = mlx_new_image(fdf_e->mlx, WIDTH, HEIGHT)))
		print_error(ERROR_FDF_INIT);
	fdf_e->data_address = mlx_get_data_addr(fdf_e->img,
			&(fdf_e->bits_per_pixel), &(fdf_e->size_line), &(fdf_e->endian));
	fdf_e->map = map;
	return (fdf_e);
}

t_camera		*create_camera(t_environment *fdf)
{
	t_camera *camera;

	if (!(camera = (t_camera *)ft_memalloc(sizeof(t_camera))))
		print_error(ERROR_CAMERA_INIT);
	camera->zoom = FT_MIN((WIDTH - MENU_DIALOGUE_WIDTH) / fdf->map->width / 2,
			HEIGHT / fdf->map->height / 2);
	camera->alpha = 0;
	camera->beta = 0;
	camera->gamma = 0;
	camera->z_divisor = 1;
	camera->offset_x = 0;
	camera->offset_y = 0;
	return (camera);
}
