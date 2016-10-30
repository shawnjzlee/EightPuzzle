#include <iostream>
#include "global.h"
#include "eight_puzzle.h"

void algorithm_choice(EightPuzzle puzzle) { 
    int option = 0;
    std::cout << "Enter your choice of algorithm:\n" 
              << "\t 1.\t Uniform Cost Search\n"
              << "\t 2.\t A* with Misplaced Tile heuristic\n"
              << "\t 3.\t A* with Manhattan distance heuristic\n";
    std::cin >> option;
    
    switch(option) {
        case 1: puzzle.uniform_cost(); break;
        case 2: puzzle.misplaced_tile_astar(); break;
        case 3: puzzle.manhattan_dist_astar(); break;
        default: std::cout << "Please re-enter an option\n"; algorithm_choice(puzzle);
    }
}

void menu(void) {
    int option = 0;
    std::cout <<  "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle.\n";
    std::cin >> option;
    
    EightPuzzle puzzle;
    
    if(option == 1) {
        std::vector<int> default_puzzle_grid = {1, 2, 3, 4, 0, 6, 7, 5, 8};
        puzzle.default_puzzle_init(default_puzzle_grid);
    }
    
    switch(option) {
        case 1: algorithm_choice(puzzle); break;
        case 2: puzzle.setup_puzzle_grid(); algorithm_choice(puzzle); break;
        default: std::cout << "Please re-enter an option\n"; menu();
    }
}

int main(int argc, char * argv[]) {
    menu();
    return 0;
}