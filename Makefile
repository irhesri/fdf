
CFLAGS = -g
LFLAGS =  -Imlx -lmlx -framework OpenGl -framework Appkit
MANDATORY = main.c initialise.c get_next_line.c ft_split.c libft.c functions.c segment.c

all: m

m:
	gcc $(CFLAGS) $(LFLAGS) $(MANDATORY) -o fdf

