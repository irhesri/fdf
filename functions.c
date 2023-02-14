/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:14:51 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/13 23:34:07 by imane            ###   ########.fr       */
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

int	error_case(short n)
{
	static const char	error[8][40] = {"ALLOCATION ERROR\n", "WRONG MAP\n",
		"CAN'T OPEN THE FILE\n", "EMPTY FILE\n",
		"FOUND WRONG LINE LENGTH. EXITING.\n",
		"WRONG NUMBER OF ARGUMENTS\n", "MLX_ERROR\n",
		"WRONG EXTENSION\n"};

	exit (write(2, error[n], ft_strlen(error[n])));
}

void	check_args(char *str, int ac)
{
	int			size;

	if (ac != 2)
		error_case(5);
	size = ft_strlen(str) - 4;
	if (size < 0 || str[size++] != '.' || str[size++] != 'f'
		|| str[size++] != 'd' || str[size] != 'f')
		error_case(7);
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
