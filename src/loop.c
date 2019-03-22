/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:58:44 by niboute           #+#    #+#             */
/*   Updated: 2019/03/22 06:59:05 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <math.h>
#include "../minilibx_macos/mlx.h"


int			ft_loop(t_mlx *mlx)
{
	if (mlx->chvars->win_ch[0] != 0)
	{
		mlx_destroy_image(mlx->mlx, mlx->mainwin->img);
		mlx->mainwin->img = mlx_new_image(mlx->mlx, MAINWINWID, MAINWINHEI);
		mlx->mainwin->data = mlx_get_data_addr(mlx->mainwin->img,
				&mlx->mainwin->bpx, &mlx->mainwin->size_line,
				&mlx->mainwin->endian);
		mlx_put_image_to_window(mlx->mlx, mlx->mainwin->win, mlx->mainwin->img,
			0, 0);
		mlx->chvars->win_ch[0] = 0;
	}
	if (mlx->chvars->win_ch[1])
	{
		mlx_destroy_image(mlx->mlx, mlx->menuwin->img);
		mlx->menuwin->img = mlx_new_image(mlx->mlx, MENUWINWID, MENUWINHEI);
		mlx->menuwin->data = mlx_get_data_addr(mlx->menuwin->img,
				&mlx->menuwin->bpx, &mlx->menuwin->size_line,
				&mlx->menuwin->endian);
		ft_draw_default_menu(mlx);
	}
	return (0);
}
