/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:35:20 by niboute           #+#    #+#             */
/*   Updated: 2019/03/22 02:35:39 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int		ft_color_grad(unsigned int cola, unsigned int colb, int percent)
{
	short	r;
	short	g;
	short	b;

	r = (colb >> 16) - (cola >> 16);
	g = ((colb >> 8) & 0x000000FF) - ((cola >> 8) & 0x000000FF);
	b = (colb & 255) - (cola & 255);
	return (cola + ((((r * percent) / 100) * 65536) +
				(((g * percent) / 100) * 256) + (b * percent) / 100));
}
