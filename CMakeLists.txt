cmake_minimum_required(VERSION 3.16)
project(WearWise LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(wearwise
    src/main.cpp
    src/StringUtils.cpp
    src/WearWiseSystem.cpp
    src/ProfileManager.cpp
    src/WardrobeManager.cpp
    src/OutfitRecommendation.cpp
    src/OutfitPlanner.cpp
    src/HistoryManager.cpp
    src/ColorHarmony.cpp
    src/ClothingCareAssistant.cpp
    src/TravelPacking.cpp
    src/FavoritesWishlist.cpp
    src/AIPromptGenerator.cpp
    src/WardrobeInsights.cpp
    src/SizeAdvisor.cpp
)

target_include_directories(wearwise PRIVATE include)

# Keep file-based user data and resources relative to the repository root.
set_property(TARGET wearwise PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
