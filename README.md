*This project has been created as part of the 42 curriculum by ebansse.*

# so_long

A small top-down 2D game written in C with the **MiniLibX** graphics library. A knight explores a map, picks up every collectible, then reaches the exit.

## Gameplay

- Move with **W A S D** or the **arrow keys**
- Collect every item on the map to unlock the exit
- Walk onto the exit to win, and the number of moves is shown
- Every move is counted and printed in the terminal
- Close the window with **Esc** or the window's close button

## Maps

Maps are plain-text `.ber` files built from these characters:

| Char | Meaning |
|---|---|
| `1` | wall |
| `0` | floor |
| `P` | player start (exactly one) |
| `C` | collectible (at least one) |
| `E` | exit (exactly one) |

```
11111111111
1P000C000E1
10110001101
1010C000101
1000010C001
100C1110C01
11111111111
```

A map is rejected if it is not rectangular, is not fully enclosed by walls, has the wrong number of `P`/`E`, has no collectible, contains an unknown character, or if a flood fill shows that some collectible or the exit can't be reached.

## Build & run

Requires Linux with X11 (`libx11-dev`, `libxext-dev`, `libbsd-dev`). MiniLibX is bundled in `mlx/` and built automatically.

```bash
make
./so_long map.ber
```

## Project structure

| Path | Role |
|---|---|
| `main.c` | argument checks, initialisation, window and event loop |
| `map.c`, `map2.c` | map loading, validation (shape, walls, flood fill) and cleanup |
| `hook.c` | keyboard handling and tile drawing |
| `render_move.c` | player movement, collectibles and win condition |
| `img_utils.c`, `img_utils2.c` | XPM loading and drawing sprites into an off-screen image |
| `assets/` | sprites (`0.xpm` to `5.xpm`) |
| `mlx/` | MiniLibX |
