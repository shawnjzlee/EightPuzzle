#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <string>

#include "eight_puzzle.h"

EightPuzzle::EightPuzzle() { }

EightPuzzle::~EightPuzzle() { }

void EightPuzzle::uniform_cost(int puzzle_option) {
    return;
}

void EightPuzzle::misplaced_tile_astar(int puzzle_option) {
    return;
}

void EightPuzzle::manhattan_dist_astar(int puzzle_option) {
    return;
}

void EightPuzzle::setup_puzzle_grid() {
    std::cout << "Enter your puzzle, use a zero to represent the blank."
              << " Press 'Enter' when complete\n";
    // to be implemented
}

void EightPuzzle::print_puzzle_grid() {
    for(const auto &i : puzzle_grid) std::cout << i << " ";
    std::cout << std::endl;
}