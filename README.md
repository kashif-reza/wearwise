# WearWise — Offline Smart Fashion & Wardrobe Assistant

WearWise is a C++17 console application for managing a personal wardrobe, exploring outfit combinations, planning outfits, and learning how to care for clothing. It uses local TXT files and does not require a database or internet connection.

## Features

1. **What Should I Wear Today?**
   - Random Style Inspiration for situation-based outfit ideas.
   - My Wardrobe Recommendation uses only owned and clean/ready clothes.
   - Style & Outfit Planner lets users schedule outfits for upcoming dates.
2. **Explore Color Harmonies** — browse complementary colour combinations.
3. **My Wardrobe & Outfit History** — manage owned clothes, laundry status, and worn-outfit records.
4. **Smart Travel Packing Planner** — create trip-specific packing checklists using owned wardrobe items, add essential travel items, and mark each item as packed.
5. **My Favorites & Purchase Wishlist**
   - Save favorite items already owned.
   - Track planned purchases with category, preferred colour, estimated price, and priority.
   - See the estimated total cost of pending wishlist items.
   - Mark an item as purchased to add it to My Wardrobe automatically.
6. **My Profile** — save personal style preferences and measurements locally.
7. **AI Virtual Try-On Prompt Generator** — create a text prompt for an external image tool; WearWise does not generate images.
8. **Clothing Care Assistant** — fabric care, stain-removal suggestions, and everyday maintenance tips.
9. **Wardrobe Insights** — review logged clothing usage and wardrobe patterns.

## Project structure

- `main.cpp` — application entry point
- `WearWiseSystem.h/.cpp` — system coordinator, data initialization, and main menu
- `UserProfile.h` — profile data structure
- `ClothingItem.h` — clothing, colour-rule, and planner data structures
- `StringUtils.h/.cpp` — shared string helpers
- `ProfileManager.cpp` — profile setup and persistence
- `WardrobeManager.cpp` — wardrobe inventory and laundry status
- `OutfitRecommendation.cpp` — daily style inspiration and wardrobe recommendations
- `OutfitPlanner.cpp` — outfit scheduling inside the What Should I Wear Today? style hub
- `BudgetManager.cpp` — optional purchase-awareness helper
- `HistoryManager.cpp` — outfit history and wardrobe usage insights
- `ColorHarmony.cpp` — colour compatibility explorer
- `AIPromptGenerator.cpp` — AI try-on prompt generation
- `ClothingCareAssistant.cpp` — fabric, stain, and maintenance guidance
- `TravelPacking.cpp` — travel plans and saved packing checklists
- `FavoritesWishlist.cpp` — favorite wardrobe items and purchase wishlist

## Build and run

### CMake (recommended)

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

On Windows with MinGW, run:

```powershell
.\\build\\wearwise.exe
```

The exact executable path can vary by generator. If needed, search the `build` folder for `wearwise.exe`.

### Compile directly with g++

From the project root:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic *.cpp -o wearwise.exe
.\\wearwise.exe
```

## TXT files and sample data

WearWise uses simple pipe-separated TXT files in the current working directory:

- `users.txt` — saved user profile
- `clothing.txt` — wardrobe and catalogue records
- `clothing_seed.txt` — additional sample clothing catalogue entries
- `colors.txt` — colour compatibility rules
- `budget.txt` — optional budget and expenditure values
- `history.txt` — outfit usage records
- `planner.txt` — scheduled outfits
- `fabric_care.txt` — fabric-specific care instructions
- `stain_guide.txt` — common stain treatment suggestions
- `maintenance_tips.txt` — everyday clothing-care tips
- `travel_packing.txt` — saved trips and packed-item status (created when first used)
- `favorites.txt` — IDs of favorite owned garments (created when first used)
- `wishlist.txt` — planned purchases and purchase status (created when first used)

On startup, WearWise creates its original working files when they are missing. It also appends new sample catalogue entries from `clothing_seed.txt` only when their IDs are not already present. Existing ownership and laundry statuses are preserved; the seed file does not overwrite your personal wardrobe records.

Keep these TXT files in the project folder and run WearWise with the project root as the current working directory. Back them up before editing manually. The pipe character (`|`) is used as a field separator, so do not enter it inside a field.

## Notes

- The clothing catalogue is sample data. Edit your wardrobe through the application to mark items as owned or in laundry.
- Style recommendations are rule-based suggestions, not professional tailoring or guaranteed size advice.
- Follow the care label on each garment first. Stain treatments should be tested on a hidden area, especially for delicate or valuable fabrics.
- WearWise is a local, single-user console application.
