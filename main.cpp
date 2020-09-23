/* This is the concosle executable that mnakes use of the BullCowClass
This acts as the view in the MVC pattern and is responsible for all
user interaction. For game logic see the FBullCowGame Class */

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

// entry point for app
int main() {
	do {
		std::cout << std::endl;
		PrintIntro();

		// loop for the number of turns asking for guesses
		PlayGame();



	} while (AskToPlayAgain());
	return 0; // exit application
}

void PrintIntro() {
	// introduce the game
	std::cout << "Wellcome to Bulls and Cows, a fun word game" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I am thinking of?" << std::endl << std::endl;
	return;
}

void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	for (int32 count = 0; count <= MaxTries; count++) {
		FText Guess = GetGuess();

		FBullCowCount BullCowCount =  BCGame.SubmitGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows = " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;
	}
	// TODO add game summary
};

FText GetGuess() {
	int32 CurrentTry = BCGame.GetCurrentTry();
	// get guess from the player
	FText Guess = "";
	std::cout << "Try " << CurrentTry << ". What is your guess? ";
	std::getline(std::cin, Guess);
	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
};