#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <queue>

#include "eight_puzzle.h"
#include "search_tree_node.h"

EightPuzzle::EightPuzzle() { }

EightPuzzle::EightPuzzle(std::vector<int> grid) {
    node_status.depth = 0;
    node_status.path_cost = 0;
    node_status.heuristic_value = 0;
    m_grid = grid;
    grid_width = std::sqrt(m_grid.size());
}

EightPuzzle::EightPuzzle(int _depth, int _path_cost, int _heuristic_value,
                         std::vector<int> grid) {
    node_status.depth = _depth;
    node_status.path_cost = _path_cost;
    node_status.heuristic_value = _heuristic_value;
    m_grid = grid;
    grid_width = std::sqrt(m_grid.size());
}

EightPuzzle::~EightPuzzle() { }

void EightPuzzle::default_grid_init(std::vector<int> grid) {
    m_grid = grid;
    setup_grid_solution();
}

std::vector<int> EightPuzzle::get_node_state() const {
    return m_grid;
}

bool EightPuzzle::move_up() {
    std::vector<int>::iterator it;
    it = std::find(m_grid.begin(), m_grid.end(), 0);
    auto index = std::distance(m_grid.begin(), it);
    
    if(index < grid_width) return false;
    else {
        int above_index = (grid_width * ((index / grid_width) - 1) + (index % grid_width));
        std::swap(m_grid.at(index), m_grid.at(above_index));
        return true;
    }
}

bool EightPuzzle::move_down() {
    std::vector<int>::iterator it;
    it = std::find(m_grid.begin(), m_grid.end(), 0);
    auto index = std::distance(m_grid.begin(), it);
    
    if(index >= 2 * grid_width) return false;
    else {
        int below_index = (grid_width * ((index / grid_width) + 1) + (index % grid_width));
        std::swap(m_grid.at(index), m_grid.at(below_index));
        return true;
    }
}

bool EightPuzzle::move_left() {
    std::vector<int>::iterator it;
    it = std::find(m_grid.begin(), m_grid.end(), 0);
    auto index = std::distance(m_grid.begin(), it);
    
    if(!(index % grid_width)) return false;
    else {
        int left_index = index - 1;
        std::swap(m_grid.at(index), m_grid.at(left_index));
        return true;
    }
}

bool EightPuzzle::move_right() {
    std::vector<int>::iterator it;
    it = std::find(m_grid.begin(), m_grid.end(), 0);
    auto index = std::distance(m_grid.begin(), it);
    
    if(!((index + 1) % grid_width)) return false;
    else {
        int right_index = index + 1;
        std::swap(m_grid.at(index), m_grid.at(right_index));
        return true;
    }
}

bool EightPuzzle::is_not_repeated_grid(EightPuzzle child, std::queue<EightPuzzle> expanded) {
    EightPuzzle temp(child.m_grid);
    while(!expanded.empty()) {
        temp = expanded.front();
        expanded.pop();
        if(temp.m_grid == child.m_grid)
            return false;
    }
    return true;
}

void EightPuzzle::node_expansion() {

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
    EightPuzzle parent_node(0, 0, 0, m_grid);
    fringe.push(parent_node);

    int expanded_nodes = 0;
    int maximum_queued_nodes = 0;
    int currently_queued_nodes = 1;
    // loop do, return if fringe is empty
    while(!fringe.empty()) {
        // std::cout << "Fringe size: " << fringe.size() << std::endl;
        // node <- remove-front(fringe)
        parent_node = fringe.front();
        fringe.pop();
        
        // if goal-test[problem] applied to state(node) succeeds return node
        if(check_grid_solution(parent_node.m_grid)) {
            std::cout << "Solution found.\n";
            parent_node.print_grid();
            std::cout << "To solve this problem, the uniform cost algorithm expanded a total of "
                      << expanded_nodes << " nodes.\n";
            std::cout << "The maximum number of nodes in the queue at any one time was "
                      << maximum_queued_nodes << ".\n";
            std::cout << "The depth of the goal node was " << parent_node.node_status.depth << ".\n";
            return;
        }
        
        std::cout << "The best state to expand with a g(n) = "
                  << parent_node.node_status.path_cost << " is...\n";
        parent_node.print_grid();
        std::cout << "Expanding this node...\n";
        
        // fringe <- insert_all(expand(node, problem), fringe)
        EightPuzzle child_node(parent_node.node_status.depth + 1,
                               parent_node.node_status.path_cost + 1,
                               parent_node.node_status.heuristic_value,
                               parent_node.m_grid);
                               
        if(child_node.move_up() && is_not_repeated_grid(child_node, expanded)) {
            fringe.push(child_node);
            expanded.push(child_node);
            maximum_queued_nodes++;
            currently_queued_nodes++;
        }
        child_node.m_grid = parent_node.m_grid;
        if(child_node.move_down() && is_not_repeated_grid(child_node, expanded)) {
            fringe.push(child_node);
            expanded.push(child_node);
            expanded_nodes++;
            currently_queued_nodes++;
        }
        child_node.m_grid = parent_node.m_grid;
        if(child_node.move_left() && is_not_repeated_grid(child_node, expanded)) {
            fringe.push(child_node);
            expanded.push(child_node);
            expanded_nodes++;
            currently_queued_nodes++;
        }
        child_node.m_grid = parent_node.m_grid;
        if(child_node.move_right() && is_not_repeated_grid(child_node, expanded)) {
            fringe.push(child_node);
            expanded.push(child_node);
            expanded_nodes++;
            currently_queued_nodes++;
        }
        child_node.m_grid = parent_node.m_grid;
        if(currently_queued_nodes > maximum_queued_nodes) 
            maximum_queued_nodes = currently_queued_nodes;
    }
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
    m_grid.clear();
    
    if(std::cin.peek() == '\n')
        std::cin.ignore();
    std::getline(std::cin, s);
    std::stringstream ss(s);
    while(getline(ss, value, ' ')) {
        try {
            m_grid.push_back(stoi(value));
        }
        catch (const std::exception &e) {
            std::cout << "Too many spaces, please re-enter the values\n";
            setup_grid();
        } 
    }
    
    double d_sqrt = std::sqrt(m_grid.size());
    grid_width = d_sqrt;
    if (d_sqrt != grid_width) {
        std::cout << "Not a NxN grid, please enter a perfect square set of numbers\n";
        setup_grid();
    }

    int num_zeros = 0;
    for_each(m_grid.begin(), m_grid.end(), 
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

void EightPuzzle::print_grid() const {
    for(int i = 0; i < m_grid.size(); i++) {
        std::cout << m_grid.at(i) << " ";
        if(!((i+1) % grid_width || i == 0)) std::cout << std::endl;
    }
    std::cout << std::endl;
}

void EightPuzzle::setup_grid_solution() {
    int j = 0;
    m_grid_solution.clear();
    
    for_each(m_grid.begin(), m_grid.end() - 1, 
            [&, this](int &i) {
                m_grid_solution.push_back(++j);
            });
    m_grid_solution.push_back(0);
}

void EightPuzzle::print_grid_solution() {
    for(int i = 0; i < m_grid_solution.size(); i++) {
        std::cout << m_grid_solution.at(i) << " ";
        if(!((i+1) % grid_width || i == 0)) std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool EightPuzzle::check_grid_solution(std::vector<int> grid) {
    return grid == m_grid_solution;
}