/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 20:55:07 by itaouil           #+#    #+#             */
/*   Updated: 2022/10/26 02:45:41 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_collisions(t_cub *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_y = y / WALLS_SIDE;
	map_x = x / WALLS_SIDE;
	if (data->cubmap[map_y][map_x] == '1' || data->cubmap[map_y][map_x] == 'D'
		|| data->cubmap[map_y][map_x] == 'R')
		return (1);
	if (data->cubmap[map_y][map_x] == 'G')
		end_cub(data);
	return (0);
}

void	rotation(t_cub *data)
{
	if (data->left_arrow == true)
		data->angle += 0.05;
	else if (data->right_arrow)
		data->angle -= 0.05;
}

void	lateral_moves(t_cub *data)
{
	double	new_x;
	double	new_y;

	if (data->d_key == true)
	{
		new_x = data->player->x + cos(data->ray - (PI / 2)) * SPEED;
		new_y = data->player->y - sin(data->ray - (PI / 2)) * SPEED;
		if (!check_collisions(data, new_x, new_y))
		{
			data->player->y = new_y;
			data->player->x = new_x;
		}
	}
	if (data->a_key == true)
	{
		new_y = data->player->y - sin(data->ray + (PI / 2)) * SPEED;
		new_x = data->player->x + cos(data->ray + (PI / 2)) * SPEED;
		if (!check_collisions(data, new_x, new_y))
		{
			data->player->y = new_y;
			data->player->x = new_x;
		}
	}
}

void	forward_moves(t_cub *data)
{
	double	new_x;
	double	new_y;

	if (data->w_key == true)
	{
		new_x = data->player->x + cos(data->ray) * SPEED;
		new_y = data->player->y - sin(data->ray) * SPEED;
		if (!check_collisions(data, new_x, new_y))
		{
			data->player->y = new_y;
			data->player->x = new_x;
		}
	}
	if (data->s_key == true)
	{
		new_y = data->player->y + sin(data->ray) * SPEED;
		new_x = data->player->x - cos(data->ray) * SPEED;
		if (!check_collisions(data, new_x, new_y))
		{
			data->player->y = new_y;
			data->player->x = new_x;
		}
	}
}