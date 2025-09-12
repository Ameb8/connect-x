//
// Created by Patty Crowder on 9/11/25.
//

#ifndef CONNECT_X_COLORS_H
#define CONNECT_X_COLORS_H

#include <string>
#include <vector>
#include <sstream>

constexpr const char* BASE = "\033[";
constexpr const char* RESET = "\033[0m";

enum class Color {
    Default = 39,
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,

    BrightBlack = 90,
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93,
    BrightBlue = 94,
    BrightMagenta = 95,
    BrightCyan = 96,
    BrightWhite = 97,
};

enum class Background {
    Default = 49,
    Black = 40,
    Red = 41,
    Green = 42,
    Yellow = 43,
    Blue = 44,
    Magenta = 45,
    Cyan = 46,
    White = 47,

    BrightBlack = 100,
    BrightRed = 101,
    BrightGreen = 102,
    BrightYellow = 103,
    BrightBlue = 104,
    BrightMagenta = 105,
    BrightCyan = 106,
    BrightWhite = 107,
};

enum class Style {
    Bold = 1,
    Dim = 2,
    Italic = 3,
    Underline = 4,
    Blink = 5,
    Inverse = 7,
    Hidden = 8,
    Strikethrough = 9
};

inline std::string colorize(const std::string& text, Color color) {
    return std::string(BASE) + std::to_string(static_cast<int>(color)) + "m" + text + RESET;
}

inline std::string stylize(const std::string& text, Style style) {
    return std::string(BASE) + std::to_string(static_cast<int>(style)) + "m" + text + RESET;
}

#endif //CONNECT_X_COLORS_H