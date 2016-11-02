#ifndef EIGHT_PUZZLE_H
#define EIGHT_PUZZLE_H

#include <vector>
#include <queue>

#include "search_tree_node.h"


class EightPuzzle : public SearchTreeNode {
    public:
        EightPuzzle();
        EightPuzzle(std::vector<int>);
        EightPuzzle(int, int, int, std::vector<int>);
        ~EightPuzzle();
        
        std::vector<int> get_node_state() const;
        void node_expansion();
        
        void default_grid_init(std::vector<int>);
        
        void uniform_cost();
        void misplaced_tile_astar();
        void manhattan_dist_astar();
        
        bool move_up();
        bool move_down();
        bool move_left();
        bool move_right();
        
        template <typename PriorityQueue>
        bool is_not_repeated_grid(EightPuzzle, PriorityQueue);
        
        void setup_grid();
        void print_grid() const;
        void setup_grid_solution();
        void print_grid_solution();
        bool check_grid_solution(std::vector<int>);
        
    private:
        std::vector<int> m_grid;
        std::vector<int> m_grid_solution;
        
        int grid_width;
};
#endif /* eight_puzzle.h */