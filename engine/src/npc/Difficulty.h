//
// Created by Patty Crowder on 9/9/25.
//

#ifndef CONNECT_X_DIFFICULTY_H
#define CONNECT_X_DIFFICULTY_H
#include <functional>
#include <vector>


struct Difficulty {
    std::vector<int> evalLength; // Base score based on length of segment
    std::function<int(int)> evalFromCenter; // Multiplier based on distance form center of board
    std::function<int(int)> evalMaxLen; // Function to calculate multiplier based on the max distance segment can be
};

extern const Difficulty EasyDifficulty;
extern const Difficulty MediumDifficulty;
extern const Difficulty HardDifficulty;

#endif //CONNECT_X_DIFFICULTY_H