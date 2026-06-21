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
NAME = game

SRCS = game.c \
	src/game_render.c \
	src/game_controls.c \
	src/map.c \
	src/controls.c \
	src/params.c \
	src/main.c
OBJS = $(SRCS:.c=.o)



MLX_TYPE = MLX42

MLX_DIR = mlx42
MLX_BUILD = $(MLX_DIR)/build
MLX_LIB = $(MLX_BUILD)/libmlx42.a
MLX_INC = -I$(MLX_DIR)/include/MLX42
#     MLX_LDFLAGS = $(MLX_LIB) -ldl -lglfw -lm -lpthread -lGL
MLX_LDFLAGS = $(MLX_LIB) -ldl -lglfw(3) -pthread -lm

# MLX_DIR = minilibx-linux

LIBFT_DIR = libft
INCLUDES = -Iinclude -I$(LIBFT_DIR) $(MLX_INC)
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
LDFLAGS = -L$(MLX_DIR) -L$(LIBFT_DIR) -lmlx -lXext -lX11 -lm -lbsd -lft

all: $(NAME)

$(NAME): $(MLX_DIR)/libmlx.a $(LIBFT_DIR)/libft.a $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c include/so_long.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	if [ ! -d $(MLX_DIR) ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi
	if [ ! -f $(BUILD_DIR)/libmlx42.a ]; then \
		cmake $(MLX_DIR) -B $(BUILD_DIR) && \
		cmake --build $(BUILD_DIR) -j4; \
	fi

clean:
	rm -f $(NAME) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean 2>/dev/null || true
	$(MAKE) -C $(MLX_DIR) clean 2>/dev/null || true

.PHONY: all clean #fclean re make
