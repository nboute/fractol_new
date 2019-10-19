/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:28:18 by niboute           #+#    #+#             */
/*   Updated: 2019/10/19 14:30:51 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <stdlib.h>

int				draw_color_presets_menu_p2(t_mlx *mlx, int index)
{
	char		*tmp;

	if (!(tmp = ft_itoa(mlx->chvars.nb_color_grad)))
		return (0);
	mlx_string_put(mlx->mlx, mlx->menuwin.win,
			(MENUWINWID / 2 - (MENUWINWID / 128) * ft_strlen(tmp)),
			MENUWINHEI / 2 + MENUWINHEI / 10,
			index == 1 ? RED : WHITE, tmp);
	free(tmp);
	tmp = "VALIDATE";
	mlx_string_put(mlx->mlx, mlx->menuwin.win,
			(MENUWINWID / 2 - (MENUWINWID / 75) * ft_strlen(tmp)),
				(MENUWINHEI * 3) / 4 + MENUWINHEI / 10,
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
			MENUWINHEI / 8, index == 0 ? YELLOW : WHITE, (char*)str1);
	mlx_string_put(mlx->mlx, mlx->menuwin.win,
		(MENUWINWID / 2 - ft_strlen(str2) * 5),
		(MENUWINHEI) / 2, index == 1 ? YELLOW : WHITE, (char*)str2);
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
