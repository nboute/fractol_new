/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 11:38:40 by niboute           #+#    #+#             */
/*   Updated: 2019/10/19 15:03:09 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include "../minilibx_macos/mlx.h"
#include <stdlib.h>

int		menu_mouse_event_p2(int button, int x, int y, t_vars *vars)
{
	int	button_pressed;

	button_pressed = x / (MENUWINWID / BTN_COL) +
		((y / (MENUWINHEI / BTN_ROW)) * BTN_COL);
	if (button_pressed == 2)
	{
		vars->fractal = (vars->fractal + (button == 1 ? 1 : -1));
		if (vars->fractal == -1)
			vars->fractal = 2;
		if (vars->fractal == 3)
			vars->fractal = 0;
		reset_fractal(vars);
	}
	else if (button_pressed == 3)
		reset_fractal(vars);
	else if (button_pressed == 5)
		vars->menumode = 1;
	return (0);
}

int		menu_mouse_event(int button, int x, int y, t_vars *vars)
{
	int	button_pressed;

	if (x < 0 || x > MENUWINWID || y < 0 || y > MENUWINHEI || vars->menumode)
		return (0);
	button_pressed = x / (MENUWINWID / BTN_COL)
		+ ((y / (MENUWINHEI / BTN_ROW)) * BTN_COL);
	if (button_pressed == 0)
	{
		if (button == 1)
			vars->variter = vars->variter == 1 ? 0 : 1;
		if (button == 2)
			vars->variter = vars->variter == -1 ? 0 : -1;
	}
	else if (button_pressed == 1)
	{
		if (button == 1)
			vars->colvar = vars->colvar == 1 ? 0 : 1;
		if (button == 2)
			vars->colvar = vars->colvar == -1 ? 0 : -1;
	}
	else
		menu_mouse_event_p2(button, x, y, vars);
	vars->win_ch[1] = 1;
	return (1);
}

int		default_menu_key_event(int keycode, t_vars *vars)
{
	char	val;

	val = get_alnum_from_keycode(keycode);
	if (!vars->index && val >= 0 && val <= 9)
	{
		vars->itermax = ((vars->itermax * 10) + val) % 500;
		vars->win_ch[0] = 1;
		vars->win_ch[1] = 1;
	}
	return (0);
}

int		menu_key_event(int keycode, t_vars *vars)
{
	if (vars->menumode == 0)
		default_menu_key_event(keycode, vars);
	else if (vars->menumode == 1)
		preset_menu_key_event(keycode, vars);
	else if (vars->menumode == 2)
		color_menu_key_event(keycode, vars);
	return (0);
}
