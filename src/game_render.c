#include "MLX42.h"
#include "so_long.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*FIXME: Gobal variables are not allowed by the norm*/
static const char *g_dir_names[DIR_COUNT] = {"front", "back", "left", "right"};

int tile_color(char tile)
{
    if (tile == '1')
        return (0xE8E8E8);
    if (tile == 'C')
        return (0xFFD700);
    if (tile == 'E')
        return (0x32CD32);
    return (0x505050);
}

static char *sprite_path(const char *dir_name, int frame)
{
    char buf[128];

    snprintf(buf, sizeof(buf), "%s/%s_%02d.png", SPRITE_DIR, dir_name, frame);
    return (ft_strdup(buf));
}

static void load_direction_sprites(int d)
{
    int f;
    char *path;

    f = 0;
    while (f < SPRITE_FRAMES)
    {
        path = sprite_path(g_dir_names[d], f + 1);
        if (access(path, F_OK) != 0)
        {
            free(path);
            break ;
        }
        g_game.player_tex[d][f] = mlx_load_png(path);
        free(path);
        if (!g_game.player_tex[d][f])
        {
            ft_printf("Error: failed to load player sprite\n");
            exit(1);
        }
        f++;
    }
    g_game.player_frame_count[d] = f;
    if (f == 0)
    {
        ft_printf("Error: no sprites found for direction '%s'\n",
            g_dir_names[d]);
        exit(1);
    }
}

void load_player_sprites(void)
{
    int d;

    d = 0;
    while (d < DIR_COUNT)
    {
        load_direction_sprites(d);
        d++;
    }
}

static uint32_t blend_pixel(uint8_t *p, uint32_t bg)
{
    uint8_t a;
    uint8_t out[3];
    int i;

    a = p[3];
    if (a == 255)
        return (((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16)
            | ((uint32_t)p[2] << 8) | 0xFF);
    i = 0;
    while (i < 3)
    {
        out[i] = (uint8_t)(((int)p[i] * a
                    + (int)((bg >> (24 - i * 8)) & 0xFF) * (255 - a)) / 255);
        i++;
    }
    return (((uint32_t)out[0] << 24) | ((uint32_t)out[1] << 16)
        | ((uint32_t)out[2] << 8) | 0xFF);
}

static uint32_t texture_pixel(mlx_texture_t *tex, int i, int j, uint32_t bg)
{
    int size;
    int sx;
    int sy;

    size = (int)tex->width;
    if ((int)tex->height > size)
        size = (int)tex->height;
    sx = j * size / TILE_SIZE - (size - (int)tex->width) / 2;
    sy = i * size / TILE_SIZE - (size - (int)tex->height) / 2;
    if (sx < 0 || sx >= (int)tex->width || sy < 0 || sy >= (int)tex->height)
        return (bg);
    return (blend_pixel(tex->pixels + ((size_t)sy * tex->width + sx) * 4, bg));
}

/* Draws tex over bg. If under is set, it is drawn between the two. */
static void draw_texture_tile(mlx_texture_t *under, mlx_texture_t *tex,
    t_point pos, uint32_t bg)
{
    int i;
    int j;
    uint32_t color;

    i = 0;
    while (i < TILE_SIZE)
    {
        j = 0;
        while (j < TILE_SIZE)
        {
            color = bg;
            if (under)
                color = texture_pixel(under, i, j, bg);
            mlx_put_pixel(g_game.img, pos.x * TILE_SIZE + j,
                SCORE_BAR_HEIGHT + pos.y * TILE_SIZE + i,
                texture_pixel(tex, i, j, color));
            j++;
        }
        i++;
    }
}

void draw_player_tile(int x, int y)
{
    mlx_texture_t *tex;
    mlx_texture_t *under;
    int frame_idx;
    char tile;

    frame_idx = g_game.player_frame
        % g_game.player_frame_count[g_game.player_dir];
    tex = g_game.player_tex[g_game.player_dir][frame_idx];
    under = NULL;
    tile = '0';
    if (is_collected(g_game.cam_x + x, g_game.cam_y + y))
    {
        under = collectible_tile_texture(g_game.cam_x + x, g_game.cam_y + y);
        if (!under)
            tile = 'C';
    }
    draw_texture_tile(under, tex, (t_point){x, y},
        ((uint32_t)tile_color(tile) << 8) | 0xFF);
}

void load_exit_sprite(void)
{
    g_game.exit_tex = mlx_load_png(EXIT_SPRITE_PATH);
    if (!g_game.exit_tex)
    {
        ft_printf("Error: failed to load exit sprite\n");
        exit(1);
    }
}

void draw_exit_tile(int x, int y)
{
    draw_texture_tile(NULL, g_game.exit_tex, (t_point){x, y},
        ((uint32_t)tile_color('0') << 8) | 0xFF);
}

void draw_tile(int x, int y, int color)
{
    int i;
    int j;
    uint32_t rgba;

    rgba = ((uint32_t)color << 8) | 0xFF;
    i = 0;
    while (i < TILE_SIZE)
    {
        j = 0;
        while (j < TILE_SIZE)
        {
            mlx_put_pixel(g_game.img, x * TILE_SIZE + j,
                SCORE_BAR_HEIGHT + y * TILE_SIZE + i, rgba);
            j++;
        }
        i++;
    }
}

static void draw_collectible_tile(int x, int y, int mx, int my)
{
    mlx_texture_t *sprite;
    bool collected;
    uint32_t bg;

    sprite = collectible_tile_texture(mx, my);
    collected = is_collected(mx, my);
    bg = ((uint32_t)tile_color('0') << 8) | 0xFF;
    if (sprite && collected)
        draw_texture_tile(NULL, sprite, (t_point){x, y}, bg);
    else if (sprite)
        draw_texture_tile(sprite, g_game.broken_sign_tex, (t_point){x, y}, bg);
    else if (collected)
        draw_tile(x, y, tile_color('1'));
    else
        draw_tile(x, y, tile_color('C'));
}

static void draw_wall_tile(int x, int y, int mx, int my)
{
    mlx_texture_t *tex;

    tex = empty_table_texture(mx, my);
    if (!tex)
        tex = facing_wall_texture(mx, my);
    if (tex)
        draw_texture_tile(NULL, tex, (t_point){x, y},
            ((uint32_t)tile_color('0') << 8) | 0xFF);
    else
        draw_tile(x, y, tile_color('1'));
}

/* The strip above the map: empty at the start, full when all tasks are collected. */
static void draw_score_bar(void)
{
    int width;
    int filled;
    int x;
    int y;

    width = g_game.view_cols * TILE_SIZE - 2 * SCORE_BAR_BORDER;
    filled = width * (g_game.progress.collectibles_total
            - g_game.progress.collectibles_left)
        / g_game.progress.collectibles_total;
    y = -1;
    while (++y < SCORE_BAR_HEIGHT)
    {
        x = -1;
        while (++x < g_game.view_cols * TILE_SIZE)
        {
            if (y >= SCORE_BAR_BORDER && y < SCORE_BAR_HEIGHT - SCORE_BAR_BORDER
                && x >= SCORE_BAR_BORDER && x < SCORE_BAR_BORDER + filled)
                mlx_put_pixel(g_game.img, x, y, 0xFFD700FF);
            else
                mlx_put_pixel(g_game.img, x, y, 0x202020FF);
        }
    }
}

void render_map(void)
{
    int y;
    int x;
    int mx;
    int my;

    update_camera();
    draw_score_bar();
    y = 0;
    while (y < g_game.view_rows)
    {
        x = 0;
        while (x < g_game.view_cols)
        {
            mx = g_game.cam_x + x;
            my = g_game.cam_y + y;
            if (mx == g_game.progress.player.x && my == g_game.progress.player.y)
                draw_player_tile(x, y);
            else if (g_game.map[my][mx] == 'E')
                draw_exit_tile(x, y);
            else if (g_game.map[my][mx] == 'C')
                draw_collectible_tile(x, y, mx, my);
            else if (g_game.map[my][mx] == '1')
                draw_wall_tile(x, y, mx, my);
            else
                draw_tile(x, y, tile_color(g_game.map[my][mx]));
            x++;
        }
        y++;
    }
}
