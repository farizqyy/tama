#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <sstream>

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp"

using namespace ftxui;

// ═══════════════════════════════════════════════════════════════
// STRUCTS
// ═══════════════════════════════════════════════════════════════

struct StatusLog {
    std::string timestamp;
    std::string action;
    std::string detail;
};

struct Tamagotchi {
    std::string name;
    int hunger     = 50;
    int happiness  = 70;
    int energy     = 80;
    int health     = 100;
    int age        = 0;
    bool alive     = true;
    std::vector<StatusLog> logs;
};

// ═══════════════════════════════════════════════════════════════
// UTILITIES
// ═══════════════════════════════════════════════════════════════

template<typename T>
inline T clamp(T value, T minVal, T maxVal) {
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}

std::string currentTime() {
    std::time_t t = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%H:%M:%S", std::localtime(&t));
    return std::string(buf);
}

void addLog(Tamagotchi& t, const std::string& action, const std::string& detail) {
    StatusLog log;
    log.timestamp = currentTime();
    log.action = action;
    log.detail = detail;
    t.logs.push_back(log);
    if (t.logs.size() > 50) {
        t.logs.erase(t.logs.begin());
    }
}

// ═══════════════════════════════════════════════════════════════
// FRUTIGER AERO COLORS
// ═══════════════════════════════════════════════════════════════

// Sky blue gradient (aero signature)
Color aero_light_blue = Color::RGB(173, 216, 230);   // Light blue
Color aero_sky = Color::RGB(135, 206, 250);          // Sky blue
Color aero_deep_blue = Color::RGB(70, 130, 180);     // Steel blue

// Highlight colors (glossy effect)
Color aero_white = Color::RGB(255, 255, 255);
Color aero_light_gray = Color::RGB(240, 240, 240);
Color aero_medium_gray = Color::RGB(192, 192, 192);
Color aero_dark_gray = Color::RGB(64, 64, 64);

// Accent colors (vibrant aero palette)
Color aero_orange = Color::RGB(255, 165, 0);         // Warm orange
Color aero_green = Color::RGB(144, 238, 144);        // Light green
Color aero_cyan = Color::RGB(0, 206, 209);           // Dark turquoise

// ═══════════════════════════════════════════════════════════════
// UI COMPONENTS
// ═══════════════════════════════════════════════════════════════

Element aeroGradientBox(const std::string& title, Element content) {
    return window(
        text(title) | bold | color(aero_dark_gray),
        content | color(aero_dark_gray)
    ) | border | bgcolor(aero_light_gray);
}

Element statusBar(const std::string& label, int value, Color barColor) {
    int width = 20;
    int filled = (value * width) / 100;
    
    std::string bar = "[";
    for (int i = 0; i < width; i++) {
        bar += (i < filled) ? "█" : "░";
    }
    bar += "]";
    
    std::stringstream ss;
    ss << std::setw(3) << value << "%";
    
    return hbox({
        text(label) | size(WIDTH, EQUAL, 12),
        text(bar) | color(barColor),
        text(ss.str()) | color(aero_dark_gray)
    });
}

Element tamagotchiDisplay(const Tamagotchi& pet) {
    std::vector<Element> stats;
    
    // Title with age
    stats.push_back(
        hbox({
            text("🐾 " + pet.name) | bold | color(aero_deep_blue),
            text(" | Day " + std::to_string(pet.age)) | color(aero_dark_gray)
        }) | center
    );
    
    stats.push_back(separator());
    
    // Status indicator
    std::string status = pet.alive ? "✓ ALIVE" : "✗ DECEASED";
    Color statusColor = pet.alive ? aero_green : Color::Red;
    stats.push_back(
        text(status) | color(statusColor) | bold | center
    );
    
    stats.push_back(text(""));  // Spacing
    
    // Stats bars
    stats.push_back(text("═══════════════════════") | center);
    stats.push_back(statusBar("Fullness ", 100 - pet.hunger, aero_orange));
    stats.push_back(statusBar("Happiness", pet.happiness, aero_cyan));
    stats.push_back(statusBar("Energy   ", pet.energy, aero_green));
    stats.push_back(statusBar("Health   ", pet.health, aero_sky));
    stats.push_back(text("═══════════════════════") | center);
    
    return vbox(stats);
}

Element actionButton(const std::string& label) {
    return text(" " + label + " ") | border | center | bold;
}

// ═══════════════════════════════════════════════════════════════
// TAMAGOTCHI ENGINE
// ═══════════════════════════════════════════════════════════════

void feedPet(Tamagotchi& t) {
    t.hunger = clamp(t.hunger - 30, 0, 100);
    t.happiness = clamp(t.happiness + 10, 0, 100);
    t.energy = clamp(t.energy + 5, 0, 100);
    addLog(t, "FEED", "Nom nom! 😋");
}

void playWithPet(Tamagotchi& t) {
    if (t.energy < 20) {
        addLog(t, "PLAY", "Too tired... 😴");
        return;
    }
    t.happiness = clamp(t.happiness + 25, 0, 100);
    t.energy = clamp(t.energy - 20, 0, 100);
    t.hunger = clamp(t.hunger + 15, 0, 100);
    addLog(t, "PLAY", "Wheee! 🎮");
}

void sleepPet(Tamagotchi& t) {
    t.energy = clamp(t.energy + 40, 0, 100);
    t.hunger = clamp(t.hunger + 10, 0, 100);
    t.health = clamp(t.health + 5, 0, 100);
    addLog(t, "SLEEP", "Zzzzz... 😴");
}

void healPet(Tamagotchi& t) {
    t.health = clamp(t.health + 30, 0, 100);
    t.energy = clamp(t.energy + 10, 0, 100);
    addLog(t, "HEAL", "Feeling better! 💊");
}

void ageTick(Tamagotchi& t) {
    t.age++;
    t.hunger = clamp(t.hunger + 10, 0, 100);
    t.happiness = clamp(t.happiness - 5, 0, 100);
    t.energy = clamp(t.energy - 8, 0, 100);
    
    if (t.hunger >= 80) t.health = clamp(t.health - 15, 0, 100);
    if (t.happiness <= 20) t.health = clamp(t.health - 5, 0, 100);
    
    if (t.hunger >= 100 || t.health <= 0) {
        t.alive = false;
        addLog(t, "DIED", "Rest in peace... 💀");
    } else {
        addLog(t, "TIME", "Day " + std::to_string(t.age));
    }
}

void randomEvent(Tamagotchi& t) {
    const char* events[] = {
        "Found fruit! 🍎",
        "Sunny day! ☀️",
        "Caught a cold 🤧",
        "Made a friend! 👫",
        "Lost in thought... 💭"
    };
    
    int idx = std::rand() % 5;
    t.hunger = clamp(t.hunger + (std::rand() % 20 - 10), 0, 100);
    t.happiness = clamp(t.happiness + (std::rand() % 20 - 10), 0, 100);
    t.health = clamp(t.health + (std::rand() % 20 - 10), 0, 100);
    
    addLog(t, "EVENT", events[idx]);
}

// ═══════════════════════════════════════════════════════════════
// MAIN UI COMPONENT
// ═══════════════════════════════════════════════════════════════

class TamagotchiApp {
public:
    Tamagotchi pet;
    int selected_tab = 0;
    int log_scroll = 0;
    
    TamagotchiApp(const std::string& name) : pet() {
        pet.name = name;
        pet.hunger = 50;
        pet.happiness = 70;
        pet.energy = 80;
        pet.health = 100;
        pet.age = 0;
        pet.alive = true;
        addLog(pet, "BORN", "Welcome to the world!");
    }
    
    Element renderHeader() {
        return vbox({
            text(" ╔═══════════════════════════════════════╗ ") | color(aero_deep_blue),
            text(" ║     🐾 TAMAGOTCHI AERO 🐾           ║ ") | color(aero_deep_blue),
            text(" ╚═══════════════════════════════════════╝ ") | color(aero_deep_blue),
        });
    }
    
    Element renderStatus() {
        return aeroGradientBox("PET STATUS", tamagotchiDisplay(pet));
    }
    
    Element renderActions() {
        return vbox({
            text(" ACTIONS ") | bold | color(aero_deep_blue),
            hbox({
                actionButton("🍽️  FEED") | flex,
                text(" "),
                actionButton("🎮 PLAY") | flex,
            }),
            text(""),
            hbox({
                actionButton("😴 SLEEP") | flex,
                text(" "),
                actionButton("💊 HEAL") | flex,
            }),
            text(""),
            hbox({
                actionButton("⏰ TIME") | flex,
                text(" "),
                actionButton("🎲 EVENT") | flex,
            }),
        }) | border | bgcolor(aero_light_gray);
    }
    
    Element renderLogs() {
        std::vector<Element> log_elements;
        
        log_elements.push_back(
            text(" ACTIVITY LOG ") | bold | color(aero_deep_blue)
        );
        
        int start = std::max(0, (int)pet.logs.size() - 10);
        
        for (int i = start; i < (int)pet.logs.size(); i++) {
            const auto& log = pet.logs[i];
            std::string log_line = "[" + log.timestamp + "] " + 
                                  log.action + ": " + log.detail;
            log_elements.push_back(
                text(log_line) | color(aero_dark_gray)
            );
        }
        
        return vbox(log_elements) | border | bgcolor(aero_light_gray) | flex;
    }
    
    Element render() {
        return vbox({
            renderHeader(),
            text(""),
            hbox({
                renderStatus() | flex,
                text(" "),
                renderActions() | flex,
            }) | flex,
            text(""),
            renderLogs() | flex,
        }) | bgcolor(aero_light_blue);
    }
};

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    auto screen = ScreenInteractive::TerminalOutput();
    
    TamagotchiApp app("Tama");
    
    auto component = Container::Vertical({});
    
    std::function<void()> quit = screen.ExitLoopClosure();
    
    // Render loop with input handling
    auto renderer = Renderer([&] {
        return app.render();
    });
    
    // Simple button handlers
    auto handle_input = [&](Event event) {
        if (event == Event::Character('q')) {
            quit();
        } else if (event == Event::Character('f')) {
            if (app.pet.alive) feedPet(app.pet);
        } else if (event == Event::Character('p')) {
            if (app.pet.alive) playWithPet(app.pet);
        } else if (event == Event::Character('s')) {
            if (app.pet.alive) sleepPet(app.pet);
        } else if (event == Event::Character('h')) {
            if (app.pet.alive) healPet(app.pet);
        } else if (event == Event::Character('t')) {
            if (app.pet.alive) ageTick(app.pet);
        } else if (event == Event::Character('e')) {
            if (app.pet.alive) randomEvent(app.pet);
        }
        return false;
    };
    
    auto component_with_input = CatchEvent(renderer, handle_input);
    
    screen.Loop(component_with_input);
    
    return 0;
}
