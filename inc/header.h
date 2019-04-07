/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboute <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:08:05 by niboute           #+#    #+#             */
/*   Updated: 2019/04/07 17:58:24 by niboute          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define MAINWINWID 1280
# define MAINWINHEI 960
# define MENUWINWID 400
# define MENUWINHEI 400
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define LIGHT_GREEN 0x007FFF00
# define RED 0x00FF0000
# define BLUE 0x003333FF
# define ORANGE 0x00FF7F00
# define DARK_GREEN 0X00006633
# define YELLOW 0X00FFFF00
# define BUTTONS 9
# define BTN_ROW 3
# define BTN_COL 3
# define CPU_THREADS 4
# define POW_MAX 48
# define NB_FRACTS 3
#include "../libft/libft.h"
#include "../minilibx_macos/mlx.h"
#include <pthread.h>
typedef struct			s_win
{
	void				*win;
	void				*img;
	char				*data;
	int					wid;
	int					hei;
	int					bpx;
	int					size_line;
	int					endian;
}						t_win;

typedef struct			s_vars
{
	char				win_ch[2];
	unsigned int		*btns_cols;
	char				**btns_txt;
	char				**btns_vals;
	short				fractal;
	double				xmin;
	double				xmax;
	double				ymin;
	double				ymax;
	unsigned int		zpow;
	unsigned long		zoom;
	unsigned int		itermax;
	short				variter;
	unsigned int		*color_set;
	unsigned int		nb_color_set;
	unsigned int		nb_color_grad;
	unsigned int		nb_cols;
	unsigned int		*colors;
	unsigned short		menumode;
	unsigned short		index;
	char				**fract_names;
	short				vary;
	short				colvar;
	short				varyval;
	double				padx;
	double				pady;
	double				tmpx[MAINWINWID];
}						t_vars;

typedef struct			s_mlx
{
	struct s_fileline	*lines;
	struct s_point		**points;
	void				*mlx;
	struct s_win		*mainwin;
	struct s_win		*menuwin;
	struct s_vars		*chvars;
	int	(*fractal_draw)(double, double, t_vars*);
}						t_mlx;

typedef struct			s_thread
{
	int					y;
	t_mlx				*mlx;
	pthread_t			thread;
}						t_thread;

t_mlx	*ft_setup_mlx(t_mlx *mlx);
t_mlx	*ft_read_file(int fd, t_mlx *mlx);
int		ft_bind_events(t_mlx *mlx);
int		ft_exit();
int		ft_loop(t_mlx *mlx);
int		ft_resetvals(t_mlx *mlx);
int		ft_init_default_menu(t_mlx *mlx);
void	ft_draw_buttons(t_mlx *mlx, t_win *win);
void	ft_draw_default_menu(t_mlx *mlx);
void	ft_draw_menu(t_mlx *mlx);
void	ft_reset_all(t_vars *vars);
int		ft_color_grad(unsigned int cola, unsigned int colb, int percent);
int		ft_init_menu_win(t_mlx *mlx);
int		ft_menu_mouse_event(int button, int x, int y, t_vars *vars);
int		ft_main_mouse_event(int button, int x, int y, t_vars *vars);
int		ft_menu_key_event(int keycode, t_vars *vars);
int		ft_main_key_event(int keycode, t_vars *vars);
int		ft_menu_mouse_release_event(int button, int x, int y, t_vars *vars);
int		ft_draw_fractal(t_mlx *mlx);
int			ft_reset_fractal(t_vars *vars);
void	ft_draw_menu_x(t_mlx *mlx);
int		ft_set_colors(t_vars *vars);
int		ft_main_mouse_hover_event(int x, int y, t_vars *vars);
void	*ft_draw_fractal_x(void *ptr);
int		ft_draw_julia_point(double zx, double zy, t_vars *vars);
int		ft_draw_burning_ship_point(double cx, double cy, t_vars *vars);
int		ft_draw_mandelbrot_point(double cx, double cy, t_vars *vars);

#endif
