#include "fdf.h"

void    ft_dda(t_main *a, t_draw *p, float h)
{
    int i;

    i = 0;
    p->dx = p->x2 - p->x1;
    p->dy = p->y2 - p->y1;
    p->steps = abs(p->dx) > abs(p->dy) ? abs(p->dx) : abs(p->dy);
    p->xinc = p->dx / (float)p->steps;
    p->yinc = p->dy / (float)p->steps;
    p->x = p->x1;
    p->y = p->y1;
    while (i <= p->steps)
    {
        if (h > 0)
            mlx_pixel_put(a->mlx, a->win, p->x, p->y, 0xffffff);
        else if (h < 0)
            mlx_pixel_put(a->mlx, a->win, p->x, p->y, 0xff0000);
        else
            mlx_pixel_put(a->mlx, a->win, p->x, p->y, 0xffff00);
        p->x += p->xinc;
        p->y += p->yinc;
        i++;
    }
}

void    ft_p1(int x, int y, t_draw *p1, t_main *a)
{
    p1->x1 = a->mapb[y][x] / 10000;
    p1->y1 = a->mapb[y][x] % 10000;
    p1->x2 = a->mapb[y][x + 1] / 10000;
    p1->y2 = a->mapb[y][x + 1] % 10000;
}

void    ft_p2(int x, int y, t_draw *p2, t_main *a)
{
    p2->x1 = a->mapb[y][x] / 10000;
    p2->y1 = a->mapb[y][x] % 10000;
    p2->x2 = a->mapb[y + 1][x] / 10000;
    p2->y2 = a->mapb[y + 1][x] % 10000;
}

void    ft_prepdda(t_main *a)
{
    t_draw  p;
    t_draw  p1;

    p1.y = 0;
    while (p1.y < a->y)
    {
        p1.x = 0;
        while (p1.x < a->x)
        {
            p1.cx = (int)p1.x;
            p1.cy = (int)p1.y;
            if (p1.x < a->x - 1)
            {
                ft_p1(p1.x, p1.y, &p, a);
                ft_dda(a, &p, a->mapa[p1.cy][p1.cx]);
            }
            if (p1.y < a->y - 1)
            {
                ft_p2(p1.x, p1.y, &p, a);
                ft_dda(a, &p, a->mapa[p1.cy][p1.cx]);
            }
            p1.x++;
        }
        p1.y++;
    }
}

int			my_key_funct(int keycode, void *param)
{
	param = NULL;
	if (keycode == 53 || keycode == 12)
	{
		exit(0);
	}
	return (0);
}

void		map(t_main *a)
{
	t_norm	n;

	a->y = 0;
	while (get_next_line(a->fd, &a->line))
	{
		a->x = 0;
		a->i = 0;
		a->str = ft_strsplit(a->line, ' ');
		while (a->str[a->i])
			a->mapa[a->y][a->x++] = ft_atoi(a->str[a->i++]);
		a->y++;
	}
    n.y = -1;
    while (n.y++ < a->y)
    {
        n.x = -1;
        while (n.x++ < a->x)
        {
            n.fx = (n.x * SCALE) - (n.y * SCALE) + 700;
            n.temp = ((n.x * SCALE) + (n.y * SCALE));
            n.fy = n.temp / 2 + 200 - a->mapa[n.y][n.x];
            n.coord = n.fx * 10000 + n.fy;
            a->mapb[n.y][n.x] = n.coord;
        }
    }
}

int			main(int ac, char **av)
{
	t_main a;

	a.mlx = mlx_init();
	a.win = mlx_new_window(a.mlx, 1920, 1080, "FDF");
	if ((ac != 2) || (!ft_strstr(av[1], ".fdf")))
	{
		ft_putendl("Invaid format");
	}
	else if ((a.fd = open(av[1], O_RDONLY)))
	{
		map(&a);
		ft_prepdda(&a);
		mlx_key_hook(a.win, my_key_funct, 0);
		mlx_loop(a.mlx);
	}
	else
		ft_putendl("Invalid format");
	return (0);
}
