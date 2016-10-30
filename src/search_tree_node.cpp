#include <iostream>
#include <vector>

#include "search_tree_node.h"

SearchTreeNode::SearchTreeNode() { }

SearchTreeNode::SearchTreeNode(int _depth, int _path_cost, int _heuristic_value,
                               std::vector<int> _state) {
    depth = _depth;
    path_cost = _path_cost;
    heuristic_value = _heuristic_value;
    state = _state;
}

SearchTreeNode::~SearchTreeNode() { }

void SearchTreeNode::print_node_state() {
    for(const auto &i : state) std::cout << i << " ";
    std::cout << std::endl;
}

int SearchTreeNode::get_depth() const {
    return depth;
}

void SearchTreeNode::set_depth(int _depth) {
    depth = _depth;
}

int SearchTreeNode::get_path_cost() const {
    return path_cost;
}

void SearchTreeNode::set_path_cost(int _path_cost) {
    path_cost = _path_cost;
}

int SearchTreeNode::get_heuristic_value() const {
    return heuristic_value;
}

void SearchTreeNode::set_heuristic_value(int _heuristic_value) {
    heuristic_value = _heuristic_value;
}