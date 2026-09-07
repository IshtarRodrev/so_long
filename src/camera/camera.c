#include "so_long.h"

static void compute_viewport_size(void)
{
    g_game.view_cols = g_game.cols < VIEWPORT_COLS
        ? g_game.cols : VIEWPORT_COLS;
    g_game.view_rows = g_game.rows < VIEWPORT_ROWS
        ? g_game.rows : VIEWPORT_ROWS;
}

static void clamp_camera(void)
{
    int max_cam_x;
    int max_cam_y;

    max_cam_x = g_game.cols - g_game.view_cols;
    max_cam_y = g_game.rows - g_game.view_rows;
    if (g_game.cam_x < 0)
        g_game.cam_x = 0;
    if (g_game.cam_y < 0)
        g_game.cam_y = 0;
    if (g_game.cam_x > max_cam_x)
        g_game.cam_x = max_cam_x;
    if (g_game.cam_y > max_cam_y)
        g_game.cam_y = max_cam_y;
}

void init_camera(void)
{
    int px;
    int py;

    px = 0;
    py = 0;
    find_player(&px, &py);
    compute_viewport_size();
    g_game.cam_x = px - g_game.view_cols / 2;
    g_game.cam_y = py - g_game.view_rows / 2;
    clamp_camera();
}

void update_camera(void)
{
    int px;
    int py;

    px = 0;
    py = 0;
    find_player(&px, &py);
    compute_viewport_size();
    if (px - g_game.cam_x < CAMERA_MARGIN)
        g_game.cam_x = px - CAMERA_MARGIN;
    else if (px - g_game.cam_x > g_game.view_cols - 1 - CAMERA_MARGIN)
        g_game.cam_x = px - (g_game.view_cols - 1 - CAMERA_MARGIN);
    if (py - g_game.cam_y < CAMERA_MARGIN)
        g_game.cam_y = py - CAMERA_MARGIN;
    else if (py - g_game.cam_y > g_game.view_rows - 1 - CAMERA_MARGIN)
        g_game.cam_y = py - (g_game.view_rows - 1 - CAMERA_MARGIN);
    clamp_camera();
}
