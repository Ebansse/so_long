/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:03:39 by ebansse           #+#    #+#             */
/*   Updated: 2025/01/07 18:59:00 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_img	*new_image(void *mlx, int width, int height)
{
	t_img	*i;

	i = ft_calloc(1, sizeof(t_img));
	i->img = mlx_new_image(mlx, width, height);
	i->addr = mlx_get_data_addr(i->img,
			&i->bpp,
			&i->line_length,
			&i->endian);
	i->width = width;
	i->height = height;
	return (i);
}

void	free_image(t_game *game, t_img *img)
{
	mlx_destroy_image(game->mlx_ptr, img->img);
	free(img);
}

void	clear_array_img(t_game *game, t_img **imgs)
{
	t_img	**arr;

	arr = imgs;
	while (*imgs)
	{
		free_image(game, *imgs);
		imgs++;
	}
	free(arr);
}

int	error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}
