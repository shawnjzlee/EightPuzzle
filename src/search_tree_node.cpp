#include <iostream>
#include <vector>
#include <cmath>

#include "search_tree_node.h"

SearchTreeNode::SearchTreeNode() { }

SearchTreeNode::SearchTreeNode(int _depth, int _path_cost, int _heuristic_value,
                               std::vector<int> _state) {
    node_status.depth = _depth;
    node_status.path_cost = _path_cost;
    node_status.heuristic_value = _heuristic_value;
    state = _state;
    grid_width = std::sqrt(state.size());
}

SearchTreeNode::~SearchTreeNode() { }

std::vector<int> SearchTreeNode::get_node_state() {
    return state;
}

void SearchTreeNode::print_node_state() {
    for(int i = 0; i < state.size(); i++) {
        std::cout << state.at(i) << " ";
        if(!((i+1) % grid_width || i == 0)) std::cout << std::endl;
    }
    std::cout << std::endl;
}

// int SearchTreeNode::get_depth() const {
//     return depth;
// }

// void SearchTreeNode::set_depth(int _depth) {
//     depth = _depth;
// }

// int SearchTreeNode::get_path_cost() const {
//     return path_cost;
// }

// void SearchTreeNode::set_path_cost(int _path_cost) {
//     path_cost = _path_cost;
// }

// int SearchTreeNode::get_heuristic_value() const {
//     return heuristic_value;
// }

// void SearchTreeNode::set_heuristic_value(int _heuristic_value) {
//     heuristic_value = _heuristic_value;
// }