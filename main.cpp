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
        std::cout << "Usage: " << argv[0] << " [-w] [cards-file]\n-w shows the word and asks for the definition" << std::endl;
        return 1;
    }

    bool word_first = false;

    std::ifstream cards_file;
    if (std::string(argv[1]) == "-w") { // screw proper option parsing
        if (argc > 2) {
            word_first = true;
            cards_file.open(argv[2]);
        } else {
            std::cout << "No cards-file specified" << std::endl;
        }
    } else {
        cards_file.open(argv[2]);
    }

    std::vector<card> cards;
    card cur;
    while (getline(cards_file, cur.word) && getline(cards_file, cur.def)) {
        cards.push_back(cur);
    }

    random_shuffle(cards.begin(), cards.end());

    bool loop = true;
    while (loop) {

        int num_wrong = 0;
        int failed_one_job = 0;

        sort(cards.begin(), cards.end());

        for (card &v : cards ) {
            std::string word = v.word;
            std::string def = v.def;
            if (word_first) {
                def = v.word;
                word = v.def;
            }

            std::cout << def << std::endl;

            std::string answer;
            getline(std::cin, answer);

            if (stringlower(answer) == stringlower(word)) {
                std::cout << "Correct" << std::endl << std::endl;
                v.streak++;
            } else {
                num_wrong++;
                std::cout << "Wrong, the correct answer is " << word << std::endl;
                std::cout << "Type in the correct answer: ";

                getline(std::cin, answer);
                if (stringlower(answer) != stringlower(word)) {
                    std::cout << "You had one job..." << std::endl;
                    failed_one_job++;
                }

                std::cout << std::endl;
                v.streak = 0;
            }

        }
        std::cout << "You got " << cards.size() - num_wrong << "/" << cards.size() << " correct." << std::endl;
        if (failed_one_job) {
            switch (failed_one_job) {
                case 1:
                    std::cout << "You failed at copying the answer once -_-" << std::endl;
                    break;
                case 2:
                    std::cout << "You failed at copying the answer twice -_-" << std::endl;
                    break;
                default:
                    std::cout << "You failed at copying the answer " << failed_one_job << " times -_-" << std::endl;
                    break;
            }
        }

        std::string input;
http://xkcd.com/292/
        std::cout << "Try again? (y/d/w/n/?) ";
        getline(std::cin, input);
        switch (tolower(input[0])) {
            case 'd':
              word_first = false;
              break;

            case 'w':
              word_first = true;
              break;

            case '?':
              std::cout << "y = yes\nd = see definition first\nw = see word first\nn = no\n? = help" << std::endl;
              goto http; // this was an terrible idea

            default:
              loop = false;
              break;
        }
    }

    return 0;
}
