/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_alnum_keycodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <niboute@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:44:49 by niboute           #+#    #+#             */
/*   Updated: 2019/10/16 17:51:12 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int		get_key_letter_p1(int keycode)
{
	if (keycode == 0)
		return ('a');
	else if (keycode == 1)
		return ('s');
	else if (keycode == 2)
		return ('d');
	else if (keycode == 3)
		return ('f');
	else if (keycode == 4)
		return ('h');
	else if (keycode == 5)
		return ('g');
	else if (keycode == 6)
		return ('z');
	else if (keycode == 7)
		return ('x');
	else if (keycode == 8)
		return ('c');
	else if (keycode == 9)
		return ('v');
	return (-1);
}

int		get_key_letter_p2(int keycode)
{
	if (keycode == 11)
		return ('b');
	else if (keycode == 12)
		return ('q');
	else if (keycode == 13)
		return ('w');
	else if (keycode == 14)
		return ('e');
	else if (keycode == 15)
		return ('r');
	else if (keycode == 16)
		return ('y');
	else if (keycode == 17)
		return ('t');
	return (-1);
}

int		get_key_letter_p3(int keycode)
{
	if (keycode == 31)
		return ('o');
	else if (keycode == 32)
		return ('u');
	else if (keycode == 34)
		return ('i');
	else if (keycode == 35)
		return ('p');
	else if (keycode == 37)
		return ('l');
	else if (keycode == 38)
		return ('j');
	else if (keycode == 40)
		return ('k');
	else if (keycode == 45)
		return ('n');
	else if (keycode == 46)
		return ('m');
	return (-1);
}

int		get_key_letter(int keycode)
{
	if (keycode < 10)
		return (get_key_letter_p1(keycode));
	else if (keycode < 18)
		return (get_key_letter_p2(keycode));
	else
		return (get_key_letter_p3(keycode));
	return (-1);
}

int		get_alnum_from_keycode(int keycode)
{
	if (keycode >= 82 && keycode <= 92 && keycode != 90)
		return (keycode >= 91 ? keycode - 83 : keycode - 82);
	else if (keycode >= 18 && keycode <= 29 && keycode != 27 && keycode != 24)
	{
		if (keycode <= 21)
			return (keycode - 17);
		if (keycode <= 23)
			return (keycode == 22 ? 6 : 5);
		if (keycode <= 26)
			return (keycode == 25 ? 9 : 7);
		if (keycode <= 29)
			return (keycode == 29 ? 0 : 8);
	}
	else if ((keycode >= 0 && keycode <= 9) || (keycode >= 11 && keycode <= 17)
		|| (keycode >= 31 && keycode <= 46))
		return (get_key_letter(keycode));
	return (-1);
}
