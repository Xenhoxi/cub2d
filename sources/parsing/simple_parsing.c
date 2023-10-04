/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:44:15 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/03 15:50:27 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	selected_fd(char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	return (fd);
}

char	**parsing(char *map)
{
	char	**tab;
	char	*line;
	int		fd;

	tab = NULL;
	fd = selected_fd(map);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		tab = array_join(tab, line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (tab);
}

char	**array_join(char **array, char *line)
{
	int		i;
	char	**new_array;
	int		len;

	i = 0;
	if (array != NULL)
		while (array[i])
			i++;
	len = i;
	new_array = malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_array[i] = array[i];
		i++;
	}
	if (line[ft_strlen(line) - 1] == '\n')
		new_array[i] = ft_substr(line, 0, ft_strlen(line) - 1);
	else
		new_array[i] = ft_strdup(line);
	new_array[++i] = NULL;
	free(array);
	return (new_array);
}

int	check_ext(char	*file_name, char	*ext)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (file_name[i])
		i++;
	if (i < 5)
	{
		ft_printf("Error\nFile name too short\n");
		return (1);
	}
	i -= 4;
	while (file_name[i] && ext[j])
	{
		if (file_name[i] != ext[j])
		{
			ft_printf("Error\nWrong file extension\n");
			return (1);
		}
		i++;
		j++;
	}
	return (0);
}

int	file_exist(char	*file_name)
{
	if (open(file_name, O_RDONLY) == -1)
	{
		ft_printf("Error\nFile does not exist\n");
		return (1);
	}
	return (0);
}
