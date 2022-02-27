
CFLAGS = -g
LFLAGS =  -Imlx -lmlx -framework OpenGl -framework Appkit
MANDATORY = test2.c init_map.c get_next_line.c ft_split.c libft.c

all: m


m:
	gcc $(MANDATORY) -o fdf

