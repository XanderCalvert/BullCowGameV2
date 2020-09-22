#include <iostream>
#include <string>
#include "main.h"

void PrintIntro();
void PlayGame();
std::string GetGuess();

// entry point for app
int main() {

	PrintIntro();

	// loop for the number of turns asking for guesses
	PlayGame();

	return 0; // exit application
}

void PrintIntro() {
	// introduce the game
	constexpr int WORD_LENGTH = 5;
	std::cout << "Wellcome to Bulls and Cows, a fun word game" << std::endl;
	std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I am thinking of?" << std::endl << std::endl;
	return;
}

void PlayGame() {
	constexpr int NUMBER_OF_TURNS = 4;
	for (int count = 0; count <= NUMBER_OF_TURNS; count++) {
		std::string Guess = GetGuess();
		std::cout << "You guessed the word: " << Guess << std::endl << std::endl;
	}
};



std::string GetGuess() {
	// get guess from the player
	std::string Guess = "";
	std::cout << "What is your guess? ";
	std::getline(std::cin, Guess);
	return Guess;
}