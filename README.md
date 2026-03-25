# Make Guns

A 2D top-down action game built with C++ and SDL3, created by following a game development tutorial. Features a player that can move, jump, and shoot at enemies in a tile-based environment with parallax scrolling backgrounds.

---

## Features

- **Player movement**: Walk, run, jump, and slide with smooth physics
- **Shooting**: Fire bullets with momentum transfer and random spread
- **Enemy AI**: Enemies patrol and chase the player when in range, take damage, and die with animations
- **Collision detection**: AABB collision for player, enemies, bullets, and level tiles
- **Parallax scrolling**: Multi-layer background scrolling at different speeds
- **Sprite animations**: Frame-based animations for player states, enemies, and bullets
- **Audio**: Sound effects for shooting, bullet impacts, and looping background music
- **Fullscreen toggle**: F11 to switch between windowed and fullscreen
- **Debug mode**: F key shows collision boxes and game state

---

## Controls

| Key | Action |
|-----|--------|
| A / D | Move left / right |
| K | Jump |
| J | Shoot |
| F | Toggle debug mode |
| F11 | Toggle fullscreen |

---

## Building

### Requirements

- CMake 3.8+
- C++20 compiler (Visual Studio 2019+ recommended)
- [SDL3](https://github.com/libsdl-org/SDL)
- [SDL3_image](https://github.com/libsdl-org/SDL_image)
- [SDL3_mixer](https://github.com/libsdl-org/SDL_mixer)
- [GLM](https://github.com/g-truc/glm)

### Steps

```sh
cmake --preset default
cmake --build build
```

The executable will be output as `makeguns`.

---

## Project Structure

```
makeguns/
├── data/                   # Game assets
│   ├── audio/              # Sound effects (.wav) and music (.mp3)
│   ├── bg/                 # Parallax background layers
│   ├── tiles/              # Tile sprites (brick, grass, ground, panel)
│   ├── *.png               # Player, enemy, and bullet sprites
├── makeguns/               # Source code
│   ├── makeguns.cpp        # Main game loop and logic
│   ├── makeguns.h          # Main header
│   ├── gameobject.h        # Entity structures and types
│   ├── animation.h/cpp     # Frame-based animation system
│   ├── timer.h/cpp         # Timer utility
│   └── CMakeLists.txt      # Build config
├── CMakeLists.txt          # Root build config
└── CMakePresets.json       # CMake preset definitions
```

---

## Technical Details

- **Resolution**: 640x320 logical pixels, scaled up with letterboxing
- **Physics**: Gravity at 500 units/sec², velocity-based movement with acceleration/deceleration
- **Bullet pooling**: Up to 8 pooled bullet objects reused to avoid allocations
- **Rendering layers**: Background → background tiles → player/enemies → bullets → foreground tiles
- **Audio**: SDL3_mixer with 8 polyphonic sound channels + 1 music track
- **Camera**: Follows player horizontally, centered on the viewport

---

## Credits

Background music: *Juhani Junkala - Retro Game Music Pack, Level 1*
