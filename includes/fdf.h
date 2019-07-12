/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwidaha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 13:44:55 by nwidaha           #+#    #+#             */
/*   Updated: 2019/06/20 13:58:59 by nwidaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH					1400
# define HEIGHT					1400
# define MENU_DIALOGUE_WIDTH	250

typedef	enum
{
	ISOMETRIC,
	PARALLEL
}	t_projection;

typedef	enum
{
	false,
	true
}	t_bool;

typedef	struct	s_coordinate
{
	int						z;
	int						color;
	struct s_coordinate		*next;
}				t_coordinate;

typedef	struct	s_point
{
	int						x;
	int						y;
	int						z;
	int						color;
}				t_point;

typedef	struct	s_camera
{
	t_projection			projection;
	int						zoom;
	double					alpha;
	double					beta;
	double					gamma;
	float					z_divisor;
	int						offset_x;
	int						offset_y;
}				t_camera;

typedef	struct	s_map
{
	int						width;
	int						height;
	int						*coordinates_array;
	int						*colors_array;
	int						min_z;
	int						max_z;
	int						range_z;
}				t_map;

typedef	struct	s_environment
{
	void					*mlx;
	void					*window;
	void					*img;
	char					*data_address;
	int						bits_per_pixel;
	int						size_line;
	int						endian;
	t_camera				*camera;
	t_map					*map;
}				t_environment;

void			print_error(char *string);
t_map			*create_map(void);
t_environment	*create_fdf_environment(t_map *map);
t_camera		*create_camera(t_environment *fdf);
void			create(t_map *map, t_environment *fdf);
int				escape_screen(void *param);
int				handle_key(int key, void *param);
void			setup(t_environment *fdf);
void			print_error(char *string);
t_point			project(t_point p, t_environment *fdf);
void			change_projection_type(int key, t_environment *fdf);
int				get_index_element(int x, int y, int width);
void			push(t_coordinate **coordinates, t_coordinate *new);
t_coordinate	*pop(t_coordinate **coordinates);
void			create_stack(t_coordinate **coordinates, t_map *map);
t_bool			ft_isnumber(char *str, int base);
int				ft_atoi_base(const char *str, int base);
t_point			new_point(int x, int y, t_map *map);
int				read_map_by_line(const int fd, t_coordinate **coordinates_stack,
								t_map *map);
double			percentage(int start, int end, int current);
int				get_default(int z, t_map *map);
int				get_light(int start, int end, double percentage);
int				get_color(t_point current, t_point start, t_point end,
								t_point delta);

#endif
