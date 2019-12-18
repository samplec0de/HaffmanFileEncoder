//
//  main.cpp
//  Haffman
//
//  Created by Андрей Москалёв on 13.11.2019.
//  Copyright © 2019 Андрей Москалёв. All rights reserved.
//

//
// Created by Андрей Москалёв on 13.11.2019.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

struct Node {
    char c;
    Node * left, * right;
    int id, weight = 1;
    Node() {
        left = nullptr;
        right = nullptr;
    }
    Node(char c, int id) {
        this->c = c;
        this->id = id;
        left = nullptr;
        right = nullptr;
    }
    bool isTerm() {
        return left == nullptr && right == nullptr;
    }
};

Node * buildTree(const std::string& source) {
    std::map<char, int> cnt;
    for (int c : source)
        ++cnt[c];
    std::set<std::pair<int, Node *>> st;
    int nodes = 0;
    for (auto now : cnt)
        st.insert({now.second, new Node(now.first, ++nodes)});
    while (st.size() > 1) {
        auto A = *st.begin();
        st.erase(st.begin());
        auto B = *st.begin();
        st.erase(st.begin());
        int AB = A.first + B.first;
        auto tmp = new Node('#', ++nodes);
        tmp->left = A.second;
        tmp->right = B.second;
        tmp->weight = AB;
        st.insert({AB, tmp});
    }
    auto root = (*st.begin()).second;
    root->id = 0;
    return root;
}

void fillMap(Node * root, Node * p, std::map<Node *, int> &mp) {
    if (root == nullptr)
        return;
    if (p == nullptr)
        mp[root] = root->id;
    else
        mp[root] = p->id;
    if (root->left != nullptr)
        fillMap(root->left, root, mp);
    if (root->right != nullptr)
        fillMap(root->right, root, mp);
}

void printTree(std::map<Node *, int> &mp) {
    std::vector<std::pair<char, int>> res(mp.size());
    for (auto now : mp) {
        res[now.first->id] = {now.first->c, now.second};
    }
    std::ofstream out("/Users/andrewmoskalev/CLionProjects/Haffman/cmake-build-debug/generator.output");
    out << mp.size() << '\n';
    for (int i = 0; i < mp.size(); ++i) {
        out << res[i].first << res[i].second << '\n';
    }
}

int main() {
    std::string input = "";
    char * tmp = new char;
    std::ifstream in("/Users/andrewmoskalev/CLionProjects/Haffman/cmake-build-debug/generator.input");
    while ((in.read(tmp, 1))) {
        input += tmp;
    }
    Node * root = buildTree(input);
    std::map<Node *, int> mp;
    fillMap(root, nullptr, mp);
    printTree(mp);
    return 0;
}
