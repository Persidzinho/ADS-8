// Copyright 2021 NNTU-CS
#include <fstream>
#include <iostream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <utility>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error!" << std::endl;
    return;
  }

  std::string word;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(static_cast<unsigned char>(ch));
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }
  if (!word.empty()) {
    tree.insert(word);
  }
  file.close();
}

bool freqCompare(const std::pair<std::string, int>& a,
                 const std::pair<std::string, int>& b) {
  return a.second > b.second;
}

void printFreq(BST<std::string>& tree) {
  auto words = tree.getAll();
  std::sort(words.begin(), words.end(), freqCompare);

  std::ofstream out("result/freq.txt");
  if (!out) {
    std::cerr << "Cannot create result/freq.txt" << std::endl;
    return;
  }

  for (const auto& p : words) {
    out << p.first << " " << p.second << std::endl;
    std::cout << p.first << " " << p.second << std::endl;
  }
  out.close();
}
