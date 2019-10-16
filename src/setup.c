/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:44:31 by niboute           #+#    #+#             */
/*   Updated: 2019/10/11 16:15:15 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <stdlib.h>
#include "../minilibx_macos/mlx.h"
#include <stdio.h>


int				init_menu_win(t_mlx *mlx)
{
	mlx->menuwin.wid = MENUWINWID;
	mlx->menuwin.hei = MENUWINHEI;
	if (!(mlx->menuwin.win =
				mlx_new_window(mlx->mlx, MENUWINWID, MENUWINHEI, "Menu")))
		return (0);
	if (mlx->menuwin.img)
		mlx_destroy_image(mlx->mlx, mlx->menuwin.img);
	if (!(mlx->menuwin.img = mlx_new_image(mlx->mlx, MENUWINWID, MENUWINHEI)))
		return (0);
	if (!(mlx->menuwin.data =
				mlx_get_data_addr(mlx->menuwin.img, &mlx->menuwin.bpx,
					&mlx->menuwin.size_line, &mlx->menuwin.endian)))
		return (0);
	mlx_hook(mlx->menuwin.win, 17, 1L << 17, init_menu_win, (void*)mlx);
	mlx_hook(mlx->menuwin.win, 5, 1L << 3, menu_mouse_release_event,
			&mlx->chvars);
	mlx_mouse_hook(mlx->menuwin.win, menu_mouse_event, &mlx->chvars);
	mlx_key_hook(mlx->menuwin.win, menu_key_event, &mlx->chvars);
	mlx->chvars.win_ch[1] = 1;
	return (1);
}

t_mlx			*setup_mlx_p2(t_mlx *mlx)
{
	if (!(mlx->mlx = mlx_init()))
		return (NULL);
	mlx->menuwin.img = NULL;
	if (!(mlx->mainwin.win =
				mlx_new_window(mlx->mlx, MAINWINWID, MAINWINHEI, "Fractol")))
		return (NULL);
	mlx->mainwin.wid = MAINWINWID;
	mlx->mainwin.hei = MAINWINHEI;
	if (!(mlx->mainwin.img = mlx_new_image(mlx->mlx, MAINWINWID, MAINWINHEI)))
		return (NULL);
	if (!(mlx->mainwin.data =
				mlx_get_data_addr(mlx->mainwin.img, &mlx->mainwin.bpx,
					&mlx->mainwin.size_line, &mlx->mainwin.endian)))
		return (NULL);
	mlx_hook(mlx->mainwin.win, 6, 1L << 6, main_mouse_hover_event, &mlx->chvars);
	mlx_mouse_hook(mlx->mainwin.win, main_mouse_event, &mlx->chvars);
	mlx_key_hook(mlx->mainwin.win, main_key_event, &mlx->chvars);
	return (init_menu_win(mlx) != 0 ? mlx : NULL);
}

t_mlx			*setup_mlx(t_mlx *mlx)
{
	reset_fractal(&mlx->chvars);
	set_default_colors(&mlx->chvars);
	return (setup_mlx_p2(mlx));
}
