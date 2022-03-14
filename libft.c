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

static int	color_to_int(char *str)
{
	int	n;
	int	i;
	int	size;

	i = 0;
	n = 0;
	size = ft_strlen(str);
	if (*str++ != '0' || *str != 'x' || size > 8)
		return (-1);
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
			error_case(6);
	}
	return (n);
}

int	my_atoi(char *str, t_point *point)
{
	unsigned long long	n;
	int					symbole;

	n = 0;
	symbole = 1;
	// if (!str)
	// 	error_case();
	if (*str == '-')
		symbole = -1;
	if ((*str == '+' || *str == '-') && *(str + 1))
		str++;
	while (*str > 47 && *str < 58 && (n < 2147483648))
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