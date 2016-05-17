#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

struct card {
    std::string word;
    std::string def;
    int streak;

    bool operator<(const card& x) {
        return streak < x.streak;
    }
};

std::string stringlower(std::string str) {
    for (auto &c : str) {
        c = tolower(c);
    }
    return str;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " [cards-file]" << std::endl;
        return 1;
    }

    std::ifstream cards_file;
    cards_file.open(argv[1]);

    std::vector<card> cards;
    card cur;
    while (getline(cards_file, cur.word) && getline(cards_file, cur.def)) {
        cards.push_back(cur);
    }

    random_shuffle(cards.begin(), cards.end());

    int num_wrong = 0;
    bool loop = true;
    while (loop) {

        sort(cards.begin(), cards.end());

        for (card &v : cards ) {
            std::cout << v.def << std::endl;

            std::string answer;
            getline(std::cin, answer);

            if (stringlower(answer) == stringlower(v.word)) {
                std::cout << "Correct" << std::endl << std::endl;
                v.streak++;
            } else {
                num_wrong++;
                std::cout << "Wrong, the correct answer is " << v.word << std::endl;
                std::cout << "Type in the correct answer: ";

                getline(std::cin, answer);
                if (stringlower(answer) != stringlower(v.word))
                    std::cout << "You had one job..." << std::endl;

                std::cout << std::endl;
                v.streak = 0;
            }

        }
        std::cout << "You got " << cards.size() - num_wrong << "/" << cards.size() << " correct." << std::endl;

        std::string input;
        std::cout << "Try again? (y/n) ";
        getline(std::cin, input);
        if (tolower(input[0]) != 'y') loop = false;
    }

    return 0;
}
