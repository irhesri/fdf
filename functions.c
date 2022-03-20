/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:14:51 by irhesri           #+#    #+#             */
/*   Updated: 2022/03/17 21:14:53 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

static void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
		{
			write(fd, s, 1);
			s++;
		}
	}
}

int	error_case(short n)
{
	if (n == 0)
		ft_putstr_fd("ALLOCATION ERROR", 2);
	else if (n == 1)
		ft_putstr_fd("WRONG MAP", 2);
	else if (n == 2)
		ft_putstr_fd("CAN'T OPEN THE FILE", 2);
	else if (n == 3)
		ft_putstr_fd("EMPTY FILE", 2);
	else if (n == 4)
		ft_putstr_fd("FOUND WRONG LINE LENGTH. EXITING.", 2);
	else if (n == 5)
		ft_putstr_fd("WRONG ARGUMENTS", 2);
	else if (n == 6)
		ft_putstr_fd("MLX_ERROR", 2);
	ft_putstr_fd("\n", 2);
	exit (0);
	return (0);
}

static int	color_to_int(char *str)
{
	int	n;
	int	i;
	int	size;

	i = 0;
	n = 0;
	size = ft_strlen(str);
	if (*str++ != '0' || *str != 'x' || size < 3 || size > 8)
		error_case(1);
	size -= 2;
	while (*++str)
	{
		if (*str > 47 && *str < 58)
			n += (*str - 48) * pow(16, --size);
		else if (*str > 64 && *str < 71)
			n += (*str - 55) * pow(16, --size);
		else if (*str > 96 && *str < 103)
			n += (*str - 87) * pow(16, --size);
		else
			error_case(1);
	}
	return (n);
}

int	my_atoi(char *str, t_point *point)
{
	unsigned long long	n;
	int					symbole;

	n = 0;
	symbole = 1;
	if (*str == '-')
		symbole = -1;
	if ((*str == '+' || *str == '-') && *(str + 1))
		str++;
	while (*str > 47 && *str < 58)
	{
		n = n * 10 + *str - 48;
		str++;
	}
	if (!*str)
		point->color = -1;
	else if (*str == ',')
		point->color = color_to_int(++str);
	else
		error_case(1);
	return (symbole * n);
}
