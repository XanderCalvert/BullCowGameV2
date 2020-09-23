#include "FBullCowGame.h"



int FBullCowGame::GetMaxTries() const { return MyMaxTries; }

int FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const {
	return false;
}

FBullCowGame::FBullCowGame() {
	Reset();
}

void FBullCowGame::Reset() {
	MyCurrentTry = 1;
	constexpr int MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = MAX_TRIES;
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

// receives valid guess and increments try
FBullCowCount FBullCowGame::SubmitGuess(FString Guess) {
	// increment turn 
	MyCurrentTry++;

	// setup return variable
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
	return BullCowCount;
}