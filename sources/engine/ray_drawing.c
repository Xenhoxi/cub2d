/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:00:33 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/08 01:29:54 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	**setup_array_line(void)
{
	mlx_image_t	**array;

	array = malloc(sizeof(mlx_image_t *) * ((NB_RAY) + 100));
	return (array);
}

void	scale_for_ray(t_cub *cub, double new_angle, t_line *line)
{
	line->angle = new_angle;
	line->dir_x = cos(line->angle);
	line->dir_y = sin(line->angle);
	line->end_x = cub->player->pos_x + (line->dir_x * TSMAP);
	line->end_y = cub->player->pos_y + (line->dir_y * TSMAP);
	line->s_x = cub->player->pos_x;
	line->s_y = cub->player->pos_y;
	line->dx = line->end_x - cub->player->pos_x;
	line->dy = line->end_y - cub->player->pos_y;
	line->pixels = sqrt((line->dx * line->dx) + (line->dy * line->dy));
	line->dx_p = line->dx;
	line->dy_p = line->dy;
	line->dx_p /= line->pixels;
	line->dy_p /= line->pixels;
	line->sx = sqrt(1 + pow(line->dy / line->dx, 2));
	line->sy = sqrt(1 + pow(line->dx / line->dy, 2));
	printf("sx = %f sy = %f\n", line->sx, line->sy);
	printf("cos = %f sin = %f\n", line->dir_x, line->dir_y);
}

// Offset sur la premiere case + setup case dans laquelle je suis
void	calcul_offset(t_cub *cub, t_line *line)
{
	// double	offset_x;
	// double	offset_y;

	// offset_x = ((int)cub->player->pos_x) % TSMAP;
	// offset_y = ((int)cub->player->pos_y) % TSMAP;
	// printf("offset_x %f offset_y %f\n", offset_x, offset_y);
	// offset_x = offset_x / TSMAP;
	// offset_y = 1 - (offset_y / TSMAP);
	// printf("offset_x %f offset_y %f\n", offset_x, offset_y);
	// line->lenght_x = offset_x * line->sx * TSMAP;
	// line->lenght_y = offset_y * line->sy * TSMAP;
	line->map_y = ((int)cub->player->pos_y) / TSMAP;
	line->map_x = ((int)cub->player->pos_x) / TSMAP;
	printf("sx = %f sy = %f\n", line->sx, line->sy);
	if (line->dir_x < 0)
	{
		line->step_x = -1;
		line->lenght_x = (line->s_x - (line->map_x) * TSMAP) * line->sx;
	}
	else
	{
		line->step_x = 1;
		line->lenght_x = (((line->map_x + 1) * TSMAP) - line->s_x) * line->sx;
	}
	if (line->dir_y < 0)
	{
		line->step_y = -1;
		line->lenght_y = (line->s_y - (line->map_y) * TSMAP) * line->sy;
	}
	else
	{
		line->step_y = 1;
		line->lenght_y = (((line->map_y + 1) * TSMAP) - line->s_y) * line->sy;
	}
	printf("lenght_offx %f lenght_offy %f\n", line->lenght_x, line->lenght_y);
}

void	draw_rays(t_cub *cub)
{
	t_line		line;
	double		actual;
	double		fdist;
	double		end;
	int			i;

	i = 0;
	fdist = 0;
	actual = cub->player->angle;
	end = cub->player->angle + (PI / 6);
	while (actual <= end)
	{
		printf("--------Drawline--------\n");
		scale_for_ray(cub, actual, &line);
		calcul_offset(cub, &line);
		printf("start map_x = %d start map_y = %d\n", line.map_x, line.map_y);
		while (1)
		{
			printf("dir_x %f dir_y %f\n", line.dir_x, line.dir_y);
			printf("lenght_x = %f lenght_y = %f\n", line.lenght_x, line.lenght_y);
			if (cub->map->map[line.map_y][line.map_x] == '1')
				break ;
			if (line.lenght_x < line.lenght_y)
			{
				fdist = line.lenght_x;
				line.lenght_x += line.sx * TSMAP;
				line.map_x += line.step_x;
			}
			else
			{
				fdist = line.lenght_y;
				line.lenght_y += line.sy * TSMAP;
				line.map_y += line.step_y;
			}
			printf("map_x %d map_y %d\n", line.map_x, line.map_y);
		}
		line.end_x = cub->player->pos_x + line.dir_x * fdist;
		line.end_y = cub->player->pos_y + line.dir_y * fdist;
		printf("fdist = %f\n", fdist);
		draw_rayline(cub, &line, &cub->player->array_line[i]);
		i++;
		printf("i = %d\n", i);
		actual += (PI);
	}
}

void	draw_rayline(t_cub *cub, t_line *line, mlx_image_t **img)
{
	line->s_x = cub->player->pos_x;
	line->s_y = cub->player->pos_y;
	line->dx = line->end_x - cub->player->pos_x;
	line->dy = line->end_y - cub->player->pos_y;
	line->dx_p = line->dx;
	line->dy_p = line->dy;
	line->pixels = sqrt((line->dx * line->dx) + (line->dy * line->dy));
	line->dx_p /= line->pixels;
	line->dy_p /= line->pixels;
	if (*img)
		mlx_delete_image(cub->mlx, *img);
	*img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	while (line->pixels > 0 && line->s_x > 0 && line->s_y > 0)
	{
		mlx_put_pixel(*img, line->s_x, line->s_y, 0x00FFFFFF);
		line->s_x += line->dx_p;
		line->s_y += line->dy_p;
		line->pixels--;
	}
	mlx_image_to_window(cub->mlx, *img, 0, 0);
}
