/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:58:44 by niboute           #+#    #+#             */
/*   Updated: 2019/10/16 17:41:45 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <math.h>
#include "../minilibx_macos/mlx.h"
#include <stdio.h>

int			reset_fractal(t_vars *vars)
{
	vars->zoom = 1;
	if (vars->fractal != 1)
	{
		vars->xmin = -2;
		vars->xmax = vars->xmin + (2.5 / (double)(vars->zoom));
		vars->ymin = -1;
		vars->ymax = vars->ymin + (double)2 / (double)(vars->zoom);
	}
	else
	{
		vars->xmin = -1.25;
		vars->ymin = 1.25;
	}
	vars->padx = 0;
	vars->pady = 0;
	vars->zpow = 0;
	vars->variter = 0;
	vars->itermax = 100;
	vars->win_ch[0] = 1;
	return (0);
}

void	repeat_events(t_vars *vars)
{
	if (vars->variter)
	{
		if (vars->itermax > 0 || vars->variter != -1)
		vars->itermax += vars->variter;
		vars->win_ch[0] = 1;
		vars->win_ch[1] = 1;
	}
	if (vars->colvar)
	{
		vars->varyval = vars->varyval + vars->colvar;
		if (vars->varyval < 0)
			vars->varyval += vars->nb_cols;
		else
			vars->varyval %= vars->nb_cols;
		vars->win_ch[0] = 1;
	}
}


int			loop(t_mlx *mlx)
{
	repeat_events(&mlx->chvars);
	if (mlx->chvars.win_ch[0] != 0)
	{
		mlx_destroy_image(mlx->mlx, mlx->mainwin.img);
		mlx->mainwin.img = mlx_new_image(mlx->mlx, MAINWINWID, MAINWINHEI);
		mlx->mainwin.data = mlx_get_data_addr(mlx->mainwin.img,
				&mlx->mainwin.bpx, &mlx->mainwin.size_line,
				&mlx->mainwin.endian);
		mlx_put_image_to_window(mlx->mlx, mlx->mainwin.win, mlx->mainwin.img,
			0, 0);
		mlx->chvars.win_ch[0] = 0;
		draw_fractal(mlx);
	}
	if (mlx->chvars.win_ch[1])
	{
		mlx_destroy_image(mlx->mlx, mlx->menuwin.img);
		mlx->menuwin.img = mlx_new_image(mlx->mlx, MENUWINWID, MENUWINHEI);
		mlx->menuwin.data = mlx_get_data_addr(mlx->menuwin.img,
				&mlx->menuwin.bpx, &mlx->menuwin.size_line,
				&mlx->menuwin.endian);
		draw_menu_x(mlx);
		mlx->chvars.win_ch[1] = 0;
	}
	return (0);
}
