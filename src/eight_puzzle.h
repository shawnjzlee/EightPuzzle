#ifndef EIGHT_PUZZLE_H
#define EIGHT_PUZZLE_H

#include <vector>

#include "search_tree_node.h"

class EightPuzzle : public SearchTreeNode {
    public:
        EightPuzzle();
        EightPuzzle(int, int, int, std::vector<int>);
        ~EightPuzzle();
        
        std::vector<int> get_node_state();
        
        void node_expansion();
        
        void default_grid_init(std::vector<int>);
        
        void uniform_cost();
        void misplaced_tile_astar();
        void manhattan_dist_astar();
        
        void setup_grid();
        void print_grid();
        void setup_grid_solution();
        void print_grid_solution();
        bool check_grid_solution(std::vector<int>);
        
    private:
        std::vector<int> grid;
        std::vector<int> grid_solution;
        
        int grid_width;
};
#endif /* eight_puzzle.h */