#include "Difficulty.h"
#include <cmath>

// Bias towards center of board
int centerBiasEasy(int distanceFromCenter) {
    return 1; // No bias
}
int centerBiasMedium(int distanceFromCenter) {
    return std::max(1, 4 - distanceFromCenter); // Slight center preference
}
int centerBiasHard(int distanceFromCenter) {
    return std::max(1, 7 - distanceFromCenter); // Stronger preference for center
}


// Max segment multiplier
int maxLenMultiplierEasy(int remainingSpaces) {
    return 1;
}
int maxLenMultiplierMedium(int remainingSpaces) {
    return 1 + remainingSpaces / 4;
}
int maxLenMultiplierHard(int remainingSpaces) {
    return 1 + remainingSpaces;
}


// Tokens in segment
const std::vector<int> easyEval =    {0, 1, 5, 10, 100};
const std::vector<int> mediumEval =  {0, 2, 10, 50, 1000};
const std::vector<int> hardEval =    {0, 5, 20, 100, 10000};


// Difficulty instances
const Difficulty EasyDifficulty = {
    easyEval,
    centerBiasEasy,
    maxLenMultiplierEasy
};
const Difficulty MediumDifficulty = {
    mediumEval,
    centerBiasMedium,
    maxLenMultiplierMedium
};
const Difficulty HardDifficulty = {
    hardEval,
    centerBiasHard,
    maxLenMultiplierHard
};


