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

int		*toint(char *line)
{
	char		**arr;
	int		i;
	int		j;
	int		*ret;
	int		len;
	
	j = 2;
	i = 0;
	len = 0;
	arr = ft_strsplit(line, ' ');
	while(arr[len])
	{
		len++;
	}
	ret = (int*)malloc(sizeof(int) * len + 1);
	while (arr[i])
	{
		ret[i] = ft_atoi(arr[i]);
		i++;
	}
	return(ret);
}

void	drawline()
{

}

void	parse(int fd)
{
	char	*line;
	int		i;
	int		x;
	int		y;
	int		**arr;
	int		isox;
	int		isoy;
	void	*mlx;
	void	*win;

	arr = (int**)malloc(sizeof(int*) * 100);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 600, 600, "fdf");
	x = 0;
	i = 0;
	y = 0;  
	while (get_next_line(fd, &line) > 0)
	{
		arr[i] = (int*)malloc(sizeof(int) * 20);
		arr[i] = toint(line);
		i++;
	}

	while (y < i)
	{
		x = 0;
		while (x < 17)
		{
			isox = ((x - y)) * 15;	
			isoy = ((x + y) / 2) * 15;
			isoy = isoy + arr[y][x];
			mlx_pixel_put(mlx, win, isox + 200, isoy + 200, 7266244);
			x++;
		}
		y++;
	}
	mlx_loop(mlx);
}
