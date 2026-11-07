# NAME = so_long
# CC = gcc
# CFLAGS = -Wall -Wextra -Werror
# INCLUDES = -Iinclude -Ilibft
# LIBFT_DIR = libft
# LIBFT = $(LIBFT_DIR)/libft.a
# SRCS = src/main.c \
# 	src/map.c \
# 	src/params.c
# OBJS = $(SRCS:.c=.o)
# RM = rm -f

# all: $(LIBFT) $(NAME)

# $(NAME): $(OBJS) $(LIBFT)
# 	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)

# $(LIBFT):
# 	$(MAKE) -C $(LIBFT_DIR)

# %.o: %.c
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# clean:
# 	$(RM) $(OBJS)
# 	$(MAKE) -C $(LIBFT_DIR) clean

# fclean: clean
# 	$(RM) $(NAME)
# 	$(MAKE) -C $(LIBFT_DIR) fclean

# re: fclean all

# .PHONY: all clean fclean re

CC = cc
NAME = so_long

SRCS = src/main.c \
	src/controls.c \
	src/menu.c \
	src/game_render.c \
	src/game_render_texture.c \
	src/game_render_tiles.c \
	src/game_render_map.c \
	src/game_controls.c \
	src/map/map.c \
	src/map/map_path.c \
	src/map/map_path_check.c \
	src/map/map_read.c \
	src/map/params.c \
	src/camera/camera.c \
	src/patterns/patterns.c \
	src/patterns/patterns_tile.c \
	src/patterns/patterns_runs.c \
	src/patterns/patterns_lines.c \
	src/patterns/patterns_desks.c \
	src/patterns/patterns_collectible.c \
	src/progress/progress.c \
	src/progress/tasks.c \
	src/cleanup.c
OBJS = $(SRCS:.c=.o)



MLX_TYPE = MLX42

MLX_DIR = mlx42
MLX_BUILD = $(MLX_DIR)/build
MLX_LIB = $(MLX_BUILD)/libmlx42.a
MLX_INC = -I$(MLX_DIR)/include/MLX42
# MLX_DIR = minilibx-linux

LIBFT_DIR = libft
LIBFT_LIB = libft/libft.a
INCLUDES = -Iinclude -I$(LIBFT_DIR) $(MLX_INC)
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
LDFLAGS = $(MLX_LIB) -L$(LIBFT_DIR) -lglfw -ldl -lpthread -lm -lft

all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c include/so_long.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	if [ ! -d $(MLX_DIR) ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi
	if [ ! -f $(MLX_LIB) ]; then \
		cmake $(MLX_DIR) -B $(MLX_BUILD) && \
		cmake --build $(MLX_BUILD) -j4; \
	fi

clean:
	rm -f $(NAME) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean 2>/dev/null || true
	$(MAKE) -C $(MLX_DIR) clean 2>/dev/null || true

fclean: clean
	rm -f $(NAME)

re: fclean all

FORCE:

.PHONY: all clean fclean re FORCE
