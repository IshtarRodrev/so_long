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
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR)
LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
NAME = game

all: $(NAME)

$(NAME): game.c $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(MLX_DIR)/libmlx.a:
	@if [ ! -d $(MLX_DIR) ]; then \
		tar -xzf $(MLX_DIR).tgz; \
	fi
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(NAME)
	$(MAKE) -C $(MLX_DIR) clean 2>/dev/null || true

.PHONY: all clean #fclean re make