/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:59:46 by ebansse           #+#    #+#             */
/*   Updated: 2025/01/14 17:18:16 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_floor(t_data *data)
{
	data->game->perso_step++;
	data->game->print_step = 1;
	put_image(data->map->img_map, data->map->sprites_array[1],
		data->game->perso_x, data->game->perso_y);
}

void	display_item(t_map *map, int x, int y, char c)
{
	if (c == 'E')
	{
		put_image(map->img_map, map->sprites_array[1], x, y);
		put_image(map->img_map, map->sprites_array[0], x, y);
	}
	else if (c == 'C')
	{
		put_image(map->img_map, map->sprites_array[1], x, y);
		put_image(map->img_map, map->sprites_array[2], x, y);
	}
	else if (c == '0')
	{
		put_image(map->img_map, map->sprites_array[1], x, y);
	}
	else if (c == '1')
	{
		put_image(map->img_map, map->sprites_array[5], x, y);
	}
}

void	display_map(t_game *game, t_map *map)
{
	put_image(map->img_map, map->sprites_array[4],
		game->perso_x + game->marge_x, game->perso_y + game->marge_y);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		map->img_map->img, 0, 0);
}

void	create_map(t_game *game, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->line_map)
	{
		j = 0;
		while (j < (int)map->cols)
		{
			if (map->map[i][j] == '0' || map->map[i][j] == 'P')
				display_item(map, j * game->width, i * game->height, '0');
			else if (map->map[i][j] == '1')
				display_item(map, j * game->width, i * game->height, '1');
			else if (map->map[i][j] == 'E')
				display_item(map, j * game->width, i * game->height, 'E');
			else if (map->map[i][j] == 'C')
				display_item(map, j * game->width, i * game->height, 'C');
			j++;
		}
		i++;
	}
	display_map(game, map);
}

int	move(int keycode, t_data *data)
{
	if (!data || !data->game)
		return (0);
	data->game->print_step = 0;
	if ((keycode == 119 || keycode == 65362))
		render_top(data);
	else if ((keycode == 115 || keycode == 65364))
		render_bottom(data);
	else if ((keycode == 97 || keycode == 65361))
		render_left(data);
	else if ((keycode == 100 || keycode == 65363))
		render_right(data);
	if (data->game->print_step == 1)
		ft_printf("Steps: %i\n", data->game->perso_step);
	return (1);
}
