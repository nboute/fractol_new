/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 20:12:25 by niboute           #+#    #+#             */
/*   Updated: 2019/03/22 07:03:00 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

#include <unistd.h>
#include "../minilibx_macos/mlx.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int		ft_exit(int err)
{
	printf("An error has occured\n");
	exit(-1);
}

int		ft_main_key_event(int keycode, t_vars *vars)
{
	vars = NULL;
	if (keycode == 53)
		ft_exit(0);
	return (0);
}

int		ft_init_default_menu(t_mlx *mlx)
{
	if (!(mlx->chvars->btns_cols = (unsigned int*)malloc(sizeof(int) * BUTTONS)))
		return (-1);
	ft_bzero((void*)mlx->chvars->btns_cols, BUTTONS * sizeof(int));
	if (!(mlx->chvars->btns_txt = (char**)malloc(sizeof(char*) *
					(BUTTONS + 1))))
		return (-1);
	mlx->chvars->btns_txt[BUTTONS] = NULL;
	mlx->chvars->btns_txt[0] = ft_strdup("rot X");
	mlx->chvars->btns_txt[1] = ft_strdup("rot Y");
	mlx->chvars->btns_txt[2] = ft_strdup("rot Z");
	mlx->chvars->btns_txt[3] = ft_strdup("reset");
	mlx->chvars->btns_txt[4] = ft_strdup("rotspd +/-");
	mlx->chvars->btns_txt[5] = ft_strdup("zoom +/-");
	mlx->chvars->btns_txt[6] = ft_strdup("red");
	mlx->chvars->btns_txt[7] = ft_strdup("green");
	mlx->chvars->btns_txt[8] = ft_strdup("blue");
	ft_draw_default_menu(mlx);
	return (0);
}

int		main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac != 2)
		return (0);
	if (!(mlx.chvars = (t_vars*)malloc(sizeof(t_vars))))
		return (-1);
	if (!ft_setup_mlx(&mlx))
	{
		ft_putendl("An error occured\n");
	}
	mlx_hook(mlx.mainwin->win, 17, 1L << 17, ft_exit, (void*)1);
	ft_init_default_menu(&mlx);
	mlx_loop_hook(mlx.mlx, ft_loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
