/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 20:12:25 by niboute           #+#    #+#             */
/*   Updated: 2019/10/16 17:37:34 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

#include <unistd.h>
#include "../minilibx_macos/mlx.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int		ft_exit(int err)
{
	if (err)
		ft_putstr("An error has occured\n");
	exit(-1);
}

int		init_default_menu_p2(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < BUTTONS)
		mlx->chvars.btns_vals[i++] = NULL;
//	if (!(mlx->chvars.color_hex = (char*)malloc(sizeof(char) * 11)))
//		return (0);
	return (1);
}

int		init_default_menu(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < BUTTONS)
		mlx->chvars.btns_cols[i++] = BLACK;
	if (!(mlx->chvars.btns_txt[0] = ft_strdup("iter +/-")))
		return (0);
	if (!(mlx->chvars.btns_txt[1] = ft_strdup("vary col")))
		return (0);
	if (!(mlx->chvars.btns_txt[2] = ft_strdup("<fractal>")))
		return (0);
	if (!(mlx->chvars.btns_txt[3] = ft_strdup("reset")))
		return (0);
	if (!(mlx->chvars.btns_txt[4] = ft_strdup("Zoom (power)")))
		return (0);
	if (!(mlx->chvars.btns_txt[5] = ft_strdup("ch colors")))
		return (0);
	if (!(init_default_menu_p2(mlx)))
		return (0);
	mlx->chvars.win_ch[1] = 1;
	return (1);
}

void	set_vars_p2(t_vars *vars)
{
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
}

int		set_vars(t_vars *vars, char *name)
{
	int	i;

	i = 0;
	if (!(vars->fract_names[0] = ft_strdup("mandelbrot")))
		return (0);
	if (!(vars->fract_names[1] = ft_strdup("julia")))
		return (0);
	if (!(vars->fract_names[2] = ft_strdup("burning_ship")))
		return (0);
	vars->fractal = 3;
	while (i < NB_FRACTS)
	{
		if (!ft_strcmp(name, vars->fract_names[i]))
			vars->fractal = i;
		i++;
	}
	if (vars->fractal >= 3)
	{
		ft_putendl("Invalid name, fractal set to mandelbrot as default");
		vars->fractal = 0;
	}
	set_vars_p2(vars);
	return (1);
}

int		main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac != 2)
	{
		ft_putendl_fd("usage: ./fractol \
		[fractal_name {\"julia\", \"mandelbrot\", \"burning_ship\"}]", 2);
		return (0);
	}
	ac--;
	av++;
	if (!set_vars(&mlx.chvars, *av))
		ft_exit(1);
	if (!setup_mlx(&mlx))
		ft_exit(1);
	mlx_hook(mlx.mainwin.win, 17, 1L << 17, ft_exit, (void*)1);
	if (!(init_default_menu(&mlx)))
		ft_exit(1);
	ft_putendl("Initialization finished");
	mlx_loop_hook(mlx.mlx, loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
