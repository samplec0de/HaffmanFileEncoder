//
// Created by Андрей Москалёв on 05.11.2019.
//

#include <iostream>
#include <map>
#include <fstream>

int ind = 0;
std::string dct = "";
char * tmp;
std::map<char, std::string> mp;

std::string getCode() {
    ++ind;
    std::string answer = "";
    while (dct[ind] == '0' || dct[ind] == '1') {
        answer += dct[ind++];
    }
    ++ind;
    return answer;
}

void loadDict() {
    tmp = new char;
    std::ifstream in("generator.output");
    while (in.read(tmp, 1)) {
        dct += tmp;
    }
    while (ind < dct.size()) {
        char dind = dct[ind];
        std::string code = getCode();
        std::cout << dind << ": " << code << "\n";
        mp[dind] = code;
    }
}

int main() {
    loadDict();
//    freopen("encoder.input", "rb", stdin);
//    freopen("encoder.output", "wb", stdout);
    std::ifstream in("encoder.input");
    std::ofstream out("encoder.output");
    while (in.read(tmp, 1)) {
        out << mp[*(tmp)];
        std::cout << mp[*(tmp)];
    }
    return 0;
}
//
// Created by Андрей Москалёв on 13.11.2019.
//
//
//#include <bits/stdc++.h>
//
//using namespace std;
//
//struct Node {
//    char c;
//    Node * left, * right;
//    int id, weight = 1;
//    Node() {
//        left = nullptr;
//        right = nullptr;
//    }
//    Node(char c, int id) {
//        this->c = c;
//        this->id = id;
//        left = nullptr;
//        right = nullptr;
//    }
//    bool isTerm() {
//        return left == nullptr && right == nullptr;
//    }
//};
//
//Node * loadTree() {
//    std::ifstream in("/Users/andrewmoskalev/CLionProjects/Haffman/cmake-build-debug/generator.output");
//    int n;
//    in >> n;
//    std::vector<pair<Node *, int>> v(n + 1);
//    for (int i = 1; i <= n; ++i) {
//        std::ifstream in("generator.output");
//        char * tmp = new char;
//        char * c = new char;
//        in.read(c, 1);
//        string pInd = "";
//        while (in.read(tmp, 1)) {
//            if (*tmp == '\n') {
//                break;
//            }
//            pInd += *tmp;
//        }
//        int p = stoi(pInd);
//        v[i] = {new Node(*c, i), p};
//    }
//    for (int i = 2; i <= n; ++i) {
//        if (v[i].first->left == nullptr) {
//            v[i].first->left = v[v[i].second].first;
//        } else {
//
//        }
//    }
//}
//
//int main() {
//
//    return 0;
//}
