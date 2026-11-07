*This project has been created as part of the 42 curriculum by akechedz*
# so_long
This project is a small 2D game. Its purpose is to learn working with textures, sprites, and other basic gameplay elements.
# Description
A “Description” section that clearly presents the project, including its goal and a brief overview.

## Project structure

```
so_long/
├── Makefile
├── include/so_long.h       all types, defines and prototypes
├── libft/                  own libft (+ ft_printf, get_next_line, ft_realloc)
├── maps/                   .ber maps: playable ones, err_*.ber error cases
├── assets/sprites/         the images, one folder per object (desk/, window/, player/front/ …)
└── src/
    ├── main.c
    ├── game/       game flow     game · menu · input · error · cleanup
    ├── map/        map file      map_load · map_read · map · map_path · map_path_check
    │                             map_tile (tile helpers) · flood (the shared flood fill)
    ├── progress/   progress      progress · collectibles (random task selection)
    ├── render/     drawing       render_init · render_map · render_tiles · render_images · camera
    ├── textures/   load / free   textures · textures_player · textures_furniture
    │                             textures_glass · textures_free
    └── patterns/   tile rules    which sprite / floor / decoration each tile gets:
                                  tile · collectible · lines · runs · desks · lamps · lamp_spot
                                  windows · glass · floor · outside · pots · trees · init
```

Each folder has one job: `map/` reads and validates the map, `patterns/` decides how every tile looks (rules only, no loading or drawing), `textures/` loads the images, and `render/` puts them in the window as MLX42 image instances.

## Tile render variants

Collectibles (`C`) and walls (`1`) are drawn with different sprites depending on the tiles around them, so a map turns into an office floor plan. The rules live in `src/patterns/`. Equipment always faces the floor side (up, down, left or right).

| Variant | Shape that triggers it |
|---|---|
| sink / toilet / lockers | a row (or column) of 2 / 3 / 4+ `C`, walls at both ends, wall along one side, floor along the other |
| vending machines | 2 `C`, wall at one end, floor at the other |
| kitchen (water cooler, coffee, kitchen, fridge) | 4+ `C`, floor at both ends |
| shower | 1 `C` between walls above and below, wall on one side, a corridor on the other |
| desk up / down | single `C` with floor on one side and wall on the other |
| table | wall between two desks |
| neon lamp | wall touching at least 4 collectibles, sides and corners counted (the middle of a desk cluster) — one lamp per island of walls and collectibles (touching by a side), on its first such wall; never next to a toilet |
| window | outer wall with the outside right above it and floor below: in each horizontal run of 6+ walls (`WINDOW_MIN_RUN`) every 2nd and 3rd tile (wall, window, window, …); the tile above shows through the glass |
| facing wall | wall with floor, `C` or `E` below |
| glass fence | 4+ walls in a diagonal chain, touching only at corners; the side next to a closed area is drawn dark, the side next to the outside is drawn as grass (`glass_fence/*_dark_*.png`, `*_grass_*.png`) |
| dark floor | floor the player can never reach, closed in by walls (closed rooms, courtyards, space only reachable through the exit) |
| grass | floor the player can never reach that is connected to the edge of the map (the outside) |
| asphalt | outside floor with a wall at most 3 tiles below it (a 3-row strip along the upper side of horizontal walls; `ASPHALT_ROWS`) |
| tree | unreachable floor (inside or outside) with no wall or other tree within 5 tiles in any direction — trees stand 6 tiles apart (`TREE_SPACING`); the map edge does not count |
| flowerpots | on dark floor: the rightmost column, the top row and the bottom row of each closed area — only if that rightmost column is a vertical row (2+ tiles); an area ending in a diagonal gets none |
| empty floor tile (only the warning sign) | `C` with no matching shape |

`maps/labyrinth.ber` uses every variant.

# Instructions
An “Instructions” section containing any relevant information about compilation, installation, and/or execution.
# Resources
• A “Resources” section listing classic references related to the topic (documentation, articles, tutorials, etc.), as well as a description of how AI was used — specifying for which tasks and which parts of the project.