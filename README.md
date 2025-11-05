# Test RPG Console

Advanced C++ console RPG with rich visual rendering and object-oriented architecture.

## Features

- **Advanced OOP Design**: Polymorphic entity system with inheritance hierarchy
- **Rich Console UI**: ANSI color support, animated text, bordered panels
- **Combat System**: Turn-based tactical combat with multiple enemy types
- **Inventory Management**: Equipment system with weapons and consumables
- **Progression System**: Level-up mechanics with stat increases
- **Modular Architecture**: Clean separation of concerns (entities, systems, UI)

## Architecture

```
src/
├── core/          # Game engine and configuration
├── entities/      # Polymorphic entity classes (Entity → Character/Enemy)
├── systems/       # Game systems (Combat, Inventory, Progression)
├── ui/            # Console rendering and input handling
└── utils/         # Utilities (Random, Colors)
```

## Build

```bash
mkdir build && cd build
cmake ..
make
./bin/TestRPGConsole
```

## Requirements

- C++17 compatible compiler
- CMake 3.15+
- Unix/Linux (ANSI color support)

## Gameplay

- Explore dungeons and fight enemies
- Collect weapons and potions
- Level up your character
- Strategic turn-based combat

## Technical Highlights

- Abstract base classes with pure virtual methods
- Dynamic polymorphism with virtual dispatch
- RAII principles and smart pointers
- STL containers and algorithms
- Modern C++17 features
