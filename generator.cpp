//
// Created by Андрей Москалёв on 04.11.2019.
//

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <fstream>

struct Node {
    int c;
    Node * left, * right;
    Node() {
        left = nullptr;
        right = nullptr;
    }
    Node(int c) {
        this->c = c;
        left = nullptr;
        right = nullptr;
    }
    bool isTerm() {
        return left == nullptr && right == nullptr;
    }
};

void dfs(Node * p, std::string cur, std::map<int, std::string> &mp) {
    if (p->isTerm()) {
        mp[p->c] = cur;
        return;
    }
    dfs(p->left, cur + "0", mp);
    dfs(p->right, cur + "1", mp);
}

std::map<int, std::string> haffmanEncode(const std::string &source) {
    std::map<int, int> cnt;
    for (int c : source)
        ++cnt[c];
    std::set<std::pair<int, Node *>> st;
    for (auto now : cnt) {
        st.insert({now.second, new Node(now.first)});
    }
    std::vector<Node *> lst;
    while (st.size() > 1) {
        auto A = *st.begin();
        st.erase(st.begin());
        auto B = *st.begin();
        st.erase(st.begin());
        int AB = A.first + B.first;
        auto tmp = new Node('#');
        tmp->left = A.second;
        tmp->right = B.second;
        st.insert({AB, tmp});
        lst.push_back(tmp);
    }
    std::map<int, std::string> mp;
    if (lst.size() == 0)
        dfs(st.begin()->second, "0", mp);
    else
        dfs(st.begin()->second, "", mp);
    for (auto now : lst)
        delete now;
    return mp;
}

int main() {
    std::string input;
    char * tmp = new char;
    std::ifstream in("generator.input");
    std::ofstream out("generator.output");
    while ((in.read(tmp, 1))) {
        input += tmp;
    }
    std::map<int, std::string> ans = haffmanEncode(input);
    for (auto now : ans) {
        std::string cur = "";
        cur += now.first;
        out << cur << now.second << '\n';
    }
    return 0;
}
