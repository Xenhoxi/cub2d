/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:17:23 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/07 00:05:30 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap(t_cub *cub)
{
	mlx_image_t	*img_0;
	mlx_image_t	*img_1;

	img_1 = create_img_full(TSMAP, cub->mlx, 0xFFFF00FF);
	img_0 = create_img_full(TSMAP, cub->mlx, 0xFFFFFF01);
	draw_minimap(cub->map, cub->mlx, img_1, img_0);
}

void	draw_minimap(t_map *map, mlx_t *mlx, mlx_image_t *img_1, mlx_image_t *img_0)
{
	char	**map_char;
	int		x;
	int		y;

	map_char = map->map;
	x = -1;
	y = -1;
	while (map_char[++y])
	{
		while (map_char[y][++x])
		{
			if (map_char[y][x] == '1')
				mlx_image_to_window(mlx, img_1, x * TSMAP, y * TSMAP);
			else
				mlx_image_to_window(mlx, img_0, x * TSMAP, y * TSMAP);
		}
		x = -1;
	}
}

mlx_image_t	*create_img_full(int size, mlx_t *mlx, uint64_t color)
{
	int			x;
	int			y;
	mlx_image_t	*img;

	x = -1;
	y = -1;
	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
	while (++y < size)
	{
		while (++x < size)
		{
			if (x == 0 || x == size - 1 || y == 0 || y == size - 1)
				mlx_put_pixel(img, x, y, color);
			else
				mlx_put_pixel(img, x, y, 0x000000FF);
		}
		x = -1;
	}
	return (img);
}
