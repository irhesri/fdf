/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:01:22 by irhesri           #+#    #+#             */
/*   Updated: 2022/02/15 14:01:24 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static	char const	*my_skip(char const *s, char c, int *size, int *len)
{
	if (s)
	{
		(*len) = 0;
		while (*s == c)
		{
			(*size)--;
			s++;
		}
		while (*s != c && *s)
		{
			s++;
			(*len)++;
		}
		if (*s)
			return (s);
	}
	return (NULL);
}

static	void	my_size(int *t, char const *s, char c, int size)
{
	int	*ptr;
	int	len;
	int	i;

	if (s && t)
	{
		i = 0;
		ptr = t + 1;
		while (s)
		{
			s = my_skip(s, c, &size, &len);
			if (s)
			{
				size -= len;
				*ptr++ = len;
				i++;
			}
		}
		if (size > 0)
		{
			*ptr = size;
			i++;
		}
		*t = i;
	}
}

static	char	**my_alloc(char **str, int *t)
{
	int	i;

	if (t)
	{
		i = 0;
		str = (char **) malloc(sizeof(char *) * (t[0] + 1));
		if (str)
		{
			while (i < t[0])
			{
				str[i] = (char *) malloc(sizeof(char) * (t[i + 1] + 1));
				if (!str[i])
				{
					while (--i)
						free(str[i]);
					free(str);
					exit (0);
					break ;
				}
				i++;
			}
			return (str);
		}
	}
	return (NULL);
}

static	void	my_assignment(char **str, char const *s, char c, int *t)
{
	int	i;
	int	j;

	if (str && s)
	{
		i = 0;
		while (i < t[0])
		{
			while (*s == c)
				s++;
			j = 0;
			while (j < t[i + 1])
			{
				str[i][j] = *s;
				s++;
				j++;
			}
			str[i][j] = '\0';
			i++;
		}
		str[i] = NULL;
	}
}

char	**ft_split(char const *s, char c, int *len)
{
	int		*t;
	int		size;
	char	**str;

	if (s)
	{
		str = NULL;
		size = ft_strlen(s);
		t = (int *) malloc(sizeof(int) * (size / 2 + 2));
		my_size(t, s, c, size);
		str = my_alloc(str, t);
		if (!str)
			exit (0);
		my_assignment(str, s, c, t);
		(*len) = *t;
		free(t);
		return (str);
	}
	(*len) = 0;
	return (NULL);
}
