/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwidaha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 16:36:38 by nwidaha           #+#    #+#             */
/*   Updated: 2019/06/18 18:11:29 by nwidaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdlib.h>
#include <keys.h>
#include <stdio.h>
#include <errno.h>
#include "libft.h"

int		escape_screen(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int		handle_key(int key, void *param)
{
	t_environment *fdf;

	fdf = (t_environment *)param;
	if (key == KEY_ESCAPE)
		exit(0);
	else if (key == KEY_PARALLEL || key == KEY_ISO)
		change_projection_type(key, fdf);
	return (0);
}

void	setup(t_environment *fdf)
{
	mlx_hook(fdf->window, 2, 0, handle_key, fdf);
	mlx_hook(fdf->window, 17, 0, escape_screen, fdf);
}

void	print_error(char *string)
{
	if (errno == 0)
		ft_putendl_fd(string, 2);
	else
		perror(string);
	exit(1);
}
