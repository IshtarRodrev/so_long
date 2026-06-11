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
MLX_DIR = minilibx-linux
LIBFT_DIR = libft
INCLUDES = -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR)
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
LDFLAGS = -L$(MLX_DIR) -L$(LIBFT_DIR) -lmlx -lXext -lX11 -lm -lbsd -lft
NAME = game
SRCS = game.c src/game_render.c src/game_controls.c src/map.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(MLX_DIR)/libmlx.a $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c include/so_long.h
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX_DIR)/libmlx.a:
	@if [ ! -d $(MLX_DIR) ]; then \
		tar -xzf $(MLX_DIR).tgz; \
	fi
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(NAME) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean 2>/dev/null || true
	$(MAKE) -C $(MLX_DIR) clean 2>/dev/null || true

.PHONY: all clean #fclean re make