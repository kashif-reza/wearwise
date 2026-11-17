cmake_minimum_required(VERSION 3.16)
project(WearWise LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(wearwise
    main.cpp
    StringUtils.cpp
    WearWiseSystem.cpp
    ProfileManager.cpp
    WardrobeManager.cpp
    OutfitRecommendation.cpp
    OutfitPlanner.cpp
    BudgetManager.cpp
    HistoryManager.cpp
    ColorHarmony.cpp
    AIPromptGenerator.cpp
    ClothingCareAssistant.cpp
)
