/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:27:55 by niboute           #+#    #+#             */
/*   Updated: 2019/10/19 15:01:40 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int		main_mouse_event(int button, int x, int y, t_vars *vars)
{
	if (x < 0 || x > MAINWINWID || y < 0 || y > MAINWINHEI)
		return (-1);
	if (button == 4)
		button = 1;
	if (button == 5)
		button = 2;
	zoom(button, x, y, vars);
	return (0);
}

int		main_key_event(int keycode, t_vars *vars)
{
	if (keycode >= 123 && keycode <= 126)
	{
		if (vars->fractal != 1)
			translate_default_fracts(keycode, vars);
		else
			translate_julia(keycode, vars);
		vars->win_ch[0] = 1;
	}
	if (keycode == 49)
		vars->vary = vars->vary ? 0 : 1;
	if (keycode == 53)
		ft_exit(0);
	return (0);
}

int		main_mouse_hover_event(int x, int y, t_vars *vars)
{
	if (vars->fractal != 1)
		return (0);
	if (vars->vary)
	{
		vars->xmin = ft_dmap(x, MAINWINWID, 2, -2);
		vars->ymin = ft_dmap(y, MAINWINHEI, -2, 2);
		vars->win_ch[0] = 1;
	}
	return (0);
}
