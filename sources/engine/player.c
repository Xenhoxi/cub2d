/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:09:37 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/04 19:58:20 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_rotation(t_cub *cub)
{
	mlx_t	*mlx;

	mlx = cub->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		cub->player->angle -= 0.05;
		if (cub->player->angle < 0)
			cub->player->angle = 2 * PI - 0.05;
		cub->player->dir_x = cos(cub->player->angle);
		cub->player->dir_y = sin(cub->player->angle);
		draw_line(cub);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		cub->player->angle += 0.05;
		if (cub->player->angle > 2 * PI)
			cub->player->angle = 0.05;
		cub->player->dir_x = cos(cub->player->angle);
		cub->player->dir_y = sin(cub->player->angle);
		draw_line(cub);
	}
	printf("dir_x = %f, dir_y = %f\n", cub->player->dir_x, cub->player->dir_y);
	printf("angle = %f\n", cub->player->angle);
}

void	player_update(t_cub *cub)
{
	mlx_t	*mlx;

	mlx = cub->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_left(cub);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_right(cub);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_forward(cub);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move_backward(cub);
	player_rotation(cub);
}

int	entity_hitbox(char **map, int x, int y)
{
	int	x_map;
	int	y_map;

	x_map = x / TSMAP;
	y_map = y / TSMAP;
	printf("x = %d | y = %d\n", x_map, y_map);
	printf("map[] = %c\n", map[y_map][x_map]);
	if (map[y_map][x_map] == '1')
		return (1);
	return (0);
}

void	draw_line(t_cub *cub)
{
	int				i;
	int				pixels;
	double			dx;
	double			dy;
	double			endX = cub->player->pos_x + (cub->player->dir_x * 10);
	double			endY = cub->player->pos_y + (cub->player->dir_y * 10);
	double			pX = cub->player->pos_y;
	double			pY = cub->player->pos_x;

	i = 0;
	dx = endX - cub->player->pos_x;
	dy = endY - cub->player->pos_y;
	pixels = sqrt((dx * dx) + (dy * dy));
	dx /= pixels;
	dy /= pixels;
	if (cub->player->ray_img)
		mlx_delete_image(cub->mlx, cub->player->ray_img);
	cub->player->ray_img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	while (pixels > 0 && pX > 0 && pY > 0)
	{
		mlx_put_pixel(cub->player->ray_img, pY, pX, 0x00FFFFFF);
		pX += dx;
		pY += dy;
		pixels--;
	}
	mlx_image_to_window(cub->mlx, cub->player->ray_img, 0, 0);
}

void	init_player(t_cub *cub)
{
	int			x;
	int			y;
	t_player	*player;

	find_spawn(cub->map->map, &y, &x);
	player = cub->player;
	player->pos_x = (x * TSMAP) + TSMAP / 2 - PM_SIZE / 2;
	player->pos_y = (y * TSMAP) + TSMAP / 2 - PM_SIZE / 2;
	player->dir_x = -1;
	player->dir_y = 0;
	printf("Player initialized\n");
}

void	find_spawn(char **map, int *x, int *y)
{
	*x = 0;
	*y = 0;
	while (map[*x])
	{
		while (map[*x][*y])
		{
			if (map[*x][*y] == 'N' || map[*x][*y] == 'E'
				|| map[*x][*y] == 'W' || map[*x][*y] == 'S')
				return ;
			(*y)++;
		}
		*y = 0;
		(*x)++;
	}
}
