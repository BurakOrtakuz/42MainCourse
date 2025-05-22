# so_long

> A 42 school project to create a simple 2D game using a minimal graphics library.

## 📚 Description

`so_long` is a basic 2D graphical game developed using the MiniLibX library. The objective is to build a simple game where the player can move around a map, collect items, and reach the exit.

This project teaches:
- Parsing and validating input files
- Working with 2D arrays and basic game logic
- Handling player input (keyboard events)
- Drawing images with MiniLibX
- Basic pathfinding validation

## 🎮 Game Overview

The game:
- Loads a map from a `.ber` file.
- The player must collect all collectibles (`C`) and reach the exit (`E`).
- The map is composed of walls (`1`), empty space (`0`), collectibles (`C`), an exit (`E`), and the player start position (`P`).

## 🛠️ Usage

Compile the project with the MiniLibX library and run it with a valid map file.

```bash
make
./so_long maps/level1.ber
```

## 🎨 Controls

| Key         | Action          |
|-------------|-----------------|
| W / ↑       | Move Up         |
| A / ←       | Move Left       |
| S / ↓       | Move Down       |
| D / →       | Move Right      |
| ESC         | Exit Game       |

## 🗺️ Map Format

- Must be a rectangular grid in a `.ber` file.
- Must have:
  - Exactly one `P` (player)
  - At least one `C` (collectible)
  - Exactly one `E` (exit)
- Must be enclosed by walls (`1`)
- Only valid characters: `01CEP`

### Example:
```
111111
1P0C01
100001
1C0E11
111111
```

## 🧪 Map Validation

The game performs checks before launching:
- Is the map rectangular?
- Are walls surrounding the map?
- Are all characters valid?
- Is the map solvable (using pathfinding)?

## 📁 File Structure

```
so_long/
├── so_long.c           # Main game loop and initialization
├── map_parser.c        # Map reading and validation
├── draw.c              # Rendering game elements
├── input.c             # Handling keyboard inputs
├── utils.c             # Helpers
├── so_long.h           # Header file
├── assets/             # Images for player, wall, collectibles, etc.
├── maps/               # Sample map files
```

## 🖼️ MiniLibX

This project uses the MiniLibX graphics library provided by 42.

## ⚙️ Compilation

Make sure MiniLibX is installed. Then run:

```bash
make
```

To clean compiled files:

```bash
make clean
```

## 🚫 Limitations

- No enemy logic or animations
- Minimal GUI, no audio

---