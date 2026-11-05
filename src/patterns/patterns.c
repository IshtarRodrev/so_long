#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

static mlx_texture_t *load_required_texture(const char *path)
{
    mlx_texture_t *tex;

    tex = mlx_load_png(path);
    if (!tex)
    {
        ft_printf("Error: failed to load sprite '%s'\n", path);
        exit(1);
    }
    return (tex);
}

static mlx_texture_t *load_named(const char *name, const char *direction)
{
    char path[128];

    ft_strlcpy(path, SPRITE_DIR "/", sizeof(path));
    ft_strlcat(path, name, sizeof(path));
    ft_strlcat(path, direction, sizeof(path));
    return (mlx_load_png(path));
}

/* Loads <name>_down.png, <name>_up.png, <name>_left.png and <name>_right.png. */
static void load_faces(mlx_texture_t **tex, const char *name)
{
    tex[FACE_DOWN] = load_named(name, "_down.png");
    tex[FACE_UP] = load_named(name, "_up.png");
    tex[FACE_LEFT] = load_named(name, "_left.png");
    tex[FACE_RIGHT] = load_named(name, "_right.png");
}

static void load_required_faces(mlx_texture_t **tex, const char *name)
{
    int face;

    load_faces(tex, name);
    face = 0;
    while (face < FACE_COUNT)
    {
        if (!tex[face])
        {
            ft_printf("Error: failed to load the sprites of '%s'\n", name);
            exit(1);
        }
        face++;
    }
}

void load_pattern_sprites(void)
{
    load_required_faces(g_game.desk_tex, "desk");
    load_required_faces(g_game.table_tex, "table");
    g_game.broken_sign_tex = load_required_texture(BROKEN_SIGN_SPRITE_PATH);
    g_game.facing_wall_tex = mlx_load_png(WALL_DOWN_SPRITE_PATH);
    g_game.glass_down_right_tex = mlx_load_png(GLASS_DOWN_RIGHT_SPRITE_PATH);
    g_game.glass_down_left_tex = mlx_load_png(GLASS_DOWN_LEFT_SPRITE_PATH);
    g_game.shower_tex[FACE_RIGHT] = mlx_load_png(SHOWER_RIGHT_SPRITE_PATH);
    g_game.shower_tex[FACE_LEFT] = mlx_load_png(SHOWER_LEFT_SPRITE_PATH);
    load_faces(g_game.toilet_tex, "toilet");
    load_faces(g_game.lockers_tex, "lockers");
    load_faces(g_game.sink_tex, "sink");
    load_faces(g_game.kitchen_tex, "kitchen");
    load_faces(g_game.coffee_tex, "coffee");
    load_faces(g_game.water_cooler_tex, "water_cooler");
    load_faces(g_game.fridge_tex, "fridge");
    load_faces(g_game.vending_tex, "vending_machine");
}

/* The player's starting tile ('P') is floor. */
static char tile_at(int mx, int my)
{
    if (my < 0 || my >= g_game.rows || mx < 0 || mx >= g_game.cols)
        return ('\0');
    if (g_game.map[my][mx] == 'P')
        return ('0');
    return (g_game.map[my][mx]);
}

static bool row_is(int start, int end, int my, char tile)
{
    while (start <= end)
    {
        if (tile_at(start, my) != tile)
            return (false);
        start++;
    }
    return (true);
}

/*
** A kitchen starts with a water cooler and a coffee machine, and ends with a
** fridge, or two fridges if it is longer than 7. Every tile in between is a
** kitchen tile.
*/
static mlx_texture_t *kitchen_part_texture(int index, int length, int face)
{
    if (index == 0)
        return (g_game.water_cooler_tex[face]);
    if (index == 1)
        return (g_game.coffee_tex[face]);
    if (index == length - 1 || (length > 7 && index == length - 2))
        return (g_game.fridge_tex[face]);
    return (g_game.kitchen_tex[face]);
}

static bool column_is(int start, int end, int mx, char tile)
{
    while (start <= end)
    {
        if (tile_at(mx, start) != tile)
            return (false);
        start++;
    }
    return (true);
}

/* True if a straight run with these two ends and this length is equipment. */
static bool is_equipment_run(char first, char last, int length)
{
    if (first == '1' && last == '1')
        return (length >= 2);
    if (first == '0' && last == '0')
        return (length >= 4);
    return (length == 2 && (first == '1' || last == '1')
        && (first == '0' || last == '0'));
}

/* Which sprite a straight run of collectibles gets, given what is at its two ends. */
static mlx_texture_t *run_texture(char first, char last, int index, int length,
    int face)
{
    if (!is_equipment_run(first, last, length))
        return (NULL);
    if (first == '1' && last == '1' && length == 2)
        return (g_game.sink_tex[face]);
    if (first == '1' && last == '1' && length == 3)
        return (g_game.toilet_tex[face]);
    if (first == '1' && last == '1')
        return (g_game.lockers_tex[face]);
    if (length == 2)
        return (g_game.vending_tex[face]);
    return (kitchen_part_texture(index, length, face));
}

/*
** True if the column at (mx, my) is 2 or more collectibles with walls along one
** long side and floor along the other, and is equipment. Gives its sprite, which
** is NULL if the picture is missing. It faces the floor: right if the wall is on
** the left, left if the wall is on the right.
*/
static bool column_sprite(int mx, int my, mlx_texture_t **sprite)
{
    int start;
    int end;
    int face;

    start = my;
    while (tile_at(mx, start - 1) == 'C')
        start--;
    end = my;
    while (tile_at(mx, end + 1) == 'C')
        end++;
    if (column_is(start, end, mx - 1, '1') && column_is(start, end, mx + 1, '0'))
        face = FACE_RIGHT;
    else if (column_is(start, end, mx - 1, '0')
        && column_is(start, end, mx + 1, '1'))
        face = FACE_LEFT;
    else
        return (false);
    if (!is_equipment_run(tile_at(mx, start - 1), tile_at(mx, end + 1),
            end - start + 1))
        return (false);
    *sprite = run_texture(tile_at(mx, start - 1), tile_at(mx, end + 1),
            my - start, end - start + 1, face);
    return (true);
}

/*
** Returns the sprite for a row of collectibles with walls along one long side
** and floor along the other, or NULL if the row at (mx, my) is not like that.
** Walls at both ends: 2 long is sinks, 3 long is toilets, longer is lockers.
** Wall at one end and floor at the other: 2 long is vending machines.
** Floor at both ends: 4 or more long is a kitchen, starting from the left.
** A row faces the floor: down if the wall is above it, up if the wall is below.
*/
static mlx_texture_t *row_texture(int mx, int my)
{
    int start;
    int end;
    char left;
    char right;
    int face;

    start = mx;
    while (tile_at(start - 1, my) == 'C')
        start--;
    end = mx;
    while (tile_at(end + 1, my) == 'C')
        end++;
    if (!(row_is(start, end, my - 1, '1') && row_is(start, end, my + 1, '0'))
        && !(row_is(start, end, my - 1, '0') && row_is(start, end, my + 1, '1')))
        return (NULL);
    face = FACE_UP;
    if (tile_at(mx, my - 1) == '1')
        face = FACE_DOWN;
    left = tile_at(start - 1, my);
    right = tile_at(end + 1, my);
    return (run_texture(left, right, mx - start, end - start + 1, face));
}

/* True if (mx, my) is a floor tile with walls above and below it. */
static bool is_corridor(int mx, int my)
{
    return (tile_at(mx, my) == '0' && tile_at(mx, my - 1) == '1'
        && tile_at(mx, my + 1) == '1');
}

/*
** True if (mx, my) is a seat in a sideways desk block: floor on one side, a wall
** on the other, and either another seat two tiles above or below it in the same
** column, or walls above and below it and a seat diagonally across its wall.
*/
static bool is_sideways_desk(int mx, int my)
{
    char left;
    char right;
    char top;
    char bottom;
    int wall_x;

    left = tile_at(mx - 1, my);
    right = tile_at(mx + 1, my);
    top = tile_at(mx, my - 1);
    bottom = tile_at(mx, my + 1);
    if (tile_at(mx, my) != 'C' || !((left == '0' && right == '1')
            || (left == '1' && right == '0')))
        return (false);
    wall_x = mx - 1;
    if (right == '1')
        wall_x = mx + 1;
    return ((top == '1' && bottom == '1' && (tile_at(wall_x, my - 1) == 'C'
                || tile_at(wall_x, my + 1) == 'C'))
        || (top == '1' && tile_at(mx, my - 2) == 'C')
        || (bottom == '1' && tile_at(mx, my + 2) == 'C'));
}

/*
** Returns the sprite for the wall at (mx, my) if it is table in a sideways desk
** block, or NULL. It has seats above and below it, or at a corner one seat above
** or below it and one beside it, and floor on its open side.
*/
static mlx_texture_t *sideways_table_texture(int mx, int my)
{
    char left;
    char right;
    int above;
    int below;
    int beside;

    left = tile_at(mx - 1, my);
    right = tile_at(mx + 1, my);
    above = is_sideways_desk(mx, my - 1);
    below = is_sideways_desk(mx, my + 1);
    beside = is_sideways_desk(mx - 1, my) || is_sideways_desk(mx + 1, my);
    if (!((above && below) || ((above || below) && beside)))
        return (NULL);
    if (left == '0')
        return (g_game.table_tex[FACE_LEFT]);
    if (right == '0')
        return (g_game.table_tex[FACE_RIGHT]);
    return (NULL);
}

/*
** A seat in a table line one tile thick: walls on two opposite sides and floor on
** the other two. Vertical lines always face left, horizontal lines face the
** centre of the map.
*/
static mlx_texture_t *thin_line_desk_texture(int mx, int my)
{
    char left;
    char right;
    char top;
    char bottom;

    left = tile_at(mx - 1, my);
    right = tile_at(mx + 1, my);
    top = tile_at(mx, my - 1);
    bottom = tile_at(mx, my + 1);
    if (top == '1' && bottom == '1' && left == '0' && right == '0')
        return (g_game.desk_tex[FACE_LEFT]);
    if (left != '1' || right != '1' || top != '0' || bottom != '0')
        return (NULL);
    if (my < g_game.rows / 2)
        return (g_game.desk_tex[FACE_DOWN]);
    return (g_game.desk_tex[FACE_UP]);
}

/*
** Returns the sprite for the collectible at (mx, my), or NULL if no rule fits.
** Toilets, sinks, kitchens and vending machines are recognised by their row or
** column.
** A shower has walls above, below and on one side, and opens into a corridor.
** Collectibles side by side against a wall are other equipment, not desks.
*/
mlx_texture_t *collectible_tile_texture(int mx, int my)
{
    mlx_texture_t *row;
    bool beside;
    char top;
    char bottom;

    row = row_texture(mx, my);
    if (row)
        return (row);
    if (column_sprite(mx, my, &row))
        return (row);
    beside = (tile_at(mx - 1, my) == 'C' || tile_at(mx + 1, my) == 'C');
    top = tile_at(mx, my - 1);
    bottom = tile_at(mx, my + 1);
    if (top == '1' && bottom == '1' && tile_at(mx - 1, my) == '1'
        && is_corridor(mx + 1, my))
        return (g_game.shower_tex[FACE_RIGHT]);
    if (top == '1' && bottom == '1' && tile_at(mx + 1, my) == '1'
        && is_corridor(mx - 1, my))
        return (g_game.shower_tex[FACE_LEFT]);
    if (is_sideways_desk(mx, my) && tile_at(mx - 1, my) == '0')
        return (g_game.desk_tex[FACE_LEFT]);
    if (is_sideways_desk(mx, my))
        return (g_game.desk_tex[FACE_RIGHT]);
    if (top == '0' && (bottom == 'C' || (bottom == '1' && !beside)))
        return (g_game.desk_tex[FACE_UP]);
    if (bottom == '0' && (top == 'C' || (top == '1' && !beside)))
        return (g_game.desk_tex[FACE_DOWN]);
    return (thin_line_desk_texture(mx, my));
}

/*
** Returns the sprite for the wall at (mx, my), or NULL if it is a plain wall.
** A wall is table if it sits between two collectibles, or if it is the corner
** of a desk block: a collectible on one side and one above or below it.
*/
mlx_texture_t *empty_table_texture(int mx, int my)
{
    mlx_texture_t *sideways;
    int sides;
    char top;
    char bottom;

    sideways = sideways_table_texture(mx, my);
    if (sideways)
        return (sideways);
    sides = (tile_at(mx - 1, my) == 'C') + (tile_at(mx + 1, my) == 'C');
    top = tile_at(mx, my - 1);
    bottom = tile_at(mx, my + 1);
    if (top == '0' && (sides == 2 || (sides == 1 && bottom == 'C')))
        return (g_game.table_tex[FACE_UP]);
    if (bottom == '0' && (sides == 2 || (sides == 1 && top == 'C')))
        return (g_game.table_tex[FACE_DOWN]);
    return (NULL);
}

/* True if the walls at (mx, my) and (mx + dx, my + 1) touch only at a corner. */
static bool diagonal_step(int mx, int my, int dx)
{
    return (tile_at(mx, my) == '1' && tile_at(mx + dx, my + 1) == '1'
        && tile_at(mx + dx, my) != '1' && tile_at(mx, my + 1) != '1');
}

/*
** How many walls the diagonal chain through the wall at (mx, my) has. It runs
** down to the right if dx is 1, and down to the left if dx is -1.
*/
static int diagonal_length(int mx, int my, int dx)
{
    int length;
    int x;
    int y;

    length = 1;
    x = mx;
    y = my;
    while (diagonal_step(x, y, dx) && ++length)
    {
        x += dx;
        y++;
    }
    x = mx;
    y = my;
    while (diagonal_step(x - dx, y - 1, dx) && ++length)
    {
        x -= dx;
        y--;
    }
    return (length);
}

/*
** Returns the sprite for a wall that is glass fence or faces the camera, or NULL
** for other walls and for walls whose sprite file is missing.
** Glass fence: more than 3 walls in a diagonal chain, touching only at corners.
** Facing the camera: floor, a collectible or the exit below it.
*/
mlx_texture_t *facing_wall_texture(int mx, int my)
{
    char below;

    if (g_game.glass_down_right_tex && diagonal_length(mx, my, 1) > 3)
        return (g_game.glass_down_right_tex);
    if (g_game.glass_down_left_tex && diagonal_length(mx, my, -1) > 3)
        return (g_game.glass_down_left_tex);
    below = tile_at(mx, my + 1);
    if (below == '0' || below == 'C' || below == 'E')
        return (g_game.facing_wall_tex);
    return (NULL);
}
