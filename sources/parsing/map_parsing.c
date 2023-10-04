/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:09:25 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/03 15:32:41 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_is_closed(char **map)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (element_type(map[i]) != ft_strdup("MAP"))
		i++;
	while (map[i])
	{
		while (map[i][u])
		{
			while (is_space(map[i][u]))
				u++;
		}
		u = 0;
		i++;
	}
	return (0);
}

char	*element_type(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (is_alpha(line[i]))
	{
		while (line[i])
		{
			if (line[i] == '.' && line[i + 1] == '/')
				return ("TEXTURE_PATH");
			i++;
		}
		return ("COLOR");
	}
	else if (is_digit(line[i]))
		return ("MAP");
	else
		return ("WRONG ELEMENT SYNTAX");
}
