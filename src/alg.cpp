// Copyright 2022 NNTU-CS
#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>

#include "tree.h"

PMTree::PMTree(const std::vector<char>& elements) { create(elements); }

void PMTree::create_tree(std::shared_ptr<Node>& parent,
                         const std::vector<char>& remain) {
  if (remain.empty()) {
    return;
  }

  if (!parent) {
    parent = std::make_shared<Node>('\0');
    parent->children.reserve(remain.size());
    for (char c : remain) {
      auto child = std::make_shared<Node>(c);
      parent->children.push_back(child);
    }
    for (size_t i = 0; i < remain.size(); ++i) {
      std::vector<char> t = remain;
      t.erase(t.begin() + i);
      create_tree(parent->children[i], t);
    }
    return;
  }

  size_t n = remain.size();
  if (parent->children.size() < n) {
    while (parent->children.size() < n) {
      parent->children.push_back(nullptr);
    }
  }
  for (size_t i = 0; i < n; ++i) {
    if (!parent->children[i]) {
      parent->children[i] = std::make_shared<Node>(remain[i]);
      std::vector<char> t = remain;
      t.erase(t.begin() + i);
      create_tree(parent->children[i], t);
    }
  }
}

void PMTree::create(const std::vector<char>& data) {
  total_permutations = 1;
  for (size_t i = 1; i <= data.size(); ++i) {
    total_permutations *= i;
  }
  create_tree(root, data);
}

void collectPermutations(const std::shared_ptr<PMTree::Node>& node,
                         std::vector<char>& current,
                         std::vector<std::vector<char>>& result) {
  if (!node) return;

  if (node->value != '\0') {
    current.push_back(node->value);
  }

  if (node->children.empty()) {
    result.push_back(current);
  } else {
    for (const auto& child : node->children) {
      if (child) {
        collectPermutations(child, current, result);
      }
    }
  }

  if (!current.empty() && node->value != '\0') {
    current.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;
  auto root = tree.getRoot();
  if (!root) return result;

  std::vector<char> current;
  collectPermutations(root, current, result);

  std::sort(result.begin(), result.end());

  return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  auto all_perms = getAllPerms(tree);

  if (num < 1 || num > static_cast<int>(all_perms.size())) {
    return {};
  }

  return all_perms[num - 1];
}

static int factorial(int n) {
  int res = 1;
  for (int i = 2; i <= n; ++i) res *= i;
  return res;
}

std::vector<char> getPerm2Helper(const std::shared_ptr<PMTree::Node>& node,
                                 int& remaining,
                                 const std::vector<char>& elements_in_node,
                                 const size_t level, const size_t total_levels,
                                 const size_t& total_elements) {
  if (!node) {
    std::cerr << "getPerm2Helper: node is nullptr at level " << level << "\n";
    return {};
  }

  if (node->children.empty()) {
    --remaining;
    if (remaining == 0)
      return {node->value};
    else
      return {};
  }

  size_t n_children = node->children.size();

  std::cerr << "Level " << level << ", remaining = " << remaining
            << ", children = " << n_children << "\n";

  int block_size = factorial(static_cast<int>(total_levels - level - 1));
  int index_in_children = remaining / block_size;

  if (index_in_children >= static_cast<int>(n_children)) {
    std::cerr << "Index out of range: " << index_in_children
              << " >= " << n_children << "\n";
    return {};
  }

  remaining %= block_size;

  auto child_ptr = node->children[index_in_children];
  if (!child_ptr) {
    std::cerr << "Child pointer is nullptr at index " << index_in_children
              << ", level " << level << "\n";
    return {};
  }

  auto result = getPerm2Helper(child_ptr, remaining, elements_in_node,
                               level + 1, total_levels, total_elements);

  if (!result.empty()) {
    if (node->value != '\0') result.insert(result.begin(), node->value);
    return result;
  }

  return {};
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  auto root = tree.getRoot();
  if (!root) return {};

  int remaining = num - 1;
  size_t total_levels =
      root->children.empty() ? 0 : root->children.front()->children.size() + 1;
  std::vector<char> elements_in_node;

  auto result =
      getPerm2Helper(root, remaining, elements_in_node, 0, total_levels, 0);
  return result;
}
