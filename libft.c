/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:41:45 by irhesri           #+#    #+#             */
/*   Updated: 2022/02/15 13:53:30 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	my_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	ft_putstr_fd(char *s, int fd)
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
/*
int	my_atoi(char *str)
{
	unsigned long long	n;
	int					symbole;

	n = 0;
	symbole = 1;
	if (!str)
		error_case();
	if (*str == '-')
		symbole = -1;
	if ((*str == '+' || *str == '-') && *(str + 1))
		str++;
	while (*str > 47 && *str < 58 && (n < 2147483648))
	{
		n = n * 10 + *str - 48;
		str++;
	}
	if (*str || (n >= 2147483648 && symbole == 1)
		|| (n > 2147483648 && symbole == -1))
		error_case();
	return (symbole * n);
}*/