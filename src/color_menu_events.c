/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_menu_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:26:23 by niboute           #+#    #+#             */
/*   Updated: 2019/10/19 14:59:04 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <stdlib.h>

int		preset_menu_key_event_p2(t_vars *vars)
{
	int	i;

	vars->index = (vars->index + 1) % 3;
	if (!vars->index)
	{
		vars->index = 0;
		if (vars->color_set)
			free(vars->color_set);
		if (!(vars->color_set = (unsigned int*)malloc(sizeof(unsigned int)
						* vars->nb_color_set)))
			ft_exit(1);
		i = 0;
		while (i < vars->nb_color_set)
			vars->color_set[i++] = BLACK;
		vars->menumode = 2;
	}
	return (1);
}

int		preset_menu_key_event(int keycode, t_vars *vars)
{
	int	val;

	vars->index = keycode == 48 ? (vars->index + 1) % 3 : vars->index;
	if (keycode == 36 || keycode == 76)
		preset_menu_key_event_p2(vars);
	else if ((val = get_alnum_from_keycode(keycode)) == -1)
		return (0);
	else if (val >= 0 && val <= 9)
	{
		if (vars->index == 0)
			vars->nb_color_set = (vars->nb_color_set % 10) > 2 ? 10 + val :
				(vars->nb_color_set * 10) % 100 + val;
		else if (vars->index == 1)
		{
			vars->nb_color_grad = vars->nb_color_grad * 10 + val;
			while (vars->nb_color_grad > 100)
				vars->nb_color_grad -= 100;
		}
		if (vars->nb_color_grad < 1)
			vars->nb_color_grad = 1;
		if (vars->nb_color_set < 2 || vars->nb_color_set > 20)
			vars->nb_color_set = 2;
	}
	vars->win_ch[1] = 1;
	return (0);
}

int		color_menu_key_event(int keycode, t_vars *vars)
{
	char	key;

	key = get_alnum_from_keycode(keycode);
	if ((key >= 0 && key <= 9) || (key >= 'a' && key <= 'f'))
	{
		vars->color_set[vars->index] = ((vars->color_set[vars->index] << 4)
				& 0x00FFFFF0) + (ft_isalpha(key)
				? (unsigned int)(key - 'a' + 10) : (unsigned int)key);
	}
	if (keycode == 36 || keycode == 76)
	{
		vars->index = (vars->index + 1) % vars->nb_color_set;
		if (!vars->index)
		{
			if (vars->colors)
				free(vars->colors);
			if (!(set_colors(vars)))
				ft_exit(1);
			vars->menumode = 0;
			vars->win_ch[0] = 1;
		}
	}
	vars->win_ch[1] = 1;
	return (0);
}
