/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:00:31 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/06 01:35:30 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cub *cub)
{
	mlx_t	*mlx;

	mlx = cub->mlx;
	cub->player->pos_x += cub->player->dir_x * SPEED;
	cub->player->pos_y += cub->player->dir_y * SPEED;
	if (mlx_is_key_down(mlx, MLX_KEY_W) && !mlx_is_key_down(mlx, MLX_KEY_S)
		&& !mlx_is_key_down(mlx, MLX_KEY_A) && !mlx_is_key_down(mlx, MLX_KEY_D)
		&& !mlx_is_key_down(mlx, MLX_KEY_LEFT)
		&& !mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		draw_rays(cub);
}

void	move_backward(t_cub *cub)
{
	mlx_t	*mlx;

	mlx = cub->mlx;
	cub->player->pos_x -= cub->player->dir_x * SPEED;
	cub->player->pos_y -= cub->player->dir_y * SPEED;
	if (!mlx_is_key_down(mlx, MLX_KEY_W) && mlx_is_key_down(mlx, MLX_KEY_S)
		&& !mlx_is_key_down(mlx, MLX_KEY_A) && !mlx_is_key_down(mlx, MLX_KEY_D)
		&& !mlx_is_key_down(mlx, MLX_KEY_LEFT)
		&& !mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		draw_rays(cub);
}

void	move_left(t_cub *cub)
{
	mlx_t	*mlx;

	mlx = cub->mlx;
	cub->player->pos_x += (cos(cub->player->angle - (2 * PI / 4))) * SPEED_SIDE;
	cub->player->pos_y += (sin(cub->player->angle - (2 * PI / 4))) * SPEED_SIDE;
	if (!mlx_is_key_down(mlx, MLX_KEY_W) && !mlx_is_key_down(mlx, MLX_KEY_S)
		&& mlx_is_key_down(mlx, MLX_KEY_A) && !mlx_is_key_down(mlx, MLX_KEY_D)
		&& !mlx_is_key_down(mlx, MLX_KEY_LEFT)
		&& !mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		draw_rays(cub);
}

void	move_right(t_cub *cub)
{
	mlx_t	*mlx;

	mlx = cub->mlx;
	cub->player->pos_x -= (cos(cub->player->angle - (2 * PI / 4))) * SPEED_SIDE;
	cub->player->pos_y -= (sin(cub->player->angle - (2 * PI / 4))) * SPEED_SIDE;
	if (!mlx_is_key_down(mlx, MLX_KEY_W) && !mlx_is_key_down(mlx, MLX_KEY_S)
		&& !mlx_is_key_down(mlx, MLX_KEY_A) && mlx_is_key_down(mlx, MLX_KEY_D)
		&& !mlx_is_key_down(mlx, MLX_KEY_LEFT)
		&& !mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		draw_rays(cub);
}
