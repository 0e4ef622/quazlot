#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct card {
    std::string word;
    std::string def;
};

std::string stringlower(std::string str) {
    for (auto &c : str) {
        c = tolower(c);
    }
    return str;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "filename pl0x" << std::endl;
        return 1;
    }

    std::ifstream cards_file;
    cards_file.open(argv[1]);

    std::vector<card> cards;
    card cur;
    while (getline(cards_file, cur.word) && getline(cards_file, cur.def)) {
        cards.push_back(cur);
    }

    for (card v : cards ) {
        std::cout << v.def << std::endl;

        std::string answer;
        getline(std::cin, answer);

        if (stringlower(answer) == stringlower(v.word))
            std::cout << "Correct" << std::endl << std::endl;
        else
            std::cout << "Wrong, the correct answer is " << v.word << std::endl << std::endl;
    }

    return 0;
}
