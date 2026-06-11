# 🐾 Tamagotchi Aero

A beautiful Frutiger Aero-themed Tamagotchi TUI application built with FTXUI.

## 🎨 Features

### Design
- **Frutiger Aero Aesthetic** — Sky blue gradients, glossy highlights, and vibrant accent colors
- **Responsive Layout** — Dynamic terminal UI that adapts to your screen
- **Color-Coded Stats** — Intuitive color palette (orange = fullness, cyan = happiness, green = energy, blue = health)

### Gameplay
- **Pet Management** — Feed, play, sleep, and heal your Tamagotchi
- **Realistic Aging** — Your pet ages each day with natural stat decay
- **Random Events** — Surprises like finding fruit, getting sick, or making friends
- **Activity Log** — Track every action with timestamps
- **Permadeath** — Keep your pet alive or face the consequences

## ⚙️ Build

### Requirements
- C++17 or later
- CMake 3.11+
- GCC, Clang, or MSVC

### Steps

```bash
mkdir build
cd build
cmake ..
cmake --build .
./tamagotchi_tui
```

## ⌨️ Controls

| Key | Action |
|-----|--------|
| **f** | Feed your pet 🍽️ |
| **p** | Play with your pet 🎮 |
| **s** | Let your pet sleep 😴 |
| **h** | Give medicine 💊 |
| **t** | Pass time (age) ⏰ |
| **e** | Trigger random event 🎲 |
| **q** | Quit the game 🚪 |

## 📊 Stats

- **Fullness** — Decreases over time; feed your pet to increase (inverted hunger)
- **Happiness** — Increases when playing; decreases naturally
- **Energy** — Consumed by playing; restored by sleeping
- **Health** — Damaged by starvation or sadness; restored by sleeping or medicine

## 🎯 Gameplay Tips

1. **Balance is key** — Don't neglect any stat for too long
2. **Sleep regularly** — Restores energy, hunger, and health simultaneously
3. **Play strategically** — Costs energy but boosts happiness and longevity
4. **Watch for events** — Random events can help or hurt your pet
5. **Keep logs** — Check the activity log to understand what happened

## 🛠️ Architecture

### Tech Stack
- **FTXUI** — Fast TUI framework for terminal rendering
- **C++17** — Modern C++ for clean, efficient code
- **CMake** — Cross-platform build system

### Code Structure

```
tamagotchi_tui.cpp
├── Structs (Tamagotchi, StatusLog)
├── Utilities (clamp, currentTime, addLog)
├── Frutiger Aero Color Palette
├── UI Components (statusBar, tamagotchiDisplay, etc.)
├── Tamagotchi Engine (feedPet, playWithPet, ageTick, etc.)
├── TamagotchiApp Class (main render logic)
└── main() (event loop)
```

## 📝 License

MIT License — Feel free to use and modify!

## 🎨 Color Palette

Frutiger Aero Classic:
- Light Blue: RGB(173, 216, 230)
- Sky Blue: RGB(135, 206, 250)
- Steel Blue: RGB(70, 130, 180)
- Warm Orange: RGB(255, 165, 0)
- Light Green: RGB(144, 238, 144)
- Dark Turquoise: RGB(0, 206, 209)

---

**Enjoy your digital pet! 🐾**
