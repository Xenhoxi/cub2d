/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:00:33 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/07 01:37:54 by ljerinec         ###   ########.fr       */
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
}

// Offset sur la premiere case + setup case dans laquelle je suis
void	calcul_offset(t_cub *cub, t_line *line)
{
	double	offset_x;
	double	offset_y;

	offset_x = ((int)cub->player->pos_x) % TSMAP;
	offset_y = ((int)cub->player->pos_y) % TSMAP;
	printf("offset_x %f offset_y %f\n", offset_x, offset_y);
	offset_x = offset_x / TSMAP;
	offset_y = 1 - (offset_y / TSMAP);
	printf("offset_x %f offset_y %f\n", offset_x, offset_y);
	line->lenght_x = offset_x * line->sx * TSMAP;
	line->lenght_y = offset_y * line->sy * TSMAP;
	printf("lenght_x %f lenght_y %f\n", line->lenght_x, line->lenght_y);
	line->map_y = floor((((int)cub->player->pos_y) / TSMAP));
	line->map_x = floor((((int)cub->player->pos_x) / TSMAP));
}

void	draw_rays(t_cub *cub)
{
	t_line		line;
	double		actual;
	double		end;
	int			i;

	i = 0;
	actual = cub->player->angle;
	end = cub->player->angle + (PI / 6);
	while (actual <= end)
	{
		scale_for_ray(cub, actual, &line);
		calcul_offset(cub, &line);
		printf("map_x = %d map_y = %d\n", line.map_x, line.map_y);
		while (1)
		{
			printf("dir_x %f dir_y %f\n", line.dir_x, line.dir_y);
			if (line.lenght_x < line.lenght_y)
				line.lenght_x += line.sx * TSMAP;
			else
				line.lenght_y += line.sy * TSMAP;
			if (line.lenght_x < line.lenght_y)
			{
				if (line.dir_x > 0)
					line.map_x++;
				else
					line.map_x++;
			}
			else
			{
				if (line.dir_y < 0)
					line.map_y--;
				else
					line.map_y++;
			}
			printf("map_x %d map_y %d\n", line.map_x, line.map_y);
			if (cub->map->map[line.map_y][line.map_x] == '1')
			{
				line.end_x = cub->player->pos_x + line.dir_x * line.lenght_x;
				line.end_y = cub->player->pos_y + line.dir_y * line.lenght_y;
				draw_rayline(cub, &line, &cub->player->array_line[i]);
				break ;
			}
		}
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
