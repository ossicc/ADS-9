// Copyright 2022 NNTU-CS
#pragma once
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <iostream>
#include <memory>
#include <vector>

class PMTree {
 public:
  struct Node {
    char value;
    std ::vector<std ::shared_ptr<Node>> children;
    explicit Node(char val) : value(val) {}
  };

  explicit PMTree(const std ::vector<char>& elements);
  ~PMTree() = default;

  void create_tree(std ::shared_ptr<Node>& parent,
                   const std ::vector<char>& remain);
  void create(const std ::vector<char>& elements);

  std ::shared_ptr<Node> getRoot() const { return root; }
  int getTotalPermutations() const { return total_permutations; }

 private:
  std ::shared_ptr<Node> root;
  int total_permutations;
};

std ::vector<std ::vector<char>> getAllPerms(const PMTree& tree);
std ::vector<char> getPerm1(const PMTree& tree, int num);
std ::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
