/* This is the console executable, that makes us of the BullCowGame Class
This acts as the view in a MVC patternm, and is responsible for all
user interaction. For the game logic see the FBullCowGame class.*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FText = std::string;
using int32 = int;

void printIntro();
void playGame();
FText GetValidGuess();
bool askToPlayAgain();
void printGameSummary();

FBullCowGame BCGame; // Instantitate a new game

// Entry Point
int main() {
	bool bPlayAgain = 0;
	do {
		printIntro();
		playGame();
		bPlayAgain = askToPlayAgain();
	} while (bPlayAgain);


	return 0;
}

// Game introduction
void printIntro() {
	std::cout << "\n\n Welcome to Bulls and Cows - a fun word guessing game!\n";
	std::cout << std::endl;
	std::cout << " ((...))     ((...))     ((...))     ((...)) " << std::endl;
	std::cout << " ( o o )     ( o o )     ( o o )     ( o o ) " << std::endl;
	std::cout << "  \\   /       \\   /       \\   /       \\   /  " << std::endl;
	std::cout << "  ('_')       ('_')       ('_')       ('_')  " << std::endl;
	std::cout << std::endl;
	std::cout << " There is a secret word. The game is to guess the secret word.\n";
	std::cout << " Make a guess by typing on the keyboard and pressing enter.\n";
	std::cout << " A correct letter in the correct place is called a bull,\n";
	std::cout << " while a correct letter in the wrong place is called a cow.\n";
	std::cout << " After every guess, the game tells you how many bulls and cows were in the last guess.\n";
	std::cout << " You have to figure out the secret word in less than " << BCGame.GetMaxTries() << " guesses.\n";
	std::cout << std::endl;
	std::cout << " An isogram is a word with NO repeating letters. \n";
	std::cout << " Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram?\n";
	std::cout << std::endl;
	return;
}

void playGame() {
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries();

	// Loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();



		// Submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// Print number of Bulls and Cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	printGameSummary();

	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// Get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try: " << CurrentTry << " of " << BCGame.GetMaxTries() << ".  What is your guess? ";
		std::getline(std::cin, Guess);

		// Check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please eneter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please eneter all lowercase letters.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please eneter a word without repeating letters.\n\n";
			break;
		default:
			// Assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::Ok); // Keep looping until no errors
	return Guess;
}

bool askToPlayAgain() {
	std::cout << "Do you want to play again with the same hidden word? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void printGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else {
		std::cout << "Better luck next time\n";
	}
}