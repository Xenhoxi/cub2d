/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:17:23 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/03 15:58:00 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap(t_cub *cub)
{
	mlx_image_t	*img;

	img = create_img_full(TSMAP, cub->mlx, 0xFFFF00FF);
	draw_minimap(cub->map, cub->mlx, img);
}

void	draw_minimap(t_map *map, mlx_t *mlx, mlx_image_t *img)
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
			if (map_char[y][x] == '1')
				mlx_image_to_window(mlx, img, x * TSMAP, y * TSMAP);
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
			mlx_put_pixel(img, x, y, color);
		x = -1;
	}
	return (img);
}
