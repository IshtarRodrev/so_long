# so_long refactor checklist

## Norm requirements
- [ ] funcuions must be not longer than 25 lines
- [ ] inside each file functions must be logically separated into groups, 5 function in each, with commented divider that entitles each group. Like: 
/******************************************************************************/
/*								VALIDATION HELPERS							  */
/******************************************************************************/
## Build / wiring
- [x] Point `Makefile` `SRCS` at `src/main.c` (+ `src/params.c`, `src/controls.c`) instead of `game.c`, once those are implemented
- [x] Implement `check_params()` in `src/params.c` — parse `argv[1]` as the map path, validate extension (`.ber`), call `read_map_file` + `validate_map` + `path_is_valid`
- [x] Implement `init_game()` in `src/controls.c` — mlx_init / new_image / image_to_window / key_hook / mlx_loop (move this out of `game.c`)
- [x] Move `t_game g_game;` definition out of `game.c` into `src/main.c` — discovered while wiring the above: it was the *only* definition of the global, and `game.c` is no longer in `SRCS`, so the link would have failed with an undefined reference
- [x] Decide fate of `game.c` — deleted (along with the stale `game.o`); fully superseded by `src/main.c` + `params.c` + `controls.c`

## Map validation
- [x] Fix `read_map_file()` not stripping CRLF (`\r\n`) line endings — only `\n` was stripped, leaving a trailing `\r` treated as a real map character; caused false "border must be walls" / "invalid character" rejections on `floor0.ber`, `floor1.ber`, `min.ber` (found while testing `./game` against the sample maps)
- [ ] Wire `validate_map()` into the load path (currently dead code)
- [ ] Wire `path_is_valid()` (flood-fill reachability) into the load path (currently dead code)
- [ ] Fix `map.c:135` FIXME — enforce rectangular map (all rows same length as row 0), reject otherwise
- [ ] Fix `g_game.cols` computation (`map.c:309`) to rely on the now-enforced rectangular width, not just row 0 blindly

## Gameplay logic
- [ ] Auto-fit map scale to window: turn `TILE_SIZE` (currently a hardcoded `#define TILE_SIZE 40` in `src/game_render.c`, also used for window sizing in `game.c`) into a runtime value on `g_game`, computed at load time from `g_game.rows`/`g_game.cols` so the whole map fits inside a fixed target window size (e.g. 1280x800) — shrink tiles down to a defined minimum size (e.g. 16px), below which tiles stop shrinking further
- [ ] Camera/viewport scrolling for maps too large to fit at that minimum tile size: cap the MLX42 window at the target size, render only the visible NxM-tile region of `g_game.map` (not the whole map) each frame, and pan that visible region as the player approaches a window edge — clamp so the camera never scrolls past the map's bounds
- [ ] Track collectible count on load; decrement in `move_player()` when stepping onto `'C'`
- [ ] Win condition: reaching `'E'` only wins when collectibles remaining == 0; print/trigger win state
- [ ] Fix `move_player()` return value — currently always `return (0)`, even after a successful move (`game_controls.c:52`)
- [ ] Move counter + printf to stdout on each valid move (42 subject requirement)

## Cleanup / leaks
- [ ] Free `g_game.map` (via `free_map`-equivalent) on exit — win, ESC, and window-close paths
- [ ] Call `mlx_terminate`/destroy image before `exit()` — ESC currently calls `exit(0)` directly with zero cleanup (`game_controls.c:61`)
- [ ] Audit all exit paths (invalid map, malloc failure, mlx_init failure) for the same leak — not just the happy path

## Makefile
- [x] Add missing `fclean` and `re` rules to the active Makefile (currently only `all` and `clean` are implemented at the bottom of the file; `fclean`/`re` only exist in the dead commented-out block at `Makefile:1-34`) — `fclean` should do what `clean` does plus remove `$(NAME)`; `re` should be `fclean` followed by `all`
- [x] Uncomment `fclean` and `re` in the `.PHONY` line (`Makefile:86`); drop the stray `make` token there — it doesn't correspond to any target

## Params
- [x] ~~`check_params()` falls back to a hardcoded default map when run with no argument~~ — **superseded below**: replaced by an in-window map-choice menu, so argv is no longer read at all (`main.c` just calls `init_game()`); `check_params`/`DEFAULT_MAP` were removed from `src/params.c`. This means `./game` is no longer 42-subject compliant in the strict "map path as argv" sense — flag if that matters for grading.

## Map menu (new)
- [x] In-window map-choice screen before gameplay starts (`src/menu.c`, new file): `mlx_init`s a fixed `800x600` window first (`MENU_WIN_W`/`MENU_WIN_H` in `so_long.h`), scans `maps/` at runtime for `*.ber` files (`<dirent.h>`, capped at `MENU_MAX_MAPS` = 9), lists them via `mlx_put_string`, and lets you pick with number keys 1-9 (ESC quits)
- [x] Selecting a map runs it through the existing `load_and_validate()` (validate_map + path_is_valid); on failure shows an in-window status line and stays on the menu instead of crashing/exiting
- [x] On success: deletes the menu's text images, resizes the window + image to the chosen map's actual dimensions (`mlx_set_window_size` + `mlx_resize_image`), swaps the key hook from `menu_key_hook` to the gameplay `key_hook`, and renders — all within one single `mlx_loop` call (never calls it twice)
- [ ] Not yet tested end-to-end (can't build here — no `cc`/`make` on this machine); verify on your Linux/WSL side: menu shows all 5 maps, invalid ones (`floorEG.ber`/`floorOG.ber`, still empty) show the status line and let you pick again, valid ones resize and start correctly
- [ ] Decide whether losing pure-argv compliance (see the crossed-out Params item above) is acceptable, or whether argv should be restored as a menu-skipping override

## Housekeeping
- [ ] Delete ~90 lines of commented-out dead code in `map.c:7-97` (old `parse_map_file`, `free_lines`, `strip_newline`, `append_line`)
- [ ] Move `int i;` declaration in `path_is_valid` (`map.c:234`) to top of block — Norm violation
- [ ] Re-check whole diff against 42 Norm once logic is finalized (norminette)
