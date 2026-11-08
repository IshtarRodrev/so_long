CC = cc
NAME = so_long

SRCS = src/main.c \
	src/game/game.c \
	src/game/menu.c \
	src/game/menu_draw.c \
	src/game/blink.c \
	src/game/input.c \
	src/game/error.c \
	src/game/cleanup.c \
	src/map/map_load.c \
	src/map/map_read.c \
	src/map/map.c \
	src/map/flood.c \
	src/map/map_path.c \
	src/map/map_path_check.c \
	src/map/map_tile.c \
	src/progress/progress.c \
	src/progress/collectibles.c \
	src/render/render_init.c \
	src/render/render_map.c \
	src/render/render_tiles.c \
	src/render/render_images.c \
	src/render/camera.c \
	src/textures/textures.c \
	src/textures/textures_player.c \
	src/textures/textures_furniture.c \
	src/textures/textures_glass.c \
	src/textures/textures_free.c \
	src/patterns/patterns_init.c \
	src/patterns/patterns_tile.c \
	src/patterns/patterns_collectible.c \
	src/patterns/patterns_lines.c \
	src/patterns/patterns_runs.c \
	src/patterns/patterns_desks.c \
	src/patterns/patterns_lamp_spot.c \
	src/patterns/patterns_lamps.c \
	src/patterns/patterns_windows.c \
	src/patterns/patterns_glass.c \
	src/patterns/patterns_floor.c \
	src/patterns/patterns_outside.c \
	src/patterns/patterns_pots.c \
	src/patterns/patterns_trees.c
OBJS = $(SRCS:.c=.o)

MLX_DIR = mlx42
MLX_URL = https://github.com/codam-coding-college/MLX42.git
MLX_VERSION = v2.4.2
MLX_BUILD = $(MLX_DIR)/build
MLX_LIB = $(MLX_BUILD)/libmlx42.a
MLX_INC = -I$(MLX_DIR)/include/MLX42

LIBFT_DIR = libft
LIBFT_LIB = libft/libft.a
INCLUDES = -Iinclude -I$(LIBFT_DIR) $(MLX_INC)
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = $(MLX_LIB) -L$(LIBFT_DIR) -lglfw -ldl -lpthread -lm -lft

all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c include/so_long.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# libft's own Makefile decides what to rebuild; so_long relinks only if
# libft.a really changed.
$(LIBFT_LIB): FORCE
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(MLX_LIB):
	if [ ! -d $(MLX_DIR) ]; then \
		git clone --depth 1 --branch $(MLX_VERSION) $(MLX_URL) $(MLX_DIR); \
	fi
	if [ ! -f $(MLX_LIB) ]; then \
		cmake $(MLX_DIR) -B $(MLX_BUILD) && \
		cmake --build $(MLX_BUILD) -j4; \
	fi

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	rm -rf $(MLX_BUILD)

re: fclean all

# patch: replace assets/ in the working tree with assets/ from the public GitHub copy
# of this project. Works in any clone (also without that remote): it fetches by URL.
# unpatch: undo it, back to the assets/ of the last commit.
PATCH_URL = https://github.com/IshtarRodrev/so_long.git
PATCH_REF = master
ASSETS_DIR = assets

patch:
	git fetch --quiet $(PATCH_URL) $(PATCH_REF)
	git restore --source=FETCH_HEAD --worktree -- $(ASSETS_DIR)
	@echo "$(ASSETS_DIR)/ patched from $(PATCH_URL) ($(PATCH_REF)); 'make unpatch' to undo"

unpatch:
	git restore -- $(ASSETS_DIR)

FORCE:

.PHONY: all clean fclean re patch unpatch FORCE
