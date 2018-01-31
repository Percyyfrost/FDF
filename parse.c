/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnxele <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 12:05:56 by vnxele            #+#    #+#             */
/*   Updated: 2018/01/31 15:17:44 by vnxele           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		toint(int **iarr, int len, char *line)
{
	char 	**arr;
	int		i;
	int		j;
	int		*ret;

	ret = (int*)malloc(sizeof(int) * len + 1);
	j = 2;
	i = 0;
	arr = ft_strsplit(line, ' ');
	while (arr[i])
	{
		ret[i] = ft_atoi(arr[i]);
		i++;
	}
	*iarr = ret;
}

void	parse(int fd)
{
	char	*line;
	int		i;
	int		j;
	int		y;
	int		*tmp;
	int		**arr;
	int		isox;
	int		isoy;
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 600, 600, "fdf");
	j = 0;
	i = 0;
	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		toint(&arr[i], ft_strlen(line), line);
		i++;
	}
	while (y < i)
	{
		j = 0;
		while (j < 17)
		{
			isox = ((j - y)) * 9;
			isoy = ((j + y) / 2) * 9;
			//isoy = isoy + arr[y][j];
			mlx_pixel_put(mlx, win, isox + 200, isoy + 200, 7266244);
			j++;
		}
		y++;
	}
	mlx_loop(mlx);
}
