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
    grid_width = std::sqrt(grid.size());
}

EightPuzzle::EightPuzzle(int _depth, int _path_cost, int _heuristic_value,
                         std::vector<int> grid) {
    node_status.depth = _depth;
    node_status.path_cost = _path_cost;
    node_status.heuristic_value = _heuristic_value;
    m_grid = grid;
    grid_width = std::sqrt(grid.size());
}

EightPuzzle::~EightPuzzle() { }

void EightPuzzle::default_grid_init(std::vector<int> grid) {
    node_status.depth = 0;
    node_status.path_cost = 0;
    node_status.heuristic_value = 0;
    m_grid = grid;
    grid_width = std::sqrt(grid.size());
    setup_grid_solution();
}

void EightPuzzle::node_expansion() {

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

template <typename PriorityQueue>
bool EightPuzzle::is_not_repeated_grid(EightPuzzle child, PriorityQueue expanded) {
    EightPuzzle temp(child.m_grid);
    while(!expanded.empty()) {
        temp = expanded.top();
        expanded.pop();
        if(temp.m_grid == child.m_grid)
            return false;
    }
    return true;
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
    
    auto check = [](EightPuzzle child, std::queue<EightPuzzle> expanded) {
        EightPuzzle temp(child.m_grid);
        while(!expanded.empty()) {
            temp = expanded.front();
            expanded.pop();
            if(temp.m_grid == child.m_grid)
                return false;
        }
        return true;
    };
    
    std::queue<EightPuzzle> fringe;
    std::queue<EightPuzzle> expanded;
    
    // fringe <- insert(make-node(initial-state[problem]), fringe)
    EightPuzzle parent_node(0, 0, 0, m_grid);
    fringe.push(parent_node);

    int maximum_queued_nodes = 0;
    // loop do, return if fringe is empty
    while(!fringe.empty()) {
        // node <- remove-front(fringe)
        parent_node = fringe.front();
        fringe.pop();
        
        // if goal-test[problem] applied to state(node) succeeds return node
        if(check_grid_solution(parent_node.m_grid)) {
            std::cout << "Solution found.\n";
            parent_node.print_grid();
            std::cout << "To solve this problem, the uniform cost algorithm expanded a total of "
                      << expanded.size() << " nodes.\n";
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
                               
        if(child_node.move_up() && check(child_node, expanded)) {
            fringe.push(child_node);
            expanded.push(child_node);
        }
        child_node.m_grid = parent_node.m_grid;
        if(child_node.move_down() && check(child_node, expanded)) {
            fringe.push(child_node);
            expanded.push(child_node);
        }
        child_node.m_grid = parent_node.m_grid;
        if(child_node.move_left() && check(child_node, expanded)) {
            fringe.push(child_node);
            expanded.push(child_node);
        }
        child_node.m_grid = parent_node.m_grid;
        if(child_node.move_right() && check(child_node, expanded)) {
            fringe.push(child_node);
            expanded.push(child_node);
        }
        child_node.m_grid = parent_node.m_grid;
        if(fringe.size() > maximum_queued_nodes) 
            maximum_queued_nodes = fringe.size();
    }
}

void EightPuzzle::misplaced_tile_astar() {
    auto cmp = [](EightPuzzle lhs, EightPuzzle rhs) {
        return (lhs.node_status.path_cost + lhs.node_status.heuristic_value) >
               (rhs.node_status.path_cost + rhs.node_status.heuristic_value);
    };
    
    auto num_misplaced = [this](std::vector<int> grid) { 
        int count = 0;
        for(int i = 0; i < m_grid.size(); i++)
            if(grid.at(i) != m_grid_solution.at(i)) count++;
        return count;
    };
    
    std::priority_queue<EightPuzzle, std::vector<EightPuzzle>, decltype(cmp)> fringe(cmp);
    std::priority_queue<EightPuzzle, std::vector<EightPuzzle>, decltype(cmp)> expanded(cmp);
    
    EightPuzzle parent_node(0, 0, num_misplaced(m_grid), m_grid);
    fringe.push(parent_node);
    expanded.push(parent_node);
    
    int maximum_queued_nodes = 0;
    while(!fringe.empty()) {
        parent_node = fringe.top();
        fringe.pop();
        
        if(check_grid_solution(parent_node.m_grid)) {
            std::cout << "Solution found.\n";
            parent_node.print_grid();
            std::cout << "To solve this problem, the uniform cost algorithm expanded a total of "
                      << expanded.size() << " nodes.\n";
            std::cout << "The maximum number of nodes in the queue at any one time was "
                      << maximum_queued_nodes << ".\n";
            std::cout << "The depth of the goal node was " << parent_node.node_status.depth << ".\n";
            return;
        }
        
        std::cout << "The best state to expand with a g(n) = "
                  << parent_node.node_status.path_cost << " and h(n) = " 
                  << parent_node.node_status.heuristic_value << " is...\n";
        parent_node.print_grid();
        std::cout << "Expanding this node...\n";
        
        EightPuzzle child_node(parent_node.node_status.depth + 1,
                               parent_node.node_status.path_cost + 1,
                               parent_node.node_status.heuristic_value,
                               parent_node.m_grid);
                               
        if(child_node.move_up() && is_not_repeated_grid(child_node, expanded)) {
            child_node.node_status.heuristic_value = num_misplaced(child_node.m_grid);
            fringe.push(child_node);
            expanded.push(child_node);
        }
        child_node.m_grid = parent_node.m_grid;
        if(child_node.move_down() && is_not_repeated_grid(child_node, expanded)) {
            child_node.node_status.heuristic_value = num_misplaced(child_node.m_grid);
            fringe.push(child_node);
            expanded.push(child_node);
        }
        child_node.m_grid = parent_node.m_grid;
        if(child_node.move_left() && is_not_repeated_grid(child_node, expanded)) {
            child_node.node_status.heuristic_value = num_misplaced(child_node.m_grid);
            fringe.push(child_node);
            expanded.push(child_node);
        }
        child_node.m_grid = parent_node.m_grid;
        if(child_node.move_right() && is_not_repeated_grid(child_node, expanded)) {
            child_node.node_status.heuristic_value = num_misplaced(child_node.m_grid);
            fringe.push(child_node);
            expanded.push(child_node);
        }
        child_node.m_grid = parent_node.m_grid;
        if(fringe.size() > maximum_queued_nodes) 
            maximum_queued_nodes = fringe.size();
    }
}

void EightPuzzle::manhattan_dist_astar() {
    auto cmp = [](EightPuzzle lhs, EightPuzzle rhs) {
        return (lhs.node_status.path_cost + lhs.node_status.heuristic_value) >
               (rhs.node_status.path_cost + rhs.node_status.heuristic_value);
    };
    
    auto manhattan_count = [this](std::vector<int> grid) { 
        int count = 0;
        for(int i = 0; i < m_grid.size(); i++) {
            if(grid.at(i) != m_grid_solution.at(i)) {
                if(grid.at(i) == 0) grid.at(i) = 9;
                
                int grid_column = (i % grid_width) + 1;
                int grid_row = (i / grid_width) + 1;
                
                
                std::vector<int>::iterator it = std::find(m_grid_solution.begin(), m_grid_solution.end(), grid.at(i));
                auto index = std::distance(m_grid_solution.begin(), it);
                
                int solution_column = (index % grid_width) + 1;
                int solution_row = (index / grid_width) + 1;
                
                count += std::abs(grid_column - solution_column)
                         + std::abs(grid_row - solution_row);
                
            }
        }
        return count;
    };
    
    std::priority_queue<EightPuzzle, std::vector<EightPuzzle>, decltype(cmp)> fringe(cmp);
    std::priority_queue<EightPuzzle, std::vector<EightPuzzle>, decltype(cmp)> expanded(cmp);
    
    EightPuzzle parent_node(0, 0, manhattan_count(m_grid), m_grid);
    fringe.push(parent_node);
    expanded.push(parent_node);
    
    int maximum_queued_nodes = 0;
    while(!fringe.empty()) {
        parent_node = fringe.top();
        fringe.pop();
        
        if(check_grid_solution(parent_node.m_grid)) {
            std::cout << "Solution found.\n";
            parent_node.print_grid();
            std::cout << "To solve this problem, the uniform cost algorithm expanded a total of "
                      << expanded.size() << " nodes.\n";
            std::cout << "The maximum number of nodes in the queue at any one time was "
                      << maximum_queued_nodes << ".\n";
            std::cout << "The depth of the goal node was " << parent_node.node_status.depth << ".\n";
            return;
        }
        
        std::cout << "The best state to expand with a g(n) = "
                  << parent_node.node_status.path_cost << " and h(n) = " 
                  << parent_node.node_status.heuristic_value << " is...\n";
        parent_node.print_grid();
        std::cout << "Expanding this node...\n";
        
        EightPuzzle child_node(parent_node.node_status.depth + 1,
                               parent_node.node_status.path_cost + 1,
                               parent_node.node_status.heuristic_value,
                               parent_node.m_grid);
                               
        if(child_node.move_up() && is_not_repeated_grid(child_node, expanded)) {
            child_node.node_status.heuristic_value = manhattan_count(child_node.m_grid);
            fringe.push(child_node);
            expanded.push(child_node);
        }
        child_node.m_grid = parent_node.m_grid;
        if(child_node.move_down() && is_not_repeated_grid(child_node, expanded)) {
            child_node.node_status.heuristic_value = manhattan_count(child_node.m_grid);
            fringe.push(child_node);
            expanded.push(child_node);
        }
        child_node.m_grid = parent_node.m_grid;
        if(child_node.move_left() && is_not_repeated_grid(child_node, expanded)) {
            child_node.node_status.heuristic_value = manhattan_count(child_node.m_grid);
            fringe.push(child_node);
            expanded.push(child_node);
        }
        child_node.m_grid = parent_node.m_grid;
        if(child_node.move_right() && is_not_repeated_grid(child_node, expanded)) {
            child_node.node_status.heuristic_value = manhattan_count(child_node.m_grid);
            fringe.push(child_node);
            expanded.push(child_node);
        }
        child_node.m_grid = parent_node.m_grid;
        if(fringe.size() > maximum_queued_nodes) 
            maximum_queued_nodes = fringe.size();
    }
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