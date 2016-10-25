#ifndef EIGHT_PUZZLE_H
#define EIGHT_PUZZLE_H

#include <vector>

class EightPuzzle {
    public:
        EightPuzzle();
        ~EightPuzzle();
    
        void uniform_cost(int);
        void misplaced_tile_astar(int);
        void manhattan_dist_astar(int);
        
        void setup_puzzle_grid();
        void print_puzzle_grid();
    private:
        std::vector<int> puzzle_grid;

};
#endif /* eight_puzzle.h */