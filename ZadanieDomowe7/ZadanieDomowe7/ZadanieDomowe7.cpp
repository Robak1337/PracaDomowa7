#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

void loadWordsFromFile(const std::string& filename, std::vector<std::string>& words) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string word;
        while (file >> word) {
            words.push_back(word);
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file " << filename << std::endl;
    }
}

std::string chooseRandomWord(const std::vector<std::string>& words) {
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

void displayCurrentProgress(const std::string& word, const std::vector<bool>& guessed) {
    for (size_t i = 0; i < word.length(); ++i) {
        if (guessed[i]) {
            std::cout << word[i] << " ";
        }
        else {
            std::cout << "_ ";
        }
    }
    std::cout << std::endl;
}

bool isWordGuessed(const std::vector<bool>& guessed) {
    for (bool letterGuessed : guessed) {
        if (!letterGuessed) {
            return false;
        }
    }
    return true;
}

int main() {
    std::vector<std::string> words;
    loadWordsFromFile("words.txt", words);

    if (words.empty()) {
        std::cerr << "No words to play with. Exiting." << std::endl;
        return 1;
    }

    std::string wordToGuess = chooseRandomWord(words);
    std::vector<bool> guessed(wordToGuess.length(), false);
    int incorrectGuesses = 0;
    const int maxIncorrectGuesses = 6;

    std::cout << "Welcome to Hangman!" << std::endl;

    while (incorrectGuesses < maxIncorrectGuesses && !isWordGuessed(guessed)) {
        std::cout << "Word to guess: ";
        displayCurrentProgress(wordToGuess, guessed);

        std::cout << "Enter a letter: ";
        char guess;
        std::cin >> guess;

        bool correctGuess = false;
        for (size_t i = 0; i < wordToGuess.length(); ++i) {
            if (wordToGuess[i] == guess) {
                guessed[i] = true;
                correctGuess = true;
            }
        }

        if (!correctGuess) {
            incorrectGuesses++;
            std::cout << "Incorrect guess! You have " << (maxIncorrectGuesses - incorrectGuesses) << " attempts left." << std::endl;
        }
    }

    if (isWordGuessed(guessed)) {
        std::cout << "Congratulations! You've guessed the word: " << wordToGuess << std::endl;
    }
    else {
        std::cout << "You've been hanged! The word was: " << wordToGuess << std::endl;
    }

    return 0;
}
