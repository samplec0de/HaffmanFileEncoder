//
// Created by Андрей Москалёв on 13.11.2019.
//

#include <bits/stdc++.h>

using namespace std;

struct Node {
    char c;
    Node * left, * right;
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

map<char, string> codes;
void dfs(Node* now, string &s){
    if(now == nullptr)
        return;
    if(now->left == nullptr && now->right == nullptr){
        codes[now->c] = s;
    }
    s += '0';
    dfs(now->left, s);
    s.pop_back();
    s += '1';
    dfs(now->right, s);
    s.pop_back();
}

void get(int &pos, string &s, Node* now){
    if(now->left == nullptr && now->right == nullptr){
        cout << now->c;
        return;
    }
    if(s[pos] == '0'){
        get(++pos, s, now->left);
    } else {
        get(++pos, s, now->right);
    }
}

set<char> simbols;

void get_symbols(Node *now){
    if(now == nullptr)
        return;
    if(now->left == nullptr && now->right == nullptr){
        simbols.insert(now->c);
        return;
    }
    get_symbols(now->left);
    get_symbols(now->right);
}

int main() {
    Node * root = loadTree();

    
    char* buf = new char;
    
    get_symbols(root);
    string s;
    ifstream input("encoder.input");
    while(!input.eof()){
        if(!input.read(buf, 1)){
            break;
        }
        s.push_back(*buf);
    }
    delete buf;

    string tmp = "";
    dfs(root, tmp);
    if(codes.size() == 1){
        codes.begin()->second = '0';
    }
    freopen("encoder.output", "w", stdout);
    uint64_t size_code = 0;
    for(auto now : s){
        size_code += codes[now].size();
    }
    for(int i = 0; i < 8; i++){
        cout << (char)(size_code >> ((7 - i) * 8));
    }
    int size_buf = 0;
    char ch;
    for(auto now : s){
        for(auto bit : codes[now]){
            ch <<= 1;
            if(bit == '1'){
                ch |= 1;
            }
            size_buf++;
            if(size_buf == 8){
                cout << ch;
                size_buf = 0;
                ch = 0;
            }
        }
    }
    if (size_buf != 0){
        ch <<= (8 - size_buf);
        cout << ch;
    }
    return 0;
}
