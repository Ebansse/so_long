/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:21:26 by ebansse           #+#    #+#             */
/*   Updated: 2025/01/14 17:20:05 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "mlx/mlx.h"
# include "libft/libft.h"

typedef struct t_img
{
	int		width;
	int		height;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct t_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		win_w;
	int		win_h;
	int		width;
	int		height;
	int		perso_width;
	int		perso_height;
	int		off_width;
	int		off_height;
	void	*perso_img;
	int		perso_step;
	int		print_step;
	int		perso_x;
	int		perso_y;
	int		marge_x;
	int		marge_y;
	int		collect;
}	t_game;

typedef struct t_map
{
	char	*path_map;
	char	**map;
	char	**copy_map;
	t_img	**sprites_array;
	t_img	*img_map;
	int		spawn;
	int		exit;
	int		item;
	int		valid;
	int		line_map;
	size_t	cols;
	int		pos_e[2];
	int		pos_p[2];
}	t_map;

typedef struct t_data
{
	int		pos_x;
	int		pos_y;
	char	next_case;
	t_game	*game;
	t_map	*map;
	t_img	*img;
}	t_data;

int		key_press(int keycode, t_data *data);
int		error(char *msg);

char	**remplir_tableau(char **map, int fd);
char	**tableau_map(t_map *map);
int		wall_check(t_map *map);
void	letter_number_check(t_map *map, int i, int j);
int		rectangle_check(t_map *map);

void	flood_fill(t_map *map, int x, int y);
int		exit_check(t_map *map);
int		map_check(t_map *map, t_game *game);
void	free_all(t_data *data);
int		finish(t_data *data);

void	display_map(t_game *game, t_map *map);
void	display_item(t_map *map, int x, int y, char c);
void	create_map(t_game *game, t_map *map);
void	put_floor(t_data *data);
int		move(int keycode, t_data *data);

int		chk_item(t_data *data, char c);
void	render_top(t_data *data);
void	render_bottom(t_data *data);
void	render_left(t_data *data);
void	render_right(t_data *data);

t_img	*new_image(void *mlx, int width, int height);
void	free_image(t_game *game, t_img *img);
void	clear_array_img(t_game *game, t_img **imgs);
char	*build_path(char const *s1, char const *s2, int j);
t_img	*load_img(t_game *game, char *path);
t_img	**load_sprites(t_game *game, char *path, unsigned int count);
void	put_pixel(t_img *img, int x, int y, int color);
void	put_image(t_img *dest, t_img *img, int x0, int y0);

#endif