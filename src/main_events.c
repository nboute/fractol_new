/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:27:55 by niboute           #+#    #+#             */
/*   Updated: 2019/04/07 18:01:04 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <stdio.h>
#include <math.h>

int		ft_main_mouse_event(int button, int x, int y, t_vars *vars)
{
	if (x < 0 || x > MAINWINWID || y < 0 || y > MAINWINHEI)
		return (-1);
	if (button == 1 || button == 2)
	{
		if ((button == 1 && vars->zpow < POW_MAX) || (button == 2 && vars->zpow > 0))
			vars->zpow += (button == 1) ? 1 : -1;
		vars->zoom = ft_power(2, vars->zpow);
		if (vars->fractal != 1)
		{
			vars->xmin = ft_dmap(x, MAINWINWID, vars->xmin, vars->xmax) -
				(1.25 / (double)vars->zoom);
			vars->xmax = vars->xmin + (2.5 / (double)vars->zoom);
			vars->ymin = ft_dmap(y, MAINWINHEI, vars->ymin, vars->ymax) -
				((double)1 / (double)vars->zoom);
			vars->ymax = vars->ymin + (double)2 / (double)vars->zoom;
		}
		else
			vars->vary = vars->zoom == 1 ? 1 : 0;
		if (vars->fractal == 1 && button == 1)
		{
			vars->padx += ft_dmap(x, MAINWINWID, -2, 2) / (double)(vars->zoom);
			vars->pady += ft_dmap(y, MAINWINHEI, -2, 2) / (double)(vars->zoom);
		}
		if (vars->fractal == 1 && button == 2)
		{
			vars->padx -= vars->padx / (double)(vars->zoom);
			vars->pady -= vars->pady / (double)(vars->zoom);
		}
//		set_fractal_values(vars);
		vars->win_ch[0] = 1;
	}
	return (0);
}

void	ft_translate_default_fracts(int keycode, t_vars *vars)
{
	double	pad;

	if (keycode == 123 || keycode == 124)
	{
		pad = fabs(vars->xmax - vars->xmin) / (double)5;
		vars->xmin += (keycode == 124) ? pad : -pad;
		vars->xmax += (keycode == 124) ? pad : -pad;
	}
	if (keycode == 125 || keycode == 126)
	{
		pad = fabs(vars->ymax - vars->ymin) / (double)5;
		vars->ymin += (keycode == 125) ? pad : -pad;
		vars->ymax += (keycode == 125) ? pad : -pad;
	}
}

void	ft_translate_julia(int keycode, t_vars *vars)
{
	if (keycode == 123 || keycode == 124)
	{
		vars->padx += keycode == 124 ? (double)1 / (double)vars->zoom :
			-((double)1 / (double)vars->zoom);
	}
	if (keycode == 125 || keycode == 126)
	{
		vars->pady += keycode == 125 ? (double)1 / (double)vars->zoom :
			-((double)1 / (double)vars->zoom);
	}
}

int		ft_main_key_event(int keycode, t_vars *vars)
{
	if (keycode >= 123 && keycode <= 126)
	{
		if (vars->fractal != 1)
			ft_translate_default_fracts(keycode, vars);
		else
			ft_translate_julia(keycode, vars);
		vars->win_ch[0] = 1;
	}
	if (keycode == 49)
		vars->vary = vars->vary ? 0 : 1;
	if (keycode == 53)
		ft_exit(0);
	return (0);
}

int		ft_main_mouse_hover_event(int x, int y, t_vars *vars)
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
