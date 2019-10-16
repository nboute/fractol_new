/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:07:50 by niboute           #+#    #+#             */
/*   Updated: 2019/10/11 16:30:00 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <math.h>

int		draw_julia_point(double zx, double zy, t_vars *vars)
{
	double	tmp;
	int		iter;

	iter = 0;
	while (zx * zx + zy * zy < 4 && iter < vars->itermax)
	{
		tmp = zx * zx - zy * zy + vars->xmin;
		zy = 2 * zx * zy + vars->ymin;
		zx = tmp;
		iter++;
	}
	if (vars->colors)
		return (vars->colors[(iter + vars->varyval) % vars->nb_cols]);
	else
		return (iter == vars->itermax ? WHITE : BLACK);
}

int		draw_mandelbrot_point(double cx, double cy, t_vars *vars)
{
	double	zx;
	double	zy;
	double	tmp;
	int		iter;

	cx += vars->padx;
	cy += vars->pady;
	zx = 0;
	zy = 0;
	iter = 0;
	while (zx * zx + zy * zy < 4 && iter < vars->itermax)
	{
		tmp = zx * zx - zy * zy + cx;
		zy = 2 * zx * zy + cy;
		zx = tmp;
		iter++;
	}
	if (vars->colors)
		return (vars->colors[(iter + vars->varyval) % vars->nb_cols]);
	else
		return (iter == vars->itermax ? WHITE : BLACK);
}
int		draw_burning_ship_point(double cx, double cy, t_vars *vars)
{
	double	zx;
	double	zy;
	double	tmp;
	int		iter;

	cx += vars->padx;
	cy += vars->pady;
	zx = 0;
	zy = 0;
	iter = 0;
	while (zx * zx + zy * zy < 4 && iter < vars->itermax)
	{
		tmp = fabs(zx * zx - zy * zy + cx);
		zy = fabs(2 * zx * zy + cy);
		zx = tmp;
		iter++;
	}
	if (vars->colors)
		return (vars->colors[(iter + vars->varyval) % vars->nb_cols]);
	else
		return (iter == vars->itermax ? WHITE : BLACK);
}

void	*draw_fractal_x(void *ptr)
{
	t_mlx	*mlx;
	int		x;
	int		y;
	int		ymax;
	double	tmpy;

	mlx = (t_mlx*)(((t_thread*)(ptr))->mlx);
	y = ((t_thread*)ptr)->y * MAINWINHEI / CPU_THREADS;
	ymax = y + MAINWINHEI / CPU_THREADS;
	while (y < ymax)
	{
		x = 0;
		tmpy = mlx->chvars.fractal == 1 ? ((double)(y - MAINWINHEI / 2)
			/ (double)(MAINWINHEI * mlx->chvars.zoom / 2)) + mlx->chvars.pady
			: ft_dmap(y, MAINWINHEI, mlx->chvars.ymin, mlx->chvars.ymax);
		while (x < MAINWINWID)
		{
			*(unsigned*)(mlx->mainwin.data + y * mlx->mainwin.size_line
				+ x * (mlx->mainwin.bpx / 8))
				= mlx->fractal_draw(mlx->chvars.tmpx[x], tmpy, &mlx->chvars);
			x++;
		}
		y++;
	}
	return (NULL);
}
