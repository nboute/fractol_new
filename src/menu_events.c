/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 11:38:40 by niboute           #+#    #+#             */
/*   Updated: 2019/10/16 17:41:35 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include "../minilibx_macos/mlx.h"
#include <stdio.h>
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
			ft_exit(-1);
		i = 0;
		while (i < vars->nb_color_set)
			vars->color_set[i++] = BLACK;
		vars->menumode = 2;
	}
	return (0);
}

int		preset_menu_key_event(int keycode, t_vars *vars)
{
	int	val;

	if (keycode == 48)
		vars->index = (vars->index + 1) % 3;
	else if (keycode == 36 || keycode == 76)
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
			set_colors(vars);
			vars->menumode = 0;
			vars->win_ch[0] = 1;
		}
	}
	vars->win_ch[1] = 1;
	return (0);
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

int		menu_mouse_release_event(int button, int x, int y, t_vars *vars)
{
	vars = NULL;
	button = 1;
	x = 0;
	y = 0;
	return (0);
}
