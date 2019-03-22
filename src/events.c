/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 11:38:40 by niboute           #+#    #+#             */
/*   Updated: 2019/03/22 06:58:09 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include "../minilibx_macos/mlx.h"



int		ft_menu_mouse_event(int button, int x, int y, t_vars *vars)
{
	int	button_pressed;

	if (x < 0 || x > MENUWINWID || y < 0 || y > MENUWINHEI)
		return (0);
	button_pressed = x / (MENUWINWID / BTN_ROW) +
		((y / (MENUWINHEI / BTN_COL)) * BTN_COL);
	return (0);
}

int		ft_menu_key_event(int keycode, t_vars *vars)
{
	int	val;

	return (0);
}

int		ft_menu_mouse_release_event(int button, int x, int y, t_vars *vars)
{
	return (0);
}
