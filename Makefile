CC=gcc
FLAGS=-Wall -Wextra -Werror -g -O0
NAME=solonglib.a
OUT=game.out

FILES=main.c colors.c mod_color.c hooks.c render.c ft_pathfinding.c enemy_pathfinding.c events_utils.c get_map_info.c get_map.c load_map.c movement_manager.c check_map.c
OBJECTS=$(FILES:.c=.o)

LIBFT=libft/
LIBFTNAME=libft.a

%.o: %.c
	$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) -C $(LIBFT)
	mv $(LIBFT)$(LIBFTNAME) $(NAME)
	$(CC) $(FLAGS) $(OBJECTS) $(NAME) -no-pie -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(OUT) -g

clean:
	rm -f $(OBJECTS) $(BONUS_OBJECTS)
	$(MAKE) clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)$(LIBFTNAME)

re:	fclean $(NAME)

bonus: $(OBJECTS)
	$(MAKE) bonus -C $(PRINTF)
	mv $(LIBFT)$(LIBFTNAME) $(NAME)
	$(CC) $(FLAGS) $(OBJECTS) $(NAME) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(OUT)

.PHONY:	all clean fclean re bonus
