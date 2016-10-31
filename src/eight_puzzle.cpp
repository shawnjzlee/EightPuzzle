#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <queue>

#include "eight_puzzle.h"
#include "search_tree_node.h"

EightPuzzle::EightPuzzle() { }

EightPuzzle::EightPuzzle(int _depth, int _path_cost, int _heuristic_value,
                               std::vector<int> _grid) {
    node_status.depth = _depth;
    node_status.path_cost = _path_cost;
    node_status.heuristic_value = _heuristic_value;
    grid = _grid;
    grid_width = std::sqrt(grid.size());
}

EightPuzzle::~EightPuzzle() { }

void EightPuzzle::default_grid_init(std::vector<int> _grid) {
    grid = _grid;
    setup_grid_solution();
}

std::vector<int> EightPuzzle::get_node_state() {
    return grid;
}

void EightPuzzle::node_expansion() {
    std::cout << "The best state to expand with a g(n) = "
              << node_status.path_cost << " is...\n";
    print_grid();
    std::cout << "Expanding this node...\n";
}


// function expand(node, problem) returns a set of nodes
// successors <- the empty set
// for each action, result in successor-fn[problem](state[node]) do
//      s <- a new node
//      parent_node[s] <- node; action[s] <- action; state[s] <- result
//      path_cost[s] <- path_cost[node] + step_cost(node, action, s)
//      depth[s] <- depth[node] + 1
//      add s to successor
// return successor

void EightPuzzle::uniform_cost() {
    std::queue<EightPuzzle> fringe;
    std::queue<EightPuzzle> expanded;
    
    // fringe <- insert(make-node(initial-state[problem]), fringe)
    EightPuzzle node(0, 0, 0, grid);
    fringe.push(node);

    int expanded_nodes = 0;
    int maximum_queued_nodes = 0;
    int currently_queued_nodes = 1;
    // loop do, return if fringe is empty
    while(!fringe.empty()) {
        // node <- remove-front(fringe)
        node = fringe.front();
        fringe.pop();
        
        //if goal-test[problem] applied to state(node) succeeds return node
        if(check_grid_solution(grid)) {
            std::cout << "Solution found.\n";
            node.print_grid();
            std::cout << "To solve this problem, the uniform cost algorithm expanded a total of "
                      << expanded_nodes << " nodes.\n";
            std::cout << "The maximum number of nodes in the queue at any one time was "
                      << maximum_queued_nodes << ".\n";
            std::cout << "The depth of the goal node was " << node.node_status.depth << ".\n";
            return;
        }
        
        
        
        
        
        
        //fringe <- insert_all(expand(node, problem), fringe)
    }
    return;
}

void EightPuzzle::misplaced_tile_astar() {
    return;
}

void EightPuzzle::manhattan_dist_astar() {
    return;
}

void EightPuzzle::setup_grid() {
    std::cout << "Enter your puzzle, use a zero to represent the blank."
              << " Separate values with a space. Press 'Enter' when complete\n";
    std::string s, value;
    grid.clear();
    
    if(std::cin.peek() == '\n')
        std::cin.ignore();
    std::getline(std::cin, s);
    std::stringstream ss(s);
    while(getline(ss, value, ' ')) {
        try {
            grid.push_back(stoi(value));
        }
        catch (const std::exception &e) {
            std::cout << "Too many spaces, please re-enter the values\n";
            setup_grid();
        } 
    }
    
    double d_sqrt = std::sqrt(grid.size());
    grid_width = d_sqrt;
    if (d_sqrt != grid_width) {
        std::cout << "Not a NxN grid, please enter a perfect square set of numbers\n";
        setup_grid();
    }

    int num_zeros = 0;
    for_each(grid.begin(), grid.end(), 
            [&, this](int &i) {
                if(i == 0) num_zeros++;
                if(num_zeros > 1) {
                    std::cout << "Please enter only one zero\n";
                    setup_grid();
                    return;
                }
                if(i > 9 && grid_width < 4) {
                    std::cout << "Please enter single digit values\n";
                    setup_grid();
                    return;
                }
            });
            
    if(num_zeros == 0) {
        std::cout << "Please enter one zero\n";
        setup_grid();
    }
    
    setup_grid_solution();
}

void EightPuzzle::print_grid() {
    for(int i = 0; i < grid.size(); i++) {
        std::cout << grid.at(i) << " ";
        if(!((i+1) % grid_width || i == 0)) std::cout << std::endl;
    }
    std::cout << std::endl;
}

void EightPuzzle::setup_grid_solution() {
    int j = 0;
    grid_solution.clear();
    
    for_each(grid.begin(), grid.end() - 1, 
            [&, this](int &i) {
                grid_solution.push_back(++j);
            });
    grid_solution.push_back(0);
    
    print_grid_solution();
}

void EightPuzzle::print_grid_solution() {
    for(int i = 0; i < grid_solution.size(); i++) {
        std::cout << grid_solution.at(i) << " ";
        if(!((i+1) % grid_width || i == 0)) std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool EightPuzzle::check_grid_solution(std::vector<int> state) {
    return state == grid_solution;
}