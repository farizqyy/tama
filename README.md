# 🐾 Tamagotchi Aero

A beautiful Frutiger Aero-themed Tamagotchi TUI application built with FTXUI.

## 🎨 Features

### Design
- **Frutiger Aero Aesthetic** — Sky blue gradients, glossy highlights, and vibrant accent colors
- **Improved Color Contrast** — Carefully chosen colors for readability against light backgrounds
- **Responsive Layout** — Dynamic terminal UI that adapts to your screen
- **Color-Coded Stats** — Intuitive palette (orange = fullness, cyan = happiness, green = energy, blue = health)

### Gameplay
- **Pet Management** — Feed, play, sleep, and heal your Tamagotchi
- **Realistic Aging** — Your pet ages each day with natural stat decay
- **Merged Time+Event** — Age and random events occur in a single action
- **Persistent Save/Load** — Save your pet and continue later!
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

All actions are mapped to numeric keys **1–8**:

| Key | Action |
|-----|--------|
| **1** | Feed your pet 🍽️ |
| **2** | Play with your pet 🎮 |
| **3** | Let your pet sleep 😴 |
| **4** | Give medicine 💊 |
| **5** | Pass time + random event 📅 |
| **6** | Save game 💾 |
| **7** | Load game 📂 |
| **8** | Quit ❌ |

**Bonus:** Press **q** to quit anytime.

## 📊 Stats

- **Fullness** — Decreases over time; feed your pet to increase (inverted hunger)
- **Happiness** — Increases when playing; decreases naturally
- **Energy** — Consumed by playing; restored by sleeping
- **Health** — Damaged by starvation or sadness; restored by sleeping or medicine

## 💾 Save/Load System

Your pet is automatically saved when you press **6** to `tama_save.txt`. When you restart, press **7** to load your previous save.

**Save file includes:**
- Pet name, stats, and age
- Current alive/dead status
- Complete activity log (last 50 actions)

## 🎮 Gameplay Tips

1. **Balance is key** — Don't neglect any stat for too long
2. **Sleep regularly** — Restores energy, hunger, and health simultaneously
3. **Play strategically** — Costs energy but boosts happiness and longevity
4. **Random events** — Merged with time progression; watch your log!
5. **Save often** — Use key **6** to preserve your pet's progress

## 🎨 Improved Color Scheme

The new color palette provides:
- **Better contrast** against light backgrounds
- **Reduced eye strain** for long gaming sessions
- **Clearer differentiation** between UI elements
- **Vibrant accents** while maintaining aero aesthetics

**Primary colors:**
- Background: Light blue gradient RGB(230, 240, 250)
- Primary dark: Steel blue RGB(41, 128, 185)
- Primary light: Bright sky blue RGB(52, 152, 219)

**Accents:**
- Orange: RGB(230, 126, 34) — Fullness
- Green: RGB(39, 174, 96) — Happiness & alive status
- Cyan: RGB(26, 188, 156) — Energy
- Red: RGB(231, 76, 60) — Death indicator

## 🏗️ Architecture

### Tech Stack
- **FTXUI** — Fast TUI framework for terminal rendering
- **C++17** — Modern C++ for clean, efficient code
- **CMake** — Cross-platform build system

### New Features
- **Merged Time+Event** — Single action combining aging and random events
- **Save/Load** — Binary-free file format for portability
- **Numeric Keybinds** — Simplified 1-8 control scheme
- **Status Messages** — In-game feedback for save/load operations

## 📝 License

MIT License — Feel free to use and modify!

---

**Enjoy your digital pet! 🐾**
