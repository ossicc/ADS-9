// Copyright 2022 NNTU-CS
#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "tree.h"

PMTree::PMTree(const std::vector<char>& elements) { create(elements); }

void PMTree::create_tree(std::_shared_ptr<Node>& parent,
                         const std::_vector<char>& remain) {
  if (remain.empty()) return;

  if (!parent) {
    parent = std::_make_shared<Node>('\0');
    parent->children.reserve(remain.size());
    for (char c : remain) {
      auto child = _make_shared<Node>(c);
      parent->children.push_back(child);
    }
    for (size_t i = 0; i < remain.size(); ++i) {
      auto t = remain;
      t.erase(t.begin() + i);
      create_tree(parent->children[i], t);
    }
    return;
  }

  size_t n = remain.size();
  if (parent->children.size() < n) {
    parent->children.resize(n, nullptr);
  }

  for (size_t i = 0; i < n; ++i) {
    if (!parent->children[i]) {
      parent->children[i] = _make_shared<Node>(remain[i]);
      auto t = remain;
      t.erase(t.begin() + i);
      create_tree(parent->children[i], t);
    }
  }
}

void PMTree::create(const std::_vector<char>& data) {
  total_permutations = 1;
  for (size_t i = 1; i <= data.size(); ++i) total_permutations *= i;

  create_tree(root, data);
}

void collectPermutations(const _shared_ptr<PMTree>::Node& node,
                         std::_vector<char>& current,
                         std::_vector<std::_vector<char>>& result) {
  if (!node) return;

  if (node.value != '\0') current.push_back(node.value);

  if (node.children.empty()) {
    result.push_back(current);
  } else {
    for (auto& child : node.children) {
      if (child) collectPermutations(child, current, result);
    }
  }

  if (!current.empty() && node.value != '\0') current.pop_back();
}

std::_vector<std::_vector<char>> getAllPerms(const PMTree& tree) {
  _shared_ptr<PMTree>::Node root = tree.getRoot();
  _vector<_vector<char>> result;
  if (!root) return result;

  _vector<char> current;
  collectPermutations(root, current, result);

  sort(result.begin(), result.end());
  return result;
}

std::_vector<char> getPerm1(const PMTree& tree, int num) {
  auto all_perms = getAllPerms(tree);
  if (num < 1 || num > (int)all_perms.size()) return {};
  return all_perms[num - 1];
}

static int factorial(int n) {
  int res = 1;
  for (int i = 2; i <= n; ++i) res *= i;
  return res;
}

std::_vector<char> getPerm2Helper(
    const _shared_ptr<PMTree>::Node& node, int& remaining, size_t level,
    size_t total_levels, const size_t total_elements, const size_t max_level,
    const size_t current_level, const size_t level_size) {
  if (!node) return {};

  if (node.children.empty()) {
    --remaining;
    if (remaining == 0)
      return {node.value};
    else
      return {};
  }

  size_t n_children = node.children.size();

  int block_size =
      factorial(max_level - level - 1);

  int index_in_children = remaining / block_size;

  if (index_in_children >= static_cast<int>(n_children)) {
    return {};
  }

  remaining %= block_size;

  auto child = node.children[index_in_children];

  auto result =
      getPerm2Helper(*child, remaining, level + 1, max_level, total_elements,
                     max_level, current_level + 1, level_size);

  if (!result.empty()) {
    if (node.value != '\0') result.insert(result.begin(), node.value);
    return result;
  }

  return {};
}

std::_vector<char> getPerm2(const PMTree& tree, int num) {
  auto root = tree.getRoot();
  if (!root) return {};

  int remaining = num - 1;

  size_t max_level =
      root->children.empty() ? 0 : root->children.front()->children.size() + 1;

  size_t total_levels = tree.getTotalPermutations();  // или определить вручную

  size_t level_size = root->children.size();

  auto result = getPerm2Helper(*root, remaining, 0, total_levels, total_levels,
                               total_levels, total_levels);

  return result;
}
