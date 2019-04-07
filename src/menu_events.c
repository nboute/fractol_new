/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 11:38:40 by niboute           #+#    #+#             */
/*   Updated: 2019/04/07 17:53:44 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include "../minilibx_macos/mlx.h"
#include <stdio.h>
#include <stdlib.h>

int		get_key_letter(int keycode)
{
	if (keycode == 0)
		return ('a');
	if (keycode == 11)
		return ('b');
	if (keycode == 8)
		return ('c');
	if (keycode == 2)
		return ('d');
	if (keycode == 14)
		return ('e');
	if (keycode == 3)
		return ('f');
	if (keycode == 5)
		return ('g');
	if (keycode == 4)
		return ('h');
	if (keycode == 34)
		return ('i');
	if (keycode == 38)
		return ('j');
	if (keycode == 40)
		return ('k');
	if (keycode == 37)
		return ('l');
	if (keycode == 46)
		return ('m');
	if (keycode == 45)
		return ('n');
	if (keycode == 31)
		return ('o');
	if (keycode == 35)
		return ('p');
	if (keycode == 12)
		return ('q');
	if (keycode == 15)
		return ('r');
	if (keycode == 1)
		return ('s');
	if (keycode == 17)
		return ('t');
	if (keycode == 32)
		return ('u');
	if (keycode == 9)
		return ('v');
	if (keycode == 13)
		return ('w');
	if (keycode == 7)
		return ('x');
	if (keycode == 16)
		return ('y');
	if (keycode == 6)
		return ('z');
	return (-1);
}

int		get_key(int keycode)
{
	if (keycode >= 82 && keycode <= 92 && keycode != 90)
		return (keycode >= 91 ? keycode - 83 : keycode - 82);
	if (keycode >= 18 && keycode <= 29 && keycode != 27 && keycode != 24)
	{
		if (keycode <= 21)
			return (keycode - 17);
		if (keycode <= 23)
			return (keycode == 22 ? 6 : 5);
		if (keycode <= 26)
			return (keycode == 25 ? 9 : 7);
		if (keycode <= 29)
			return (keycode == 29 ? 0 : 8);
	}
	if ((keycode >= 0 && keycode <= 9) || (keycode >= 11 && keycode <= 17) || (keycode >= 31 && keycode <= 46))
		return (get_key_letter(keycode));
	return (-1);
}

int		ft_menu_mouse_event(int button, int x, int y, t_vars *vars)
{
	int	button_pressed;

	if (x < 0 || x > MENUWINWID || y < 0 || y > MENUWINHEI)
		return (0);
	if (vars->menumode)
		return (0);
	button_pressed = x / (MENUWINWID / BTN_ROW) +
		((y / (MENUWINHEI / BTN_COL)) * BTN_COL);
	if (button_pressed == 0)
	{
		if (button == 1)
			vars->variter = vars->variter == 1 ? 0 : 1;
		if (button == 2)
			vars->variter = vars->variter == -1 ? 0 : -1;
		if (button == 3)
			vars->index = 0;
	}
	if (button_pressed == 1)
	{
		if (button == 1)
			vars->colvar = vars->colvar == 1 ? 0 : 1;
		if (button == 2)
			vars->colvar = vars->colvar == -1 ? 0 : -1;
	}
	if (button_pressed == 2)
	{
		vars->fractal = (vars->fractal + (button == 1 ? 1 : -1));
		if (vars->fractal == -1)
			vars->fractal = 2;
		if (vars->fractal == 3)
			vars->fractal = 0;
		ft_reset_fractal(vars);
	}
	if (button_pressed == 8)
	{
		printf("CHANGED MODE\n");
		vars->menumode = 1;
	}
	vars->win_ch[1] = 1;
	return (0);
}

int		ft_preset_menu_key_event_p2(t_vars *vars)
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
		printf("MALLOCED COLOR SET\n");
		i = 0;
		while (i < vars->nb_color_set)
			vars->color_set[i++] = BLACK;
		vars->menumode = 2;
	}
	return (0);
}

int		ft_preset_menu_key_event(int keycode, t_vars *vars)
{
	int	val;

	val = get_key(keycode);
	if (val >= 0 && val <= 9)
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
	if (keycode == 48)
		vars->index = (vars->index + 1) % 3;
	if (keycode == 36 || keycode == 76)
		ft_preset_menu_key_event_p2(vars);
	vars->win_ch[1] = 1;
	return (0);
}

int		ft_color_menu_key_event(int keycode, t_vars *vars)
{
	char	key;

	key = get_key(keycode);
	if ((key >= 0 && key <= 9) || (key >= 'a' && key <= 'f'))
	{
		vars->color_set[vars->index] = ((vars->color_set[vars->index] << 4)
				& 0x00FFFFF0) + (ft_isalpha(key) ? (unsigned int)(key - 'a' + 10) : (unsigned int)key);
	}
	if (keycode == 36 || keycode == 76)
	{
		vars->index = (vars->index + 1) % vars->nb_color_set;
		printf("ITS GOING THERE|%d\n", vars->index);
		if (!vars->index)
		{
			if (vars->colors)
				free(vars->colors);
			ft_set_colors(vars);
			vars->menumode = 0;
			vars->win_ch[0] = 1;
		}
	}
	vars->win_ch[1] = 1;
	return (0);
}

int		ft_default_menu_key_event(int keycode, t_vars *vars)
{
	char	val;

	val = get_key(keycode);
	if (!vars->index && val >= 0 && val <= 9)
	{
		vars->itermax = ((vars->itermax * 10) + val) % 500;
		vars->win_ch[0] = 1;
		vars->win_ch[1] = 1;
	}
	return (0);
}

int		ft_menu_key_event(int keycode, t_vars *vars)
{
	int	val;

	if (vars->menumode == 0)
		ft_default_menu_key_event(keycode, vars);
	else if (vars->menumode == 1)
		ft_preset_menu_key_event(keycode, vars);
	else if (vars->menumode == 2)
		ft_color_menu_key_event(keycode, vars);
	return (0);
}

int		ft_menu_mouse_release_event(int button, int x, int y, t_vars *vars)
{
	return (0);
}
