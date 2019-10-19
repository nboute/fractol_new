/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:23:45 by niboute           #+#    #+#             */
/*   Updated: 2019/10/19 15:01:16 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <math.h>

void	translate_default_fracts(int keycode, t_vars *vars)
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

void	translate_julia(int keycode, t_vars *vars)
{
	if (keycode == 123 || keycode == 124)
	{
		vars->padx += keycode == 124 ? (double)0.1 / (double)vars->zoom
		: -((double)0.1 / (double)vars->zoom);
	}
	if (keycode == 125 || keycode == 126)
	{
		vars->pady += keycode == 125 ? (double)0.1 / (double)vars->zoom
		: -((double)0.1 / (double)vars->zoom);
	}
}

void	adapt_padding(int button, int x, int y, t_vars *vars)
{
	if (vars->fractal == 1 && button == 1)
	{
		vars->padx += ft_dmap(x, MAINWINWID, -1.5, 1.5)
			/ (double)(vars->zoom / 2);
		vars->pady += ft_dmap(y, MAINWINHEI, -1.125, 1.125)
			/ (double)(vars->zoom / 2);
	}
	if (vars->fractal == 1 && button == 2 && vars->zoom != 1)
	{
		vars->padx -= (vars->padx / 2) / (double)(vars->zoom);
		vars->pady -= (vars->pady / 2) / (double)(vars->zoom);
	}
	if (vars->zoom == 1)
	{
		vars->padx = 0;
		vars->pady = 0;
		if (vars->fractal != 1)
		{
			vars->xmin = -2;
			vars->xmax = vars->xmin + (2.5 / (double)(vars->zoom));
			vars->ymin = -1;
			vars->ymax = vars->ymin + (double)2 / (double)(vars->zoom);
		}
	}
}

void	zoom(int button, int x, int y, t_vars *vars)
{
	if (button == 1 || button == 2)
	{
		if ((button == 1 && vars->zpow < POW_MAX)
			|| (button == 2 && vars->zpow > 0))
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
		adapt_padding(button, x, y, vars);
		vars->win_ch[0] = 1;
		vars->win_ch[1] = 1;
	}
}
