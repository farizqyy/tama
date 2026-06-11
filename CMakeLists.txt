cmake_minimum_required(VERSION 3.11)
project(tamagotchi CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FetchContent for FTXUI
include(FetchContent)

# Fetch FTXUI
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
  GIT_TAG v5.0.0
)

FetchContent_MakeAvailable(ftxui)

# Create executable
add_executable(tamagotchi_tui
  tamagotchi_tui.cpp
)

# Link FTXUI
target_link_libraries(tamagotchi_tui PRIVATE ftxui::screen ftxui::dom ftxui::component)

# Enable optimizations
if(MSVC)
  target_compile_options(tamagotchi_tui PRIVATE /W4)
else()
  target_compile_options(tamagotchi_tui PRIVATE -Wall -Wextra -Wpedantic)
endif()
