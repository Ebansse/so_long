/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:09:44 by ebansse           #+#    #+#             */
/*   Updated: 2025/01/13 17:54:06 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**remplir_tableau(char **map, int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (map);
}

char	**tableau_map(t_map *map)
{
	char	*line;
	char	**mapp;
	int		fd;

	fd = open(map->path_map, O_RDONLY);
	line = get_next_line(fd);
	map->line_map = 0;
	while (line != NULL)
	{
		map->line_map++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	mapp = (char **)malloc((map->line_map + 1) * sizeof(char *));
	if (!mapp)
		return (NULL);
	fd = open(map->path_map, O_RDONLY);
	mapp = remplir_tableau(mapp, fd);
	close(fd);
	return (mapp);
}

int	wall_check(t_map *map)
{
	int		i;
	size_t	col;

	col = map->cols - 2;
	if (!ft_str_only_chr(map->map[0], '1'))
		return (0);
	else if (!ft_str_only_chr(map->map[map->line_map - 1], '1'))
		return (0);
	i = 0;
	while (i < map->line_map)
	{
		if (map->map[i][0] != '1' || map->map[i][col] != '1')
			return (0);
		i++;
	}
	return (1);
}

void	letter_number_check(t_map *map, int i, int j)
{
	while (i < map->line_map && map->map[i] != NULL)
	{
		j = 0;
		while (j < (int)map->cols - 1)
		{
			if (map->map[i][j] == 'P')
			{
				map->spawn++;
				map->pos_p[0] = i;
				map->pos_p[1] = j;
			}
			else if (map->map[i][j] == 'E')
			{
				map->exit++;
				map->pos_e[0] = i;
				map->pos_e[1] = j;
			}
			else if (map->map[i][j] == 'C')
				map->item++;
			else if (map->map[i][j] != '1' && map->map[i][j] != '0')
				map->valid = 0;
			j++;
		}
		i++;
	}
}

int	rectangle_check(t_map *map)
{
	int		j;
	size_t	len;

	j = 0;
	if (map->line_map < 3)
		return (0);
	while (j < map->line_map)
	{
		len = ft_strlen((const char *)map->map[j]);
		if (j == map->line_map - 1 && map->map[j][len - 1] != '\n')
			len++;
		if (len != map->cols)
			return (0);
		j++;
	}
	return (1);
}
