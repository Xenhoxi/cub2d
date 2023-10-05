/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:00:33 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/05 16:13:23 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scale_for_ray(t_cub *cub, double new_angle, t_line *line)
{
	line->end_x = cub->player->pos_x + (cos(new_angle) * TSMAP);
	line->end_y = cub->player->pos_y + (sin(new_angle) * TSMAP);
	line->s_x = cub->player->pos_x;
	line->s_y = cub->player->pos_y;
	line->dx = line->end_x - cub->player->pos_x;
	line->dy = line->end_y - cub->player->pos_y;
	line->pixels = sqrt((line->dx * line->dx) + (line->dy * line->dy));
	line->dx_p /= line->pixels;
	line->dy_p /= line->pixels;
// 	if (cub->player->ray_img)
// 		mlx_delete_image(cub->mlx, cub->player->ray_img);
// 	cub->player->ray_img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
// 	while (line->pixels > 0 && line->s_x > 0 && line->s_y > 0)
// 	{
// 		mlx_put_pixel(cub->player->ray_img, line->s_x, line->s_y, 0xFF0000FF);
// 		line->s_x += line->dx_p;
// 		line->s_y += line->dy_p;
// 		line->pixels--;
// 	}
// 	mlx_image_to_window(cub->mlx, cub->player->ray_img, 0, 0);
}

void	draw_rays(t_cub *cub)
{
	t_line	line;
	double	actual;
	double	end;

	actual = cub->player->angle; //cub->player->angle - (PI / 6)
	end = cub->player->angle + (PI / 6);
	while (actual < end)
	{
		scale_for_ray(cub, actual, &line);
		actual += (PI / 6);
	}
}
