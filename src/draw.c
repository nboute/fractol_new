/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 17:56:16 by niboute           #+#    #+#             */
/*   Updated: 2019/10/19 14:53:21 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "../inc/header.h"

void			calc_xvals(t_vars *vars)
{
	int			i;

	i = 0;
	while (i < MAINWINWID)
	{
		if (vars->fractal != 1)
			vars->tmpx[i] = ft_dmap(i, MAINWINWID,
					vars->xmin, vars->xmax);
		else
			vars->tmpx[i] = 1.5 * (double)((i - (MAINWINWID / 2))) /
				((double)((vars->zoom * MAINWINWID) / 2)) + vars->padx;
		i++;
	}
}

int				draw(t_mlx *mlx)
{
	t_thread	thread[CPU_THREADS];
	int			i;

	calc_xvals(&mlx->chvars);
	i = 0;
	while (i < CPU_THREADS)
	{
		thread[i].y = i;
		thread[i].mlx = mlx;
		if (pthread_create(&thread[i].thread, NULL, draw_fractal_x, &thread[i]))
			return (0);
		i++;
	}
	i = 0;
	while (i < CPU_THREADS)
		pthread_join(thread[i++].thread, NULL);
	mlx_put_image_to_window(mlx->mlx, mlx->mainwin.win, mlx->mainwin.img, 0, 0);
	return (1);
}

void			*select_fractal(unsigned char choice)
{
	if (!choice)
		return (draw_mandelbrot_point);
	else if (choice == 1)
		return (draw_julia_point);
	else if (choice == 2)
		return (draw_burning_ship_point);
	return (NULL);
}

int				draw_fractal(t_mlx *mlx)
{
	if (select_fractal(mlx->chvars.fractal))
	{
		mlx->fractal_draw = select_fractal(mlx->chvars.fractal);
		return (draw(mlx));
	}
	return (1);
}
