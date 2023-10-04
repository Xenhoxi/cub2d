/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 23:50:45 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/04 19:24:25 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*setup_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->map = NULL;
	return (map);
}

t_cub	*setup_cub(void)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	cub->game_on = 0;
	cub->map = setup_map();
	cub->player = malloc(sizeof(t_player));
	cub->player->pos_x = 0;
	cub->player->pos_y = 0;
	cub->player->angle = 2*PI/2;
	cub->player->dir_x = cos(cub->player->angle);
	cub->player->dir_y = sin(cub->player->angle);
	printf("Angle = %f\n", cub->player->angle);
	printf("dir_x = %f, dir_y = %f\n", cub->player->dir_x, cub->player->dir_y);
	return (cub);
}

void	key_hook(void *param)
{
	t_cub	*cub;
	mlx_t	*mlx;

	cub = (t_cub *)param;
	mlx = cub->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	ft_load(t_cub *cub)
{
	minimap(cub);
	init_player(cub);
	draw_line(cub);
}

void	ft_update(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	player_update(cub);
	return ;
}

void	run(t_cub *cub)
{
	cub->mlx = mlx_init(1280, 920, "Black ops 2 Zombies", true);
	if (!cub->mlx)
		exit(EXIT_FAILURE);
	ft_load(cub);
	mlx_loop_hook(cub->mlx, ft_update, (void *)cub);
	mlx_loop_hook(cub->mlx, key_hook, (void *)cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}

int	main(int argc, char **argv)
{
	t_cub	*big_data;

	(void) argc;
	big_data = setup_cub();
	if (argc != 2 || check_ext(argv[1], ".cub") || file_exist(argv[1]))
		return (1);
	big_data->map->map = parsing(argv[1]);
	print_char_map(big_data->map->map);
	run(big_data);
	return (0);
}
