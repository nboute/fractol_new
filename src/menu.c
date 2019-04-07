/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:44:40 by niboute           #+#    #+#             */
/*   Updated: 2019/04/07 18:04:09 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_macos/mlx.h"
#include "../inc/header.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_draw_buttons(t_mlx *mlx, t_win *win)
{
	int	x;
	int	y;
	int	curr_btn;

	y = 0;
	x = 0;
	while (y < win->hei)
	{
		x = 0;
		while (x < win->wid)
		{
			curr_btn = (x * BTN_ROW) / win->wid +
				BTN_COL * ((BTN_COL * y) / (win->hei));
			if ((x % (win->wid / BTN_COL)) == 0 ||
					(y % (win->hei / BTN_ROW) == 0))
				*(unsigned*)(win->data + ((win->bpx / 8) * x) +
						(win->size_line) * y) = WHITE;
			else
				*(unsigned*)(win->data + ((win->bpx / 8) * x) + (win->size_line)
						* y) = mlx->chvars->btns_cols[curr_btn];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, win->win, win->img, 0, 0);
}

void	ft_draw_btns_names(t_mlx *mlx, t_win *win)
{
	int	i;
	int	buthei;
	int	butwid;

	i = 0;
	butwid = win->wid / BTN_ROW;
	buthei = win->hei / BTN_COL;
	while (i < BUTTONS)
	{
		printf("A\n");
		mlx_string_put(mlx->mlx, win->win, ((i % BTN_ROW) * butwid + butwid / 2
				- 5 * ft_strlen(mlx->chvars->btns_txt[i])),
				((i / BTN_COL) * buthei + (6 * buthei) / (BTN_COL * 5))
				, 0x00FFFFFF, mlx->chvars->btns_txt[i]);
//		printf("%p\n", mlx->chvars->btns_vals);
		if (mlx->chvars->btns_vals[i])
		{
			mlx_string_put(mlx->mlx, win->win, ((i % BTN_ROW) * butwid +
						butwid / 2 - 5 * ft_strlen(mlx->chvars->btns_vals[i])),
				((i / BTN_COL) * buthei + 20 + (6 * buthei) / (BTN_COL * 5))
				, 0x00FFFFFF, mlx->chvars->btns_vals[i]);
		}
//		printf("A\n");
//		mlx_string_put(mlx->mlx, win->win, ((i % BTN_ROW) * butwid + butwid / 2
//				- (butwid / 32) * ft_strlen(mlx->chvars->btns_txt[i])),
//				((i / BTN_COL) * buthei + (6 * buthei) + 10 / (BTN_COL * 5))
//				, 0x00FFFFFF, mlx->chvars->btns_txt_2[i]);
//		if (i >= 6)
//			ft_draw_color_val(i, mlx, buthei,
//					((i % BTN_ROW) * butwid + butwid / 2) - (butwid / 32) * 3);
		i++;
	}
}

void	ft_determine_buttons_values(t_vars *vars)
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
	vars->btns_vals[0] = ft_itoa(vars->itermax);
	if (vars->btns_vals[1])
		free(vars->btns_vals[1]);
	vars->btns_vals[1] = ft_itoa(vars->colvar);
	printf("|%d|%p|%s\n", vars->fractal, vars->fract_names, vars->fract_names[vars->fractal]);
	vars->btns_vals[2] = vars->fract_names[vars->fractal];
}

void	ft_draw_default_menu(t_mlx *mlx)
{
	printf("MENU MODE 1|%d\n", mlx->chvars->fractal);
	ft_determine_buttons_values(mlx->chvars);
	printf("MENU MODE 1 P2\n");
	ft_draw_buttons(mlx, mlx->menuwin);
	printf("MENU MODE 1 P3\n");
	ft_draw_btns_names(mlx, mlx->menuwin);
	printf("BBBBBA\n");
}

void	ft_draw_color_presets_menu_p2(t_mlx *mlx, int index)
{
	char	*tmp;

	tmp = ft_itoa(mlx->chvars->nb_color_grad);
	mlx_string_put(mlx->mlx, mlx->menuwin->win,
			(MENUWINWID / 2 - (MENUWINWID / 128) * ft_strlen(tmp)),
				(MENUWINHEI) / 2 + MENUWINHEI / 10 ,
				index == 1 ? RED : WHITE, tmp);
	free(tmp);
	tmp = "VALIDATE";
	mlx_string_put(mlx->mlx, mlx->menuwin->win,
			(MENUWINWID / 2 - (MENUWINWID / 75) * ft_strlen(tmp)),
				(MENUWINHEI * 3) / 4 + MENUWINHEI / 10 ,
				index == 2 ? LIGHT_GREEN : WHITE, tmp);
}

void	ft_draw_color_presets_menu(t_mlx *mlx, int index)
{
	const char	*str1;
	const char	*str2;
	char		*tmp;

	str1 = "Choose number of colors (2-20)";
	str2 = "Choose number of color gradients (1-100)";
	mlx_string_put(mlx->mlx, mlx->menuwin->win,
			(MENUWINWID / 2 - ft_strlen(str1) * 5),
				MENUWINHEI / 4 , index == 0 ? YELLOW : WHITE, (char*)str1);
	mlx_string_put(mlx->mlx, mlx->menuwin->win,
		(MENUWINWID / 2 - ft_strlen(str2) * 5),
			(MENUWINHEI) / 2 , index == 1 ? YELLOW : WHITE,
			(char*)str2);
	tmp = ft_itoa(mlx->chvars->nb_color_set);
	mlx_string_put(mlx->mlx, mlx->menuwin->win,
			(MENUWINWID / 2 - (MENUWINWID / 128) * ft_strlen(tmp)),
				MENUWINHEI / 4 + MENUWINHEI / 10 ,
				index == 0 ? RED : WHITE, tmp);
	free(tmp);
	ft_draw_color_presets_menu_p2(mlx, index);
}
#include <string.h>

void	ft_choose_color_menu(t_mlx *mlx)
{
	char	text[13];
	char	*color_hex;
	int		i;
	int		j;

	text[0] = '\0';
	ft_strcpy(text, "COLOR XX/XX:");
	text[6] = (mlx->chvars->index + 1) / 10 + '0';
	text[7] = (mlx->chvars->index + 1) % 10 + '0';
	text[9] = mlx->chvars->nb_color_set / 10 + '0';
	text[10] = mlx->chvars->nb_color_set % 10 + '0';
	color_hex = ft_hextoa(mlx->chvars->color_set[mlx->chvars->index], 1);
	i = MENUWINHEI / 4;
	if (mlx->chvars->color_set)
		while (i < MENUWINHEI)
		{
			j = -1;
			while (++j < MENUWINWID)
				*(unsigned*)(mlx->menuwin->data + j * (mlx->menuwin->bpx / 8) +
						i * mlx->menuwin->size_line) =
					mlx->chvars->color_set[mlx->chvars->index];
			i++;
		}
	mlx_put_image_to_window(mlx->mlx, mlx->menuwin->win, mlx->menuwin->img, 0, 0);
	mlx_string_put(mlx->mlx, mlx->menuwin->win, 5, 30, WHITE, text);
	mlx_string_put(mlx->mlx, mlx->menuwin->win, MENUWINWID / 3, 30, WHITE, color_hex);
}

void	ft_draw_menu_x(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->menuwin->win, mlx->menuwin->img, 0, 0);
	if (!mlx->chvars->menumode)
		ft_draw_default_menu(mlx);
	else if (mlx->chvars->menumode == 1)
		ft_draw_color_presets_menu(mlx, mlx->chvars->index);
	else if (mlx->chvars->menumode == 2)
		ft_choose_color_menu(mlx);
}
