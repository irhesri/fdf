OS			= $(shell uname)

NAME		= fdf
NAME_B		= fdf_bonus
MANDATORY 	= main.c initialise.c segment.c
BONUS		= main_bonus.c initialise_bonus.c segment_bonus.c
BOTH		= get_next_line.c ft_split.c functions.c 

CC			= gcc
CFLAGS		= -O3 -g -fsanitize=address

ifeq ($(OS), Linux)
	MLXFLAGS = -lmlx -lbsd -lXext -lX11
	LIBRARY = mlx_linux/libmlx.a
endif
ifeq ($(OS), Darwin)
	MLXFLAGS = -framework OpenGl -framework Appkit -Imlx -Iincludes
	LIBRARY = mlx_mac/libmlx.a
endif

OBJS	= $(MANDATORY:.c=.o)
OBJS_B	= $(BOTH:.c=.o)
OBJS_BN	= $(BONUS:.c=.o)

all: $(NAME)

bonus: $(NAME_B)

check_OS:
ifndef MLXFLAGS
	@echo "\033[1;31m INCOMPATIBLE OS \033[0;37m"
	@exit 1
endif

$(NAME): $(OBJS) $(OBJS_B) check_OS
	@$(CC) $(OBJS) $(OBJS_B) $(LIBRARY) -o $@ $(CFLAGS) $(MLXFLAGS) -lm

$(NAME_B): $(OBJS_BN) $(OBJS_B) check_OS
	@$(CC) $(OBJS_BN) $(OBJS_B) $(LIBRARY) -o $@ $(CFLAGS) $(MLXFLAGS) -lm

%.o: %.c
	@$(CC) -c $< $(CFLAGS)

clean:
	@rm -rf $(OBJS) $(OBJS_B) $(OBJS_BN)

fclean: clean
	@rm -rf $(NAME) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re