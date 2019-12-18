//
// Created by Андрей Москалёв on 14.11.2019.
//

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

struct node {
    node *left;
    node *right;
    char val;
    int ind;
    node() {
        left = nullptr;
        right = nullptr;
        val = '#';
        ind = 0;
    }
};

int tree_sz = 0;

map<char, int> count_alph;
map<char, string> code;
map<node *, int> num_str;
set<pair<int, node *>> q;

node *build_tree() {
    while (q.size() > 1) {
        ++tree_sz;

        auto p1 = *q.begin();
        q.erase(q.begin());
        auto p2 = *q.begin();
        q.erase(q.begin());

        node *nw = new node;
        nw->left = p1.second;
        nw->right = p2.second;
        if (q.empty()) {
            nw->ind = 0;
        } else {
            nw->ind = tree_sz;
        }

        q.insert({p1.first + p2.first, nw});
    }

    return (*q.begin()).second;
}

void encode(node *v, string s) {
    if (v->left == nullptr && v->right == nullptr) {
        code[v->val] = s;
        return;
    }
    encode(v->left, s + "0");
    encode(v->right, s + "1");
}

void print(node *root, node *v) {
    if (v == nullptr) {
        num_str[root] = root->ind;
    } else {
        num_str[root] = v->ind;
    }

    if (root->left != nullptr) {
        print(root->left, root);
    }
    if (root->right != nullptr) {
        print(root->right, root);
    }
}

int main() {
    ifstream in("generator.input");
    fstream out("generator.output");

    char *ch = new char;
    string s = "";
    while (in.read(ch, 1)) {
        ++count_alph[*ch];
        s += *ch;
    }
    // cout << s << endl;

    int sz = 1;
    for (auto p : count_alph) {
//        if (!((p.first >= '0' && p.first <= 'z') || (p.first >= 'a' && p.first <= 'z') || (p.first >= 'A' && p.first <= 'Z'))) {
//            cout << p.first << " "<< "JOPA\n";
//        }
        ++sz; ++tree_sz;
        node *nw = new node;
        nw->val = p.first;
        nw->ind = tree_sz;
        q.insert({p.second, nw});
    }

    node *root = build_tree();
    out << tree_sz << endl;
    print(root, nullptr);

    vector<pair<char, int>> res(num_str.size());
    set<int> st;
    for (auto now : num_str) {
        st.insert(now.first->ind);
        res[now.first->ind] = {now.first->val, now.second};
    }
    cout << st.size() << " " << res.size() << "\n";
    for (int i = 0; i < num_str.size(); ++i) {
        out << char(res[i].first) << res[i].second << "\n";
    }
    out.close();
}