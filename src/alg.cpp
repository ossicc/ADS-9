// Copyright 2022 NNTU-CS
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>

#include "tree.h"

PMTree::PMTree(const std::vector<char>& elements) { create(elements); }

std::vector<char> PMTree::getElements() const { return elements; }

void PMTree::create(const std::vector<char>& data) {
  root = std::make_shared<Node>('\0');
  create_tree(root, data);
}

void PMTree::create_tree(std::shared_ptr<Node>& parent,
                         const std::vector<char>& remain) {
  if (remain.empty()) return;

  for (size_t i = 0; i < remain.size(); ++i) {
    auto child = std::make_shared<Node>(remain[i]);
    parent->children.push_back(child);

    std::vector<char> new_remain = remain;
    new_remain.erase(new_remain.begin() + i);

    create_tree(child, new_remain);
  }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;
  if (!tree.getRoot()) return result;

}

std::vector<char> getPerm1(const PMTree& tree, int num) {
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
}

void collectPermutations(const std::shared_ptr<Node>& node,
                         std::string& current,
                         std::vector<std::string>& result) {
  if (!node) return;

  current.push_back(node->value);

  if (node->children.empty()) {
    result.push_back(current);
  } else {
    for (const auto& child : node->children) {
      collectPermutations(child, current, result);
    }
  }

  current.pop_back();
}
size_t PMTree::getTotalPermutations() const {
  auto elems = getElements();
  size_t n = elems.size();
  size_t result = 1;
  for (size_t i = 2; i <= n; ++i) {
    result *= i;
  }
  return result;
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;

  auto elems = tree.getElements();

  std::sort(elems.begin(), elems.end());

  do {
    result.push_back(elems);
  } while (std::next_permutation(elems.begin(), elems.end()));

  return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  auto perms = getAllPerms(tree);
  if (num >= 0 && num < static_cast<int>(perms.size())) {
    return perms[num];
  }
  return {};
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  auto perms = getAllPerms(tree);
  if (num >= 0 && num < static_cast<int>(perms.size())) {
    return perms[num];
  }
  return {};
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;

  auto elems = tree.getElements();

  std::sort(elems.begin(), elems.end());

  do {
    result.push_back(elems);
  } while (std::next_permutation(elems.begin(), elems.end()));

  return result;
}
  return result;
}
