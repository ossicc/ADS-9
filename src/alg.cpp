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
    parent->children.resize(n);
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
      collectPermutations(child, current, result);
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
  if (node->children.empty()) {
    --remaining;
    if (remaining == 0)
      return {node->value};
    else
      return {};
  }

  size_t n_children = node->children.size();
  std::vector<char> remaining_elements_in_node(elements_in_node);

  for (size_t i = 0; i < n_children; ++i) {
    int block_size = factorial(static_cast<int>(total_levels - level - 1));

    int index_in_children = remaining / block_size;

    remaining %= block_size;

    auto result = getPerm2Helper(node->children[index_in_children], remaining,
                                 remaining_elements_in_node, level + 1,
                                 total_levels, total_elements);

    if (!result.empty()) {
      if (node->value != '\0') result.insert(result.begin(), node->value);
      return result;
    }
  }

  return {};
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  int total_perm = tree.getTotalPermutations();
  if (num < 1 || num > total_perm) return {};

  auto root = tree.getRoot();
  if (!root) return {};

  size_t n = root->children.size();

  std::vector<char> elements_in_node;

  for (const auto& ch : root->children) elements_in_node.push_back(ch->value);

  int remaining = num;

  auto perm_result =
      getPerm2Helper(root, remaining, elements_in_node, 0,
                     static_cast<size_t>(elements_in_node.size()),
                     static_cast<size_t>(elements_in_node.size()));

  return perm_result;
}
