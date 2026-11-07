*This project has been created as part of the 42 curriculum by akechedz*
# so_long
This project is a small 2D game. Its purpose is to learn working with textures, sprites, and other basic gameplay elements.
# Description
You play a member of the 42 bocal on a floor where things keep breaking. Every
collectible (`C`) is a piece of cluster equipment marked with a warning sign: walk
onto it to fix it. When everything works again, the exit (`E`) opens and you can
call it a day.

## The story behind it

Behind every working cluster there is someone from the bocal walking the floor:
a screen that won't wake up, a log in issue, a ticket waiting to be closed.
This game is about that routine, the quiet work that keeps the school running, one
task at a time.

## Special thanks

to [Rayan (rmehadje)](https://profile.intra.42.fr/users/rmehadje) who was just starting as
an IT intern at 42 when the idea for this game came up. We were talking about his
new duties (tickets, cluster maintenance and features of the
[Learning Hub](https://intranet.42heilbronn.de/)) and about a ticket system he was
planning to build for it on top of the school's floor plans. I joked that it sounded
a lot like the tasks in *Among Us*.

He might forget forget that joke already, but I didn't. I took those floor plans, turned them into the tile maps
in `maps/`, and brought the school into this project, with Rayan as the player character.

Unfortunately, it took me so_long to finish the game that Rayan finished his
internship a few days before my evaluation...

## Under the hood

This is the 42 *so_long* project: a small top-down 2D game written in C with MLX42.
The map is a `.ber` file (`0` floor, `1` wall, `C` collectible, `E` exit, `P` player).
The program validates it (rectangular, one `P`, one `E`, at least one `C`, every `C`
and the exit reachable) and prints `Error` with a reason if it is not valid.

Beyond the mandatory part:
- the map is drawn as a 42 Heilbronn floor plan (see *Tile render variants* below);
- maps with more than 10 collectibles get 10 random ones to fix, the rest start fixed;
- a progress bar above the map fills up from red to green;
- a camera follows the player on maps larger than the window;
- everything is drawn with MLX42 images (no pixel-by-pixel drawing), and all memory
  is freed on every exit (ESC, window cross, win, errors).

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

## Tile render variants

Collectibles (`C`) and walls (`1`) get their sprite from the tiles around them. Equipment always faces the floor side (up, down, left or right).

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
**Requirements** (all present on the 42 Heilbronn cluster machines): `cc`, `make`,
`cmake`, the GLFW library, and network access on the first build — the Makefile
downloads [MLX42](https://github.com/codam-coding-college/MLX42) (pinned to `v2.4.2`).

**Build**
```
make            # MLX42 + libft + so_long
make clean      # remove object files
make fclean     # also remove so_long, libft.a and the MLX42 build
make re         # fclean + make
make patch      # update assets/sprites/ from the public GitHub copy of this project
make unpatch    # undo patches: back to the original sprites
```

`make patch` downloads only `assets/sprites/` from
[github.com/IshtarRodrev/so_long/tree/main/assets/sprites](https://github.com/IshtarRodrev/so_long/tree/main/assets/sprites)
(branch `main`, or `make patch PATCH_REF=<branch or tag>`) and copies it over the local
folder: files are replaced or added, never deleted. It is never run by `make`.
`make unpatch` undoes it: replaced files come back from the last commit (`git restore`)
and the files a patch added are deleted; other new sprites of yours are kept, but
uncommitted edits to committed sprites are reverted too.

**Run** — the argument is a path to a `.ber` file; a bare name is also looked up in `maps/`:
```
./so_long maps/floorOG.ber
./so_long labyrinth.ber      # same as maps/labyrinth.ber
./so_long err_two_exits.ber  # every err_*.ber map shows one error message
```

**Controls**: `W A S D` or the arrow keys to move, any key to start from the menu,
`ESC` or the window cross to quit. Every move is printed in the terminal.

# Resources
**References**
- [42 so_long subject](https://projects.intra.42.fr) and the evaluation sheet
- [MLX42 documentation](https://github.com/codam-coding-college/MLX42/tree/master/docs) — images, instances, hooks, textures
- [42 Heilbronn floor plans](https://intranet.42heilbronn.de/floor-plans) — map reference for the `.ber` maps in `maps/`
- [Flood fill / breadth-first search](https://en.wikipedia.org/wiki/Flood_fill) — path check, closed areas, outside, desk islands
- [Xorshift random number generators](https://en.wikipedia.org/wiki/Xorshift) (G. Marsaglia, 2003) — seeded with `gettimeofday`
- [Selection sampling, Knuth's *Algorithm S*](https://en.wikipedia.org/wiki/Reservoir_sampling) — picking the random collectibles in one pass
- [Valgrind](https://valgrind.org/docs/manual/mc-manual.html) and [norminette](https://github.com/42School/norminette)

**AI usage**

Claude Sonnet 5.5 was used as an assistant during development. Every change was
reviewed, tested and is understood by me. It was used for:
- **Sprite pipeline**: I set up a pipeline in which Nano Banana (Google's Gemini
  Flash Image model) draws the sprites from a tile description sheet.
  The sheet has one prompt for every sprite the game loads. Every prompt shares the
  same base rules (pixel art, top-down, flat grey floor, readable at 40x40) and uses
  the office map in `assets/reference/` as the style reference, so all sprites look
  like one set. The up / left / right versions are made from the finished down sprite
  so every object matches from all four sides. Claude helped correcting the prompts in
  the sheet.
- **review**: checking the project against the subject and the evaluation sheet,
  and keeping a TODO list of the issues found;
- **tests**: the `err_*.ber` and `labyrinth.ber` maps generation;
- **structure**: splitting the code into the folders of *Project structure*;
- **tile rules and sprites**: implementing some complex pattern rules for the 
  sprites (flowerpots, trees, lamps, glass fence variants).
