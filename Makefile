CC=gcc
FLAGS=-Wall -Wextra -Werror
NAME=solonglib.a
OUT=so_long.out

FILES=main.c hooks.c render.c ft_pathfinding.c enemy_pathfinding.c events_utils.c get_map_info.c get_map.c load_map.c movement_manager.c check_map.c enemy_algorithm_helper.c enemy_pathfinding_utils.c enemy_random_move.c load_imgs.c add_enemies.c
OBJECTS=$(FILES:.c=.o)

LIBFT=libft/
LIBFTNAME=libft.a

%.o: %.c
	$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) -C $(LIBFT)
	mv $(LIBFT)$(LIBFTNAME) $(NAME)
	$(CC) $(FLAGS) $(OBJECTS) $(NAME) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(OUT)

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
