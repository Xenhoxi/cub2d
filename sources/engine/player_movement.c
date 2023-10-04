/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:00:31 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/04 19:45:55 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cub *cub)
{
	cub->player->pos_x += cub->player->dir_x * 2;
	cub->player->pos_y -= cub->player->dir_y * 2;
	draw_line(cub);
}

void	move_backward(t_cub *cub)
{
	cub->player->pos_x -= cub->player->dir_x * 2;
	cub->player->pos_y += cub->player->dir_y * 2;
	draw_line(cub);
}

void	move_left(t_cub *cub)
{
	(void) cub;
}

void	move_right(t_cub *cub)
{
	(void) cub;
}
