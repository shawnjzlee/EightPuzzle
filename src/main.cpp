#include <iostream>
#include "global.h"
#include "eight_puzzle.h"

EightPuzzle puzzle;

void algorithm_choice(int puzzle_option) { 
    int option = 0;
    std::cout << "Enter your choice of algorithm:\n" 
              << "\t 1.\t Uniform Cost Search\n"
              << "\t 2.\t A* with Misplaced Tile heuristic\n"
              << "\t 3.\t A* with Manhattan distance heuristic\n";
    std::cin >> option;
    
    switch(option) {
        case 1: puzzle.uniform_cost(puzzle_option); break;
        case 2: puzzle.misplaced_tile_astar(puzzle_option); break;
        case 3: puzzle.manhattan_dist_astar(puzzle_option); break;
        default: std::cout << "Please re-enter an option\n"; algorithm_choice(puzzle_option);
    }
}

void menu(void) {
    int option = 0;
    std::cout <<  "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle.\n";
    std::cin >> option;
    
    switch(option) {
        case 1: algorithm_choice(option); break;
        case 2: puzzle.setup_puzzle_grid(); algorithm_choice(option); break;
        default: std::cout << "Please re-enter an option\n"; menu();
    }
}

int main(int argc, char * argv[]) {
    menu();
    return 0;
}