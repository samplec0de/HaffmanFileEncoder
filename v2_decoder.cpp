#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <fstream>

using namespace std;

struct Node {
    char c;
    Node *left, *right;
    int id;

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

Node *root = nullptr;
map<char, string> table;

void dfs(Node *now, string &s) {
    if (now == nullptr)
        return;
    if (now->isTerm()) {
        table[now->c] = s;
    }
    s += '0';
    dfs(now->left, s);
    s.pop_back();
    s += '1';
    dfs(now->right, s);
    s.pop_back();
}

void print(int &ind, string &s, Node *p) {
    if (p->isTerm()) {
        cout << p->c;
        if (p == root) {
            ind++;
        }
        return;
    }
    if (s[ind] == '0')
        print(++ind, s, p->left);
    else
        print(++ind, s, p->right);
}

Node * loadTree() {
    std::ifstream in("/Users/andrewmoskalev/CLionProjects/Haffman/cmake-build-debug/generator.output");
    string s_n = "";
    char * tmp = new char;
    char * c = new char;
    while (in.read(tmp, 1)) {
        if (*tmp == '\n')
            break;
        s_n += *tmp;
    }
    int n = stoi(s_n);
    std::vector<pair<Node *, int>> v(n);
    for (int i = 0; i < n; ++i) {
        in.read(c, 1);
        string pInd = "";
        while (in.read(tmp, 1)) {
            if (*tmp == '\n') {
                break;
            }
            pInd += *tmp;
        }
        int p = stoi(pInd);
        v[i] = {new Node(*c, i), p};
    }
    for (int i = 1; i < n; ++i) {
        if (v[v[i].second].first->left == nullptr) {
            v[v[i].second].first->left = v[i].first;
        } else {
            v[v[i].second].first->right = v[i].first;
        }
    }
    return v[0].first;
}

int main() {
    char *buf = new char;
    root = loadTree();
    ifstream inp("encoder.output");
    uint64_t encodeSize = 0;
    for (int i = 0; i < 8; ++i) {
        encodeSize <<= 8;
        inp.read(buf, 1);
        encodeSize |= (unsigned char) (*buf);
    }
    string s;
    for (uint64_t i = 0; i < encodeSize; i += 8) {
        if ((i + 8 > encodeSize) && (encodeSize % 8 != 0)) {
            inp.read(buf, 1);
            encodeSize %= 8;
            for (int j = 0; j < encodeSize; ++j)
                s += (((*buf & (1 << (7 - j))) >> (7 - j)) + '0');
            break;
        }
        inp.read(buf, 1);
        for (int j = 0; j < 8; ++j)
            s += ((*buf & (1 << (7 - j))) >> (7 - j)) + '0';
    }
    freopen("decoder.output", "w", stdout);
    int ind = 0;
    while (ind < s.size())
        print(ind, s, root);
    return 0;
}