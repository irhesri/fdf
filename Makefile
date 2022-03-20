NAME = fdf
NAME_B = fdf_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
LFLAGS = -Imlx -lmlx -framework OpenGl -framework Appkit
MANDATORY = main.c initialise.c get_next_line.c ft_split.c functions.c segment.c
BONUS = main_bonus.c initialise_bonus.c get_next_line_bonus.c ft_split_bonus.c functions_bonus.c segment_bonus.c

all: $(NAME)

$(NAME): $(MANDATORY:.c=.o) 
	gcc $(CFLAGS) $(LFLAGS) $(MANDATORY:.c=.o) -o $@ -lm

$(NAME_B): $(BONUS:.c=.o)
	gcc $(CFLAGS) $(LFLAGS) $(BONUS:.c=.o) -o $@ -lm

bonus:$(NAME_B)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re