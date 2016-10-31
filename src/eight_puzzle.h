#ifndef EIGHT_PUZZLE_H
#define EIGHT_PUZZLE_H

#include <vector>

class EightPuzzle {
    public:
        EightPuzzle();
        ~EightPuzzle();
        
        void default_puzzle_init(std::vector<int>);
        
        void uniform_cost();
        void misplaced_tile_astar();
        void manhattan_dist_astar();
        
        void setup_puzzle_grid();
        void print_puzzle_grid();
        void setup_puzzle_grid_solution();
        void print_puzzle_grid_solution();
        bool check_puzzle_grid_solution(std::vector<int>);
        
    private:
        std::vector<int> puzzle_grid;
        std::vector<int> puzzle_grid_solution;
        
        int grid_width;
};
#endif /* eight_puzzle.h */