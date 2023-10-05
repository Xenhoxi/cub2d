/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:00:33 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/06 01:32:28 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scale_for_ray(t_cub *cub, double new_angle, t_line *line)
{
	line->img = NULL;
	line->end_x = cub->player->pos_x + (cos(new_angle) * TSMAP);
	line->end_y = cub->player->pos_y + (sin(new_angle) * TSMAP);
	line->s_x = cub->player->pos_x;
	line->s_y = cub->player->pos_y;
	line->dx = line->end_x - cub->player->pos_x;
	line->dy = line->end_y - cub->player->pos_y;
	line->pixels = sqrt((line->dx * line->dx) + (line->dy * line->dy));
	line->dx_p /= line->pixels;
	line->dy_p /= line->pixels;
	line->sx = sqrt(1 + pow(line->dy / line->dx, 2));
	line->sy = sqrt(1 + pow(line->dx / line->dy, 2));
	printf("\r\33[2Kangle = %f sx = %f sy = %f", cub->player->angle,
		line->sx, line->sy);
	fflush(stdout);
}

// Offset sur la premiere case + setup case dans laquelle je suis
void	calcul_offset(t_cub *cub, t_line *line)
{
	double	offset_x;
	double	offset_y;

	offset_x = ((int)cub->player->pos_x) % TSMAP;
	offset_y = ((int)cub->player->pos_y) % TSMAP;
	offset_x = (1 * offset_x) / TSMAP;
	offset_y = 1 - ((1 * offset_y) / TSMAP);
	line->lenght_x = offset_x * line->sx * TSMAP;
	line->lenght_y = offset_y * line->sy * TSMAP;

	if (cub->player->angle >= PI && cub->player->angle <= PI)
		line->map_y = (((int)cub->player->pos_y) / TSMAP) - 1;
	else
		line->map_y = (((int)cub->player->pos_y) / TSMAP) + 1;
	if (cub->player->angle >= PI / 2 && cub->player->angle <= (3 * PI) / 2)
		line->map_x = (((int)cub->player->pos_x) / TSMAP) - 1;
	else
		line->map_x = (((int)cub->player->pos_x) / TSMAP) + 1;
}

void	draw_rays(t_cub *cub)
{
	t_line		line;
	double		actual;
	double		end;

	actual = cub->player->angle - (PI / 6);
	end = cub->player->angle + (PI / 6);
	while (actual < end)
	{
		scale_for_ray(cub, actual, &line);
		calcul_offset(cub, &line);
		while (1)
		{
			if (line.lenght_x < line.lenght_y)
			{
				if (cub->player->angle >= PI / 2 && cub->player->angle <= (3 * PI) / 2)
					line.map_x--;
				else
					line.map_x++;
			}
			else
			{
				if (cub->player->angle >= PI && cub->player->angle <= PI)
					line.map_y--;
				else
					line.map_y++;
			}
			if (line.lenght_x < line.lenght_y)
				line.lenght_x += line.sx;
			else
				line.lenght_y += line.sy;
			if (cub->map->map[line.map_y][line.map_x] == '1')
			{
				line.end_x = cub->player->pos_x + cos(actual) * line.lenght_x;
				line.end_y = cub->player->pos_y + sin(actual) * line.lenght_y;
				draw_rayline(cub, &line);
				break ;
			}
		}
		actual += (PI / 12);
	}
}

void	draw_rayline(t_cub *cub, t_line *line)
{
	line->pixels = sqrt((line->dx * line->dx) + (line->dy * line->dy));
	line->dx_p = line->dx;
	line->dy_p = line->dy;
	line->dx_p /= line->pixels;
	line->dy_p /= line->pixels;
	if (line->img)
		mlx_delete_image(cub->mlx, line->img);
	line->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	while (line->pixels > 0 && line->s_x > 0 && line->s_y > 0)
	{
		mlx_put_pixel(line->img, line->s_x, line->s_y, 0xFFFF00FF);
		line->s_x += line->dx_p;
		line->s_y += line->dy_p;
		line->pixels--;
	}
	mlx_image_to_window(cub->mlx, line->img, 0, 0);
}
