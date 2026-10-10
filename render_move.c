/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:00:00 by ebansse           #+#    #+#             */
/*   Updated: 2025/01/14 17:23:44 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	chk_item(t_data *data, char c)
{
	if (c == 'C')
	{
		put_image(data->map->img_map, data->map->sprites_array[1],
			data->pos_x * data->game->width, data->pos_y * data->game->height);
		data->map->map[data->pos_y][data->pos_x] = '0';
		data->map->item--;
	}
	return (0);
}

void	render_top(t_data *data)
{
	data->pos_x = data->game->perso_x / data->game->width;
	data->pos_y = (data->game->perso_y / data->game->height) - 1;
	data->next_case = data->map->map[data->pos_y][data->pos_x];
	if (data->next_case != '1' && !chk_item(data, data->next_case))
	{
		if (data->next_case == 'E')
		{
			if (data->map->item == 0)
			{
				ft_printf("Felicitation vous avez gagne en : %i coup !\n",
					data->game->perso_step + 1);
				finish(data);
				return ;
			}
		}
		else
		{
			put_floor(data);
			data->game->perso_y -= data->game->height;
			display_map(data->game, data->map);
		}
	}
	else
		data->game->print_step = 0;
}

void	render_bottom(t_data *data)
{
	data->pos_x = data->game->perso_x / data->game->width;
	data->pos_y = (data->game->perso_y / data->game->height) + 1;
	data->next_case = data->map->map[data->pos_y][data->pos_x];
	if (data->next_case != '1' && !chk_item(data, data->next_case))
	{
		data->game->print_step = 0;
		if (data->next_case == 'E')
		{
			if (data->map->item == 0)
			{
				ft_printf("Felicitation vous avez gagne en : %i coup !\n",
					data->game->perso_step + 1);
				finish(data);
				return ;
			}
		}
		else
		{
			put_floor(data);
			data->game->perso_y += data->game->height;
			display_map(data->game, data->map);
		}
	}
	else
		data->game->print_step = 0;
}

void	render_left(t_data *data)
{
	data->pos_x = (data->game->perso_x / data->game->width) - 1;
	data->pos_y = data->game->perso_y / data->game->height;
	data->next_case = data->map->map[data->pos_y][data->pos_x];
	if (data->next_case != '1' && !chk_item(data, data->next_case))
	{
		data->game->print_step = 0;
		if (data->next_case == 'E')
		{
			if (data->map->item == 0)
			{
				ft_printf("Felicitation vous avez gagne en : %i coup !\n",
					data->game->perso_step + 1);
				finish(data);
				return ;
			}
		}
		else
		{
			put_floor(data);
			data->game->perso_x -= data->game->width;
			display_map(data->game, data->map);
		}
	}
	else
		data->game->print_step = 0;
}

void	render_right(t_data *data)
{
	data->pos_x = (data->game->perso_x / data->game->width) + 1;
	data->pos_y = data->game->perso_y / data->game->height;
	data->next_case = data->map->map[data->pos_y][data->pos_x];
	if (data->next_case != '1' && !chk_item(data, data->next_case))
	{
		data->game->print_step = 0;
		if (data->next_case == 'E')
		{
			if (data->map->item == 0)
			{
				ft_printf("Felicitation vous avez gagne en : %i coup !\n",
					data->game->perso_step + 1);
				finish(data);
				return ;
			}
		}
		else
		{
			put_floor(data);
			data->game->perso_x += data->game->width;
			display_map(data->game, data->map);
		}
	}
	else
		data->game->print_step = 0;
}
