/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:25:24 by ebansse           #+#    #+#             */
/*   Updated: 2025/01/13 18:00:12 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_all(t_data *data)
{
	int		i;

	i = 0;
	if (data->map->map != NULL)
	{
		while (data->map->map[i] != NULL)
			free(data->map->map[i++]);
		free(data->map->map);
	}
	if (data->map->sprites_array)
		clear_array_img(data->game, data->map->sprites_array);
	if (data->map->img_map)
		free_image(data->game, data->map->img_map);
	if (data->game->win_ptr)
		mlx_destroy_window(data->game->mlx_ptr, data->game->win_ptr);
	mlx_destroy_display(data->game->mlx_ptr);
	free(data->game->mlx_ptr);
}

int	finish(t_data *data)
{
	free_all(data);
	exit(0);
	return (1);
}

void	flood_fill(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->line_map || x < 0 || x >= (int)map->cols
		|| map->copy_map[y][x] == '1' || map->copy_map[y][x] == 'F')
		return ;
	map->copy_map[y][x] = 'F';
	flood_fill(map, y, x - 1);
	flood_fill(map, y, x + 1);
	flood_fill(map, y - 1, x);
	flood_fill(map, y + 1, x);
}

int	exit_check(t_map *map)
{
	int	accessible;
	int	i;

	i = -1;
	if (map->exit != 1 || map->spawn != 1)
		return (0);
	map->copy_map = tableau_map(map);
	if (map->copy_map != NULL)
	{
		flood_fill(map, map->pos_p[0], map->pos_p[1]);
		if (map->pos_e[1] < (int)map->cols && map->pos_e[0] < map->line_map)
			accessible = (map->copy_map[map->pos_e[0]][map->pos_e[1]] == 'F');
		else
			accessible = 0;
		i = -1;
		while (++i < map->line_map)
		{
			free(map->copy_map[i]);
		}
		free(map->copy_map);
		map->copy_map = NULL;
	}
	else
		accessible = 0;
	return (accessible);
}

int	map_check(t_map *map, t_game *game)
{
	if (!map->map || !map->map[0])
		return (0);
	letter_number_check(map, 0, 0);
	if (!rectangle_check(map) || map->spawn > 1 || map->exit > 1
		|| map->item == 0 || map->valid == 0 || !wall_check(map)
		|| !exit_check(map))
		return (0);
	game->perso_x = (map->pos_p[1] * game->width);
	game->perso_y = (map->pos_p[0] * game->height);
	game->marge_x = (game->width / 2) - (game->perso_width / 2);
	game->marge_y = (game->height / 2) - (game->perso_height / 2);
	return (1);
}
