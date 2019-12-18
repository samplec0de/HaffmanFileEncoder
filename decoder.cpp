//
// Created by Андрей Москалёв on 05.11.2019.
//

#include <iostream>
#include <map>
#include <fstream>

int ind = 0;
std::string dct = "";
char * tmp;
std::map<char *, std::string> mp;
std::map<std::string, char *> rmp;

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
        char * dind = new char(dct[ind]);
        std::string code = getCode();
        mp[dind] = code;
    }
}


int main() {
    loadDict();
//    freopen("encoder.output", "rb", stdin);
//    freopen("decoder.output", "wb", stdout);
    std::ifstream in("encoder.output");
    std::ofstream out("decoder.output");
    for (auto now : mp) {
        rmp[now.second] = now.first;
    }
    std::string cur = "";
    while (in.read(tmp, 1)) {
        cur += tmp;
        if (rmp.find(cur) != rmp.end()) {
//            std::cout << rmp[cur];
            out << rmp[cur];
            cur = "";
        }
    }
    return 0;
}
