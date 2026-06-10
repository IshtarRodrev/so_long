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

NAME = so_long

SRC = src/

SRC_FILES = $(SRC)main.c \
	$(SRC)core/close.c \
	$(SRC)core/error.c \
	$(SRC)core/free_game.c \
	$(SRC)core/init_game.c \
	$(SRC)core/init_mlx.c \
	$(SRC)parsing/parse_map.c \
	$(SRC)parsing/parse_utils.c \
	$(SRC)parsing/read_map.c \
	$(SRC)validation/flood_fill.c \
	$(SRC)validation/validate_chars.c \
	$(SRC)validation/validate_map.c \
	$(SRC)validation/validate_path.c \
	$(SRC)validation/validate_shape.c \
	$(SRC)render/animate.c \
	$(SRC)render/destroy_images.c \
	$(SRC)render/draw_animation_layer.c \
	$(SRC)render/draw_background.c \
	$(SRC)render/draw_interactive_layer.c \
	$(SRC)render/draw_map.c \
	$(SRC)render/draw_tools.c \
	$(SRC)render/end_animation.c \
	$(SRC)render/end_text.c \
	$(SRC)render/init_frames.c \
	$(SRC)render/init_render.c \
	$(SRC)render/load_assets.c \
	$(SRC)render/load_brazier_asset.c \
	$(SRC)render/load_flame_asset.c \
	$(SRC)render/redraw.c \
	$(SRC)render/redraw_interactive_frame.c \
	$(SRC)render/render_animation.c \
	$(SRC)render/update_moves_text.c \
	$(SRC)game/collect_utils.c \
	$(SRC)game/finish_game.c \
	$(SRC)game/input.c \
	$(SRC)game/move_player.c \
	$(SRC)game/move_utils.c \
	$(SRC)tools/array_tools.c \
	$(SRC)tools/checker.c \
	$(SRC)tools/free_arrays.c \
	$(SRC)tools/iterators.c \
	$(SRC)tools/random_range.c \
	$(SRC)generate/allocate_animation_layer.c \
	$(SRC)generate/allocate_interactive_layer.c \
	$(SRC)generate/fill_animation_layer.c \
	$(SRC)generate/fill_interactive_layer.c \
	$(SRC)generate/generate_animation_layer.c \
	$(SRC)generate/generate_floor.c \
	$(SRC)generate/generate_interactive_layer.c \
	$(SRC)generate/generate_walls.c \
	$(SRC)generate/map_generator.c

SRC_OBJS = $(SRC_FILES:.c=.o)


##Libriaries

#Libft
DLIBFT = libft
LIBFT = $(DLIBFT)/libft.a
FT = ft

#MLX42
MLX42 = mlx42
BUILD_DIR = $(MLX42)/build
MLX42LIB = $(BUILD_DIR)/libmlx42.a

CC = cc
# CFLAGS = -g -Wall -Wextra -Werror -Iincludes -I$(MLX42)/include/MLX42 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(MLX42)/include/MLX42

EXT_LIBS = -ldl -lglfw -pthread -lm


MLX_DIR = minilibx-linux
SAMPLE = sample_minilibx
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR)
LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

all: $(SAMPLE)

sample: $(SAMPLE)

#$(SAMPLE): src/sample_minilibx.c $(MLX_DIR)/libmlx.a
FORCE:

$(SAMPLE): src/sample_minilibx.c $(MLX_DIR)/libmlx.a FORCE
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(MLX_DIR)/libmlx.a:
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(SAMPLE)

#.PHONY: all clean sample
.PHONY: all clean sample FORCE