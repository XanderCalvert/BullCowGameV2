#include <iostream>
#include <string>
#include "main.h"

void PrintIntro();
std::string GetGuessAndPrintBack();

// entry point for app
int main() {

	PrintIntro();
	GetGuessAndPrintBack();

	return 0;
}

void PrintIntro() {
	// introduce the game
	constexpr int WORD_LENGTH = 6;
	std::cout << "Wellcome to Bulls and Cows, a fun word game" << std::endl;
	std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I am thinking of?" << std::endl << std::endl;
	return;
}

std::string GetGuessAndPrintBack() {
	// get guess from the player
	std::string Guess = "";
	std::cout << "What is your guess? ";
	std::getline(std::cin, Guess);

	// repeat the guess back to them
	std::cout << "You guessed the word: " << Guess << std::endl;
	return Guess;
}

//notice me