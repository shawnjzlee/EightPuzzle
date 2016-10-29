#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <string>
#include <cmath>

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
              << " Separate values with a space. Press 'Enter' when complete\n";
    std::string s, value;
    
    if(std::cin.peek() == '\n')
        std::cin.ignore();
    std::getline(std::cin, s);
    std::stringstream ss(s);
    while(getline(ss, value, ' ')) {
        try {
            puzzle_grid.push_back(stoi(value));
        }
        catch (const std::exception &e) {
            std::cout << "Too many spaces, please re-enter the values\n";
            setup_puzzle_grid();
        } 
    }

    int num_zeros = 0;
    for_each(puzzle_grid.begin(), puzzle_grid.end(), 
            [&num_zeros, this](int &i) {
                if(i == 0) num_zeros++;
                if(num_zeros > 1) {
                    std::cout << "Please enter only one zero\n";
                    setup_puzzle_grid();
                }
                if(i > 9) {
                    std::cout << "Please enter single digit values\n";
                    setup_puzzle_grid();
                }
            });
            
    if(num_zeros == 0) {
        std::cout << "Please enter one zero\n";
        setup_puzzle_grid();
    }
    
    std::cout << puzzle_grid.size() << std::endl;
    double d_sqrt = std::sqrt(puzzle_grid.size());
    int i_sqrt = d_sqrt;
    if (d_sqrt != i_sqrt) {
        std::cout << "Not a NxN grid, please enter a perfect square set of numbers\n";
        setup_puzzle_grid();
    }
}

void EightPuzzle::print_puzzle_grid() {
    for(const auto &i : puzzle_grid) std::cout << i << " ";
    std::cout << std::endl;
}