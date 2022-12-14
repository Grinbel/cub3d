/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:17:19 by itaouil           #+#    #+#             */
/*   Updated: 2022/10/25 03:23:25 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	closest_wall(t_cub *data, t_point *hor_inter, t_point *ver_inter)
{
	double			hor_distance;
	double			ver_distance;
	double			closest;

	hor_distance = get_distance(data->player, hor_inter);
	ver_distance = get_distance(data->player, ver_inter);
	if (ver_distance < hor_distance)
	{
		closest = ver_distance;
		data->closest_wall = VERT;
		data->intersection.x = ver_inter->x;
		data->intersection.y = ver_inter->y;
	}
	else
	{
		closest = hor_distance;
		data->closest_wall = HOR;
		data->intersection.x = hor_inter->x;
		data->intersection.y = hor_inter->y;
	}
	data->dist_to_closest_wall = closest;
	return (closest);
}

void	get_directions_3d(t_cub *data, t_directions *dir)
{
	dir->down = 0;
	dir->up = 0;
	dir->left = 0;
	dir->right = 0;
	if (data->ray > 0 && data->ray < PI)
		dir->up = 1;
	else
		dir->down = 1;
	if ((data->ray > 0 && data->ray < PI / 2)
		|| (data->ray > 3 * PI / 2 && data->ray < 2 * PI))
		dir->right = 1;
	else
		dir->left = 1;
}

void	lay_background(t_cub *data)
{
	int	i;
	int	j;
	int	floor;
	int	ceiling;

	i = 0;
	j = 0;
	floor = get_floor_or_ceiling_color(data, FLOOR);
	ceiling = get_floor_or_ceiling_color(data, CEILING);
	while (i < HEIGHT_3D)
	{
		while (j < WIDTH_3D)
		{
			if (i < HEIGHT_3D / 2)
				put_pixel_to_image_3d(data, j, i, ceiling);
			else
				put_pixel_to_image_3d(data, j, i, floor);
			j++;
		}
		j = 0;
		i++;
	}
}

void	init_3d_map(t_cub *data)
{
	t_mlx	*map3d;

	map3d = data->map3d;
	map3d->mlx_ptr = mlx_init();
	map3d->win_ptr = mlx_new_window(map3d->mlx_ptr,
			WIDTH_3D, HEIGHT_3D, "the cub");
	map3d->img_ptr = mlx_new_image(map3d->mlx_ptr, WIDTH_3D, HEIGHT_3D);
	map3d->img_addr = mlx_get_data_addr(map3d->img_ptr,
			&(map3d->bpix), &(map3d->line), &(map3d->end));
}
