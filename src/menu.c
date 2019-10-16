/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:44:40 by niboute           #+#    #+#             */
/*   Updated: 2019/10/16 17:40:05 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_macos/mlx.h"
#include "../inc/header.h"
#include <stdlib.h>
#include <stdio.h>

void	draw_buttons(t_mlx *mlx, t_win *win)
{
	int	x;
	int	y;
	int	curr_btn;

	y = -1;
	while (++y < win->hei)
	{
		x = -1;
		while (++x < win->wid)
		{
			curr_btn = (x * BTN_COL) / win->wid +
				BTN_COL * ((BTN_ROW * y) / (win->hei));
			if ((x % (win->wid / BTN_COL)) == 0 || x == win->wid - 1
				|| (y % (win->hei / BTN_ROW) == 0) || y == win->hei - 1)
				*(unsigned*)(win->data + ((win->bpx / 8) * x) +
						(win->size_line) * y) = WHITE;
			else
				*(unsigned*)(win->data + ((win->bpx / 8) * x) + (win->size_line)
						* y) = mlx->chvars.btns_cols[curr_btn];
		}
	}
	mlx_put_image_to_window(mlx->mlx, win->win, win->img, 0, 0);
}

void	draw_btns_names(t_mlx *mlx, t_win *win)
{
	int	i;
	int	buthei;
	int	butwid;

	i = 0;
	butwid = win->wid / BTN_COL;
	buthei = win->hei / BTN_ROW;
	while (i < BUTTONS)
	{
		mlx_string_put(mlx->mlx, win->win, ((i % BTN_COL) * butwid + butwid / 2
				- 5 * ft_strlen(mlx->chvars.btns_txt[i])),
				((i / BTN_COL) * buthei + (3 * buthei) / (BTN_ROW * 5))
				, 0x00FFFFFF, mlx->chvars.btns_txt[i]);
		if (mlx->chvars.btns_vals[i])
		{
			mlx_string_put(mlx->mlx, win->win, ((i % BTN_COL) * butwid +
						butwid / 2 - 5 * ft_strlen(mlx->chvars.btns_vals[i])),
				((i / BTN_COL) * buthei + (6 * buthei) / (BTN_ROW * 5))
				, 0x00FFFFFF, mlx->chvars.btns_vals[i]);
		}
		i++;
	}
}

int		determine_buttons_values(t_vars *vars)
{
	if (vars->variter != 0)
		vars->btns_cols[0] = vars->variter == 1 ? LIGHT_GREEN : RED;
	else
		vars->btns_cols[0] = BLACK;
	if (vars->colvar != 0)
		vars->btns_cols[1] = vars->colvar == 1 ? LIGHT_GREEN : RED;
	else
		vars->btns_cols[1] = BLACK;
	if (vars->btns_vals[0])
		free(vars->btns_vals[0]);
	if (!(vars->btns_vals[0] = ft_itoa(vars->itermax)))
		return (0);
	if (vars->btns_vals[1])
		free(vars->btns_vals[1]);
	if (!(vars->btns_vals[1] = ft_itoa(vars->colvar)))
		return (0);
	vars->btns_vals[2] = vars->fract_names[vars->fractal];
	if (vars->btns_vals[4])
		free(vars->btns_vals[4]);
	if (!(vars->btns_vals[4] = ft_itoa(vars->zpow)))
		return (0);
	return (1);
}

void	draw_default_menu(t_mlx *mlx)
{
	draw_buttons(mlx, &mlx->menuwin);
	draw_btns_names(mlx, &mlx->menuwin);
}

int				draw_color_presets_menu_p2(t_mlx *mlx, int index)
{
	char		*tmp;

	if (!(tmp = ft_itoa(mlx->chvars.nb_color_grad)))
		return (0);
	mlx_string_put(mlx->mlx, mlx->menuwin.win,
			(MENUWINWID / 2 - (MENUWINWID / 128) * ft_strlen(tmp)),
				MENUWINHEI / 2 + MENUWINHEI / 10 ,
				index == 1 ? RED : WHITE, tmp);
	free(tmp);
	tmp = "VALIDATE";
	mlx_string_put(mlx->mlx, mlx->menuwin.win,
			(MENUWINWID / 2 - (MENUWINWID / 75) * ft_strlen(tmp)),
				(MENUWINHEI * 3) / 4 + MENUWINHEI / 10 ,
				index == 2 ? LIGHT_GREEN : WHITE, tmp);
	return (1);
}

int				draw_color_presets_menu(t_mlx *mlx, int index)
{
	const char	*str1;
	const char	*str2;
	char		*tmp;

	str1 = "Choose number of colors (2-20)";
	str2 = "Choose number of color gradients (1-100)";
	mlx_string_put(mlx->mlx, mlx->menuwin.win,
			(MENUWINWID / 2 - ft_strlen(str1) * 5),
				MENUWINHEI / 8 , index == 0 ? YELLOW : WHITE, (char*)str1);
	mlx_string_put(mlx->mlx, mlx->menuwin.win,
		(MENUWINWID / 2 - ft_strlen(str2) * 5),
			(MENUWINHEI) / 2 , index == 1 ? YELLOW : WHITE,
			(char*)str2);
	if (!(tmp = ft_itoa(mlx->chvars.nb_color_set)))
		return (0);
	mlx_string_put(mlx->mlx, mlx->menuwin.win,
			(MENUWINWID / 2 - (MENUWINWID / 128) * ft_strlen(tmp)),
				MENUWINHEI / 4,
				index == 0 ? RED : WHITE, tmp);
	free(tmp);
	return (draw_color_presets_menu_p2(mlx, index));
}

void			fill_color_menu_string(t_vars *vars, char *str)
{
	str[0] = '\0';
	ft_strcpy(str, "COLOR XX/XX:");
	str[6] = (vars->index + 1) / 10 + '0';
	str[7] = (vars->index + 1) % 10 + '0';
	str[9] = vars->nb_color_set / 10 + '0';
	str[10] = vars->nb_color_set % 10 + '0';
}

void			choose_color_menu(t_mlx *mlx)
{
	int			i;
	int			j;

	fill_color_menu_string(&mlx->chvars, (char*)mlx->chvars.color_menu_text);
	ft_strcpy_hextoa((char*)mlx->chvars.color_hex,
		mlx->chvars.color_set[mlx->chvars.index], 1);
	i = MENUWINHEI / 8;
	if (mlx->chvars.color_set)
		while (i < MENUWINHEI)
		{
			j = -1;
			while (++j < MENUWINWID)
				*(unsigned*)(mlx->menuwin.data + j * (mlx->menuwin.bpx / 8) +
						i * mlx->menuwin.size_line) =
					mlx->chvars.color_set[mlx->chvars.index];
			i++;
		}
	mlx_put_image_to_window(mlx->mlx, mlx->menuwin.win, mlx->menuwin.img, 0, 0);
	mlx_string_put(mlx->mlx, mlx->menuwin.win, 5, 0, WHITE,
		mlx->chvars.color_menu_text);
	mlx_string_put(mlx->mlx, mlx->menuwin.win, MENUWINWID / 3, 0, WHITE,
		mlx->chvars.color_hex);
}

void	draw_menu_x(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->menuwin.win, mlx->menuwin.img, 0, 0);
	if (!mlx->chvars.menumode)
	{
		if (!determine_buttons_values(&mlx->chvars))
			ft_exit(1);
		draw_default_menu(mlx);
	}
	else if (mlx->chvars.menumode == 1)
	{
		if (!draw_color_presets_menu(mlx, mlx->chvars.index))
			ft_exit(1);
	}
	else if (mlx->chvars.menumode == 2)
		choose_color_menu(mlx);
}
