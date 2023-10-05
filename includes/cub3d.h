/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:43:06 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/05 13:11:57 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

// Engine
# define TS 64
# define PI 3.14159265359
# define WIN_HEIGHT 920
# define WIN_WIDTH 1280
# define TRUE 1
# define FALSE 0

// Map
# define TSMAP 50
# define PM_SIZE 20

typedef struct s_line
{
	int		pixels;
	double	dx;
	double	dy;
	double	end_x;
	double	end_y;
	double	s_x;
	double	s_y;
}	t_line;

typedef struct s_player
{
	mlx_image_t	*img_map;
	mlx_image_t	*ray_img;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		angle;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		x;
	int		y;
	int		height;
	int		width;
	int		height_px;
	int		width_px;
}	t_map;

typedef struct s_cub
{
	mlx_t			*mlx;
	mlx_texture_t	*texture;
	t_player		*player;
	t_map			*map;
	int				game_on;
}	t_cub;

// minimap
void		minimap(t_cub *cub);
void		draw_minimap(t_map *map, mlx_t *mlx, mlx_image_t *img);
mlx_image_t	*create_img_full(int size, mlx_t *mlx, uint64_t color);

// player
void		player_update(t_cub *cub);
int			entity_hitbox(char **map, int x, int y);
void		init_player(t_cub *cub);
void		find_spawn(char **map, int *x, int *y);
void		draw_direction(t_cub *cub);

// player_movement
void		move_forward(t_cub *cub);
void		move_backward(t_cub *cub);
void		move_left(t_cub *cub);
void		move_right(t_cub *cub);

// minimap_utils
void		print_char_map(char **map);

// simple_parsing
int			selected_fd(char *map);
char		**array_join(char **array, char *line);
char		**parsing(char *map);
int			check_ext(char	*file_name, char	*ext);
int			file_exist(char	*file_name);
// map_parsing
char		*element_type(char *line);

// parsing_utils
int			is_digit(char c);
int			is_alpha(char c);
int			is_space(char c);

#endif