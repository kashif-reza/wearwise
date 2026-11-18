# WearWise
### Offline Smart Wardrobe & Travel Assistant

WearWise is a C++17 terminal application that helps users choose outfits, manage clothes, prepare for trips, and keep a practical purchase wishlist. It works offline and stores personal records in TXT files (no database).

## 1. Terminal home screen

The main menu is intentionally ordered by everyday importance:

```text
======================================================================
                              WEARWISE
              Offline Smart Wardrobe & Travel Assistant
======================================================================
 Active User: <name> [<group>]
 Situation:   <occasion> | Weather: <season>
======================================================================
  [1] What Should I Wear Today? (Ideas, Closet Match & Outfit Planner)
  [2] My Wardrobe & Outfit History
  [3] Smart Travel Packing Planner
  [4] My Favorites & Purchase Wishlist
  [5] Clothing Care Assistant
  [6] Explore Color Harmonies
  [7] My Profile & Preferences
  [8] AI Virtual Try-On Prompt Generator
  [9] My Wardrobe Insights
  [10] Personal Clothing Size Advisor (Measurements -> Sizes)
  [11] Outfit Rating & Style Feedback (Score 1-10)
  [0] Exit Application
======================================================================
Enter option (0-11):
```

## 2. Feature guide (same order as the terminal)

### [1] What Should I Wear Today?
- **[1] Random Style Inspiration** — get outfit ideas based on occasion, weather, mood, and style.
- **[2] My Wardrobe Recommendation** — get combinations from clothes marked owned and clean/ready.
- **[3] Style & Outfit Planner** — schedule or remove an outfit for a future date.

### [2] My Wardrobe & Outfit History
- View the wardrobe.
- Add a clothing item.
- Toggle an item's clean/laundry status.
- Open Outfit Usage History and log what was worn.

### [3] Smart Travel Packing Planner
- Create a trip with destination, date, duration, trip type, expected weather, and planned activities.
- Generate a starter checklist using owned clothes plus useful essentials.
- View a trip checklist and mark items packed.

### [4] My Favorites & Purchase Wishlist
- Save or remove favorite items already in the wardrobe.
- Add planned purchases with category, preferred colour, expected price, and priority.
- Review pending wishlist cost.
- Mark an item purchased; it is added to the wardrobe.

### [5] Clothing Care Assistant
- Fabric care guide.
- Stain removal guide.
- Everyday clothing maintenance tips.

### [6] Explore Color Harmonies
- Browse the colour compatibility reference table.

### [7] My Profile & Preferences
- View the profile and personal style/measurement preferences.

### [8] AI Virtual Try-On Prompt Generator
- Build a detailed external image-generation / virtual try-on prompt from garment descriptions, profile measurements, fit preferences, accessories, setting, and camera direction.
- WearWise generates prompt text; an external image tool performs the image generation or try-on.

### [9] My Wardrobe Insights
- Summarize owned, ready-to-wear, and laundry items.
- Show category and colour breakdowns.
- Provide suggestions based on missing wardrobe categories and laundry status.

### [10] Personal Clothing Size Advisor
- Uses saved chest/bust, waist, hip and shoulder measurements to estimate shirt/top and trouser sizes.
- Asks for foot length to estimate an approximate EU shoe size; optionally accepts a trouser inseam.
- Checks suggested shirt and trouser sizes against matching garments in the catalogue.
- Results are generic starting estimates, not guaranteed brand-specific sizes; always compare the seller's measurement chart.

### [11] Outfit Rating & Style Feedback
- Enter your shirt/top, bottom, and shoe choices.
- Select the occasion and weather, then rate fit, comfort, occasion suitability, weather suitability, colour coordination, and shoe matching.
- Receive a weighted score from 1 to 10 with practical suggestions for lower-rated areas.

## 3. Project layout

```text
WearWise/
├── CMakeLists.txt
├── README.md
├── include/                 # Header files and data structures
│   ├── ClothingItem.h
│   ├── StringUtils.h
│   ├── UserProfile.h
│   └── WearWiseSystem.h
├── src/                     # C++ implementation files
│   ├── main.cpp
│   ├── WearWiseSystem.cpp
│   ├── ProfileManager.cpp
│   ├── WardrobeManager.cpp
│   ├── OutfitRecommendation.cpp
│   ├── OutfitPlanner.cpp
│   ├── HistoryManager.cpp
│   ├── ColorHarmony.cpp
│   ├── ClothingCareAssistant.cpp
│   ├── TravelPacking.cpp
│   ├── FavoritesWishlist.cpp
│   ├── AIPromptGenerator.cpp
│   ├── WardrobeInsights.cpp
│   ├── SizeAdvisor.cpp
│   ├── OutfitRating.cpp
│   └── StringUtils.cpp
├── resources/               # Read-only sample and reference text
│   ├── clothing_seed.txt
│   ├── fabric_care.txt
│   ├── stain_guide.txt
│   └── maintenance_tips.txt
└── [runtime TXT files]      # Created in the project root when needed
```

## 4. Build and run

Run commands from the WearWise project root so the TXT files stay in the expected location.

### CMake (recommended)

```bash
cmake -S . -B build
cmake --build build
```

Windows PowerShell:

```powershell
.\build\wearwise.exe
```

Linux/macOS:

```bash
./build/wearwise
```

### Direct compile with g++

Windows PowerShell:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/*.cpp -o wearwise.exe
.\wearwise.exe
```

## 5. Local TXT storage

Personal/runtime files stay in the project root so existing local data remains compatible:

- `users.txt` — user profile.
- `clothing.txt` — owned wardrobe and catalogue.
- `colors.txt` — colour compatibility rules (created on first run).
- `history.txt` — worn outfit history.
- `planner.txt` — scheduled outfits.
- `travel_packing.txt` — travel plans and packed-item status (created when used).
- `favorites.txt` — IDs of favorite wardrobe items (created when used).
- `wishlist.txt` — planned purchases and status (created when used).

Read-only sample/reference data lives in `resources/`. WearWise appends new seed catalogue entries only when their IDs are not already in the wardrobe file; existing ownership and laundry states are preserved.

Back up your TXT files before changing branches or manually editing records. The pipe character (`|`) is the field separator and should not be entered inside a value.

## 7. Notes

- Outfit suggestions are rule-based, not live AI recommendations.
- Travel packing quantities are starter estimates; users should adjust them for their trip.
- Follow each garment's care label first. Test stain treatments on a hidden area before use.
- WearWise is a local, single-user terminal application.
