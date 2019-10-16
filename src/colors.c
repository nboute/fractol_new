/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:35:20 by niboute           #+#    #+#             */
/*   Updated: 2019/10/16 14:06:58 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <stdlib.h>

int		color_grad(unsigned int cola, unsigned int colb, int percent)
{
	short	r;
	short	g;
	short	b;

	r = (colb >> 16) - (cola >> 16);
	g = ((colb >> 8) & 0x000000FF) - ((cola >> 8) & 0x000000FF);
	b = (colb & 255) - (cola & 255);
	return (cola + ((((r * percent) / 100) * 65536) +
				(((g * percent) / 100) * 256) + (b * percent) / 100));
}

int		set_colors(t_vars *vars)
{
	int	i;
	int	color;
	int	color2;

	vars->nb_cols = (vars->nb_color_set) * vars->nb_color_grad;
	if (!vars->color_set)
		return (0);
	if (!(vars->colors = (unsigned int *)malloc(sizeof(unsigned int)
					* (vars->nb_cols))))
		return (0);
	i = 0;
	color = -1;
	while (i < (int)vars->nb_cols)
	{
		if (i % vars->nb_color_grad == 0)
		{
			color = (color + 1) % vars->nb_color_set;
			color2 = (color + 1) % vars->nb_color_set;
		}
		vars->colors[i] = color_grad(vars->color_set[color],
				vars->color_set[color2], (((i % (vars->nb_color_grad)) * 100)
					/ vars->nb_color_grad));
		i++;
	}
	return (1);
}

int		set_default_colors(t_vars *vars)
{
	vars->nb_color_set = 3;
	if (!(vars->color_set = (unsigned int*)malloc(sizeof(unsigned int) *
					vars->nb_color_set)))
		return (0);
	vars->color_set[0] = RED;
	vars->color_set[1] = YELLOW;
	vars->color_set[2] = BLUE;
	vars->nb_color_grad = 20;
	set_colors(vars);
	return (1);
}
