#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset() {

	const FString hiddenWord = "planet"; // this MUST be an isogram
	MyHiddenWord = hiddenWord;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	// if guess isn't isogram
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
		// if the guess isn't all lowercase
	}
	else if (!IsLowercase(Guess)) {
		return EGuessStatus::Not_Lowercase;
		// if the guess length is wrong
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
		//otherwise
	}
	else {
		return EGuessStatus::Ok;
	}
}

bool FBullCowGame::IsLowercase(FString Word) const {
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			// if not a lowercase letter
			return false;
		}
	}
	return true;
}

// receives valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming the same length as guess

	// loop through all letters in Hidden Word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the Guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// If match
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++; // Incriment Bulls in the same place
				}
				else {
					BullCowCount.Cows++; // Incriment Cows if not
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	// treat 0 & 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	// setup map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) { // for all letters of the word
		Letter = tolower(Letter); // handle mixed case
	// loop through all letters
		if (LetterSeen[Letter]) {
			return false; // we do not have an isogram at this stage
		}
		else {
			LetterSeen[Letter] = true; // we do not have an isogram
		}

		// otherwise
			//add the letter to the map as seen
	}
	return true; // for example when \0 is entered
}

