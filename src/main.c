/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 20:12:25 by niboute           #+#    #+#             */
/*   Updated: 2019/04/07 17:59:36 by niboute          ###   ########.fr       */
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
	if (err)
		ft_putstr("An error has occured\n");
	exit(-1);
}

int		ft_init_default_menu_p2(t_mlx *mlx)
{
	int	i;

	if (!(mlx->chvars->btns_vals = (char**)malloc(sizeof(char*) *
					(BUTTONS + 1))))
		return (-1);
	i = 0;
	while (i <= BUTTONS)
		mlx->chvars->btns_vals[i++] = NULL;
	printf("[Q]%s\n", mlx->chvars->fract_names[mlx->chvars->fractal]);
	return (0);
}

int		ft_init_default_menu(t_mlx *mlx)
{
	int	i;
	printf("[O]%s\n", *(mlx->chvars->fract_names));
	if (!(mlx->chvars->btns_cols = (unsigned int*)malloc(sizeof(int) * BUTTONS)))
		return (-1);
	i = 0;
	while (i < BUTTONS)
		mlx->chvars->btns_cols[i++] = BLACK;
	if (!(mlx->chvars->btns_txt = (char**)malloc(sizeof(char*) *
					(BUTTONS + 1))))
		return (-1);
	mlx->chvars->btns_txt[BUTTONS] = NULL;
	mlx->chvars->btns_txt[0] = ft_strdup("iter +/-");
	mlx->chvars->btns_txt[1] = ft_strdup("vary col");
	mlx->chvars->btns_txt[2] = ft_strdup("< fractal >");
	mlx->chvars->btns_txt[3] = ft_strdup("reset");
	mlx->chvars->btns_txt[4] = ft_strdup("void");
	mlx->chvars->btns_txt[5] = ft_strdup("void");
	mlx->chvars->btns_txt[6] = ft_strdup("void");
	mlx->chvars->btns_txt[7] = ft_strdup("void");
	mlx->chvars->btns_txt[8] = ft_strdup("ch colors");
	ft_init_default_menu_p2(mlx);
	mlx->chvars->win_ch[1] = 1;
	return (0);
}

int		ft_set_vars(t_vars *vars, char *name)
{
	int	i;

	i = 0;
	if (!(vars->fract_names = (char**)malloc(sizeof(char*) * (NB_FRACTS + 1))))
		return (-1);
	vars->fract_names[0] = ft_strdup("mandelbrot");
	vars->fract_names[1] = ft_strdup("julia");
	vars->fract_names[2] = ft_strdup("burning_ship");
	vars->fract_names[3] = NULL;
	vars->fractal = 3;
	while (i < NB_FRACTS)
	{
		printf("%s\n", vars->fract_names[i]);
		if (!ft_strcmp(name, vars->fract_names[i]))
			vars->fractal = i;
		i++;
	}
	if (vars->fractal >= 3)
	{
		ft_putendl("Invalid name, fractal set to mandelbrot as default");
		vars->fractal = 0;
	}
	vars->vary = 1;
	vars->zoom = 1;
	vars->zpow = 0;
	vars->win_ch[0] = 1;
	vars->color_set = NULL;
	vars->nb_color_set = 0;
	vars->nb_color_grad = 0;
	vars->nb_cols = 0;
	vars->colors = NULL;
	vars->index = 0;
	vars->menumode = 0;
	vars->varyval = 0;
	vars->colvar = 0;
	vars->itermax = 100;
	vars->variter = 0;
	return (0);
}

int		main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac != 2)
		return (0);
	ac--;
	av++;
	if (!(mlx.chvars = (t_vars*)malloc(sizeof(t_vars))))
		return (-1);
	if (ft_set_vars(mlx.chvars, *av))
		return (-1);
	if (!ft_setup_mlx(&mlx))
	{
		ft_putendl("An error occured\n");
	}
	printf("%s\n", *(mlx.chvars->fract_names));
	mlx_hook(mlx.mainwin->win, 17, 1L << 17, ft_exit, (void*)1);
	ft_init_default_menu(&mlx);
	mlx_loop_hook(mlx.mlx, ft_loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
