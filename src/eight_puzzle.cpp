#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <queue>

#include "eight_puzzle.h"
#include "search_tree_node.h"

EightPuzzle::EightPuzzle() { }

EightPuzzle::~EightPuzzle() { }

void EightPuzzle::default_puzzle_init(std::vector<int> _puzzle_grid) {
    puzzle_grid = _puzzle_grid;
    setup_puzzle_grid_solution();
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
    std::queue<SearchTreeNode> fringe;
    std::queue<SearchTreeNode> expanded;
    
    // fringe <- insert(make-node(initial-state[problem]), fringe)
    SearchTreeNode node(0, 0, 0, puzzle_grid);
    fringe.push(node);
    
    std::cout << "In uniform cost: " << std::endl;
    print_puzzle_grid();
    node.print_node_state();
    print_puzzle_grid_solution();
    
    int expanded_nodes = 0;
    int maximum_queued_nodes = 0;
    int currently_queued_nodes = 1;
    // loop do, return if fringe is empty
    while(!fringe.empty()) {
        // node <- remove-front(fringe)
        node = fringe.front();
        fringe.pop();
        
        //if goal-test[problem] applied to state(node) succeeds return node
        if(check_puzzle_grid_solution(node.get_node_state())) {
            std::cout << "Solution found.\n";
            node.print_node_state();
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

void EightPuzzle::setup_puzzle_grid() {
    std::cout << "Enter your puzzle, use a zero to represent the blank."
              << " Separate values with a space. Press 'Enter' when complete\n";
    std::string s, value;
    puzzle_grid.clear();
    
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
            [&, this](int &i) {
                if(i == 0) num_zeros++;
                if(num_zeros > 1) {
                    std::cout << "Please enter only one zero\n";
                    setup_puzzle_grid();
                    return;
                }
                if(i > 9) {
                    std::cout << "Please enter single digit values\n";
                    setup_puzzle_grid();
                    return;
                }
            });
            
    if(num_zeros == 0) {
        std::cout << "Please enter one zero\n";
        setup_puzzle_grid();
    }
    
    double d_sqrt = std::sqrt(puzzle_grid.size());
    grid_width = d_sqrt;
    if (d_sqrt != grid_width) {
        std::cout << "Not a NxN grid, please enter a perfect square set of numbers\n";
        setup_puzzle_grid();
    }
    
    setup_puzzle_grid_solution();
}

void EightPuzzle::print_puzzle_grid() {
    for(int i = 0; i < puzzle_grid.size(); i++) {
        std::cout << puzzle_grid.at(i) << " ";
        if(!((i+1) % grid_width || i == 0)) std::cout << std::endl;
    }
    std::cout << std::endl;
}

void EightPuzzle::setup_puzzle_grid_solution() {
    int j = 0;
    puzzle_grid_solution.clear();
    
    for_each(puzzle_grid.begin(), puzzle_grid.end() - 1, 
            [&, this](int &i) {
                puzzle_grid_solution.push_back(++j);
            });
    puzzle_grid_solution.push_back(0);
    
    print_puzzle_grid_solution();
}

void EightPuzzle::print_puzzle_grid_solution() {
    for(int i = 0; i < puzzle_grid_solution.size(); i++) {
        std::cout << puzzle_grid_solution.at(i) << " ";
        if(!((i+1) % grid_width || i == 0)) std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool EightPuzzle::check_puzzle_grid_solution(std::vector<int> state) {
    return state == puzzle_grid_solution;
}