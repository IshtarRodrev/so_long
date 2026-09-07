#include "MLX42.h"
#include "so_long.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

void draw_player_tile(int x, int y)
{
    mlx_texture_t *tex;
    uint32_t bg;
    int i;
    int j;
    int sx;
    int sy;
    uint8_t *p;
    int frame_idx;

    frame_idx = g_game.player_frame
        % g_game.player_frame_count[g_game.player_dir];
    tex = g_game.player_tex[g_game.player_dir][frame_idx];
    bg = ((uint32_t)tile_color('0') << 8) | 0xFF;
    i = 0;
    while (i < TILE_SIZE)
    {
        j = 0;
        while (j < TILE_SIZE)
        {
            sx = (int)((uint32_t)j * tex->width / TILE_SIZE);
            sy = (int)((uint32_t)i * tex->height / TILE_SIZE);
            p = tex->pixels + ((size_t)sy * tex->width + sx) * 4;
            mlx_put_pixel(g_game.img, x * TILE_SIZE + j,
                y * TILE_SIZE + i, blend_pixel(p, bg));
            j++;
        }
        i++;
    }
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
                y * TILE_SIZE + i, rgba);
            j++;
        }
        i++;
    }
}

void render_map(void)
{
    int y;
    int x;
    int mx;
    int my;

    update_camera();
    y = 0;
    while (y < g_game.view_rows)
    {
        x = 0;
        while (x < g_game.view_cols)
        {
            mx = g_game.cam_x + x;
            my = g_game.cam_y + y;
            if (g_game.map[my][mx] == 'P')
                draw_player_tile(x, y);
            else
                draw_tile(x, y, tile_color(g_game.map[my][mx]));
            x++;
        }
        y++;
    }
}
