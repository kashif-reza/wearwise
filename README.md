# WearWise — Offline Smart Fashion & Wardrobe Assistant

WearWise is a C++17 console application for managing a personal wardrobe, exploring outfit combinations, planning outfits, tracking outfit history, and monitoring clothing expenses. This repository remains a **console-based C++ project**; it is not a website.

## Refactored source structure

- `main.cpp` — application entry point
- `UserProfile.h` — user profile data structure
- `ClothingItem.h` — clothing, color-rule, and planner data structures
- `StringUtils.h/.cpp` — shared string helpers
- `ProfileManager.cpp` — profile setup, persistence, and display
- `WardrobeManager.cpp` — wardrobe inventory and laundry status
- `OutfitRecommendation.cpp` — recommendation scoring and outfit suggestions
- `OutfitPlanner.cpp` — outfit scheduling
- `BudgetManager.cpp` — budget and purchase tracking
- `HistoryManager.cpp` — outfit usage history
- `ColorHarmony.cpp` — color compatibility and palette explorer
- `AIPromptGenerator.cpp` — AI virtual try-on prompt generation
- `WearWiseSystem.h/.cpp` — system coordinator, file initialization, and main menu

## Features

- Men’s, women’s, kids’, and unisex catalogue entries
- Upper wear, lower wear, footwear, outerwear, and accessories (for example watches, belts, bags, and sunglasses)
- Wardrobe inventory and clean/laundry availability flag
- Ideal outfit recommendations and recommendations from owned, ready items
- Occasion and season selection
- Profile and body measurement storage
- Outfit planner and persistent outfit history
- Monthly budget and expense total
- Color harmony rules
- AI try-on prompt generation (prompt text only; does not generate images)
- TXT-based local persistence

## Build

### Using g++

From the project directory:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic *.cpp -o wearwise
```

Run:

```bash
./wearwise
```

On Windows (MinGW):

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic *.cpp -o wearwise.exe
.\wearwise.exe
```

### Using CMake

```bash
cmake -S . -B build
cmake --build build
```

## TXT data files

On first launch, WearWise creates the following data files in the **current working directory**:

- `users.txt` — saved profile
- `clothing.txt` — catalogue and owned items
- `colors.txt` — color compatibility rules
- `budget.txt` — monthly budget and accumulated expenditure
- `history.txt` — worn outfit records
- `planner.txt` — scheduled outfits

The program includes menu actions for adding wardrobe items and recording outfit history; you do not need to manually edit the TXT files for these actions. Keep a backup before editing any TXT file directly. Records use pipe (`|`) separators, so avoid entering the pipe character inside values.

## Important notes

- The budget uses a configurable currency symbol currently displayed as `$`; it is not automatically converted to BDT or another currency.
- The outfit scoring system is a heuristic and does not guarantee professional styling or exact garment sizing.
- This is an offline, single-user console application.
