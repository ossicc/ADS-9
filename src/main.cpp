// Copyright 2022 NNTU-CS
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>

#include "tree.h"

std::vector<char> generateAlphabet(int n) {
  std::vector<char> alphabet;
  for (int i = 1; i <= n; ++i) {
    alphabet.push_back('0' + i);
  }
  return alphabet;
}

void printExample() {
  std::vector<char> in = {'1', '2', '3'};

  PMTree tree(in);

  auto perms = getAllPerms(tree);

  std::cout << "Все перестановки {1,2,3}:" << std::endl;

  for (const auto& perm : perms) {
    for (char c : perm) std::cout << c;
    std::cout << "\n";
  }

  std::cout << "\nПолучение перестановок по индексу:\n";

  int totalPerms = tree.getTotalPermutations();

  for (int i = 1; i <= totalPerms; ++i) {
    auto p1 = getPerm1(tree, i);
    auto p2 = getPerm2(tree, i);

    std::cout << "Перестановка №" << i << ": ";
    for (char c : p1) std::cout << c;
    std::cout << " (getPerm1), ";

    std::cout << " ";
    for (char c : p2) std::cout << c;

    std::cout << " (getPerm2)\n";
  }
}

void runExperiment() {
  std::ofstream data_file("experiment_data.csv");
  data_file << "n,getAllPerms_time,getPerm1_time,getPerm2_time\n";

  std::random_device rd;
  std::mt19937 gen(rd());

  for (int n = 1; n <= 10; ++n) {
    auto elements = generateAlphabet(n);
    PMTree tree(elements);

    size_t total_perms = tree.getTotalPermutations();

    if (total_perms == 0) continue;

    std::uniform_int_distribution<> distr(1, total_perms);

    const int test_cases = 10;
    std::vector<int> test_nums(test_cases);
    for (int i = 0; i < test_cases; ++i) test_nums[i] = distr(gen);

    auto start = std::chrono::high_resolution_clock::now();

    auto all_perms = getAllPerms(tree);

    auto end = std::chrono::high_resolution_clock::now();

    double time_all_perm = std::chrono::duration<double>(end - start).count();

    double time_perm1 = 0.0, time_perm2 = 0.0;

    for (int num : test_nums) {
      start = std::chrono::high_resolution_clock::now();
      auto perm = getPerm1(tree, num);
      end = std::chrono::high_resolution_clock::now();
      time_perm1 += std::chrono::duration<double>(end - start).count();

      start = std::chrono::high_resolution_clock::now();
      auto perm2 = getPerm2(tree, num);
      end = std::chrono::high_resolution_clock::now();
      time_perm2 += std::chrono::duration<double>(end - start).count();
    }

    data_file << n << "," << time_all_perm << "," << (time_perm1 / test_cases)
              << "," << (time_perm2 / test_cases) << "\n";

    std ::cout << "n=" << n << " completed." << std ::endl;
  }
  data_file.close();
}

int main() {
  printExample();
  runExperiment();
  return 0;
}
