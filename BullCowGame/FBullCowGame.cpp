#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map // TODO FOR FUTURE: to make syntax Unreal friendly

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const {	return MyCurrentTry; }
// const after the method like this only works with class member functions, and disables the method from setting any other variable to 
// some other value. the "const" must also be added to the definition of the method (FBullCowGame.h).
// MyCurrentTry = 12; <--- this is the kind of thing the const does not allow for
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,8}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	//constexpr int32 MAX_TRIES = 8;
	//MyMaxTries = MAX_TRIES;
	// we don't need these MAX_TRIES stuff any more because we are now determining the amount of tries based on the hidden word length
	
	const FString HIDDEN_WORD = "planet"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if the guess ins't an isogram
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	// if the guess isnt all lower case
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase; // TODO write function
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	// otherwise
	else
	{
		return EGuessStatus::OK;
	}
	
	return EGuessStatus::OK; // TODO make actual error
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming the same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// compare letter against the hidden word
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
					// increment bulls if they're in the same place
				}
				else
				{
					BullCowCount.Cows++;
					// increment cows if not
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map
	// loop through all the letters of the word
	for (auto Letter : Word) // for all letters of the word (: means in)
	{
		Letter = tolower(Letter); // handle mixed case
		// if the letter is already in the map
		if (LetterSeen[Letter]) { return false; } // we do NOT have an isogram
		// otherwise
		else { LetterSeen[Letter] = true; } // add the letter to the map as seen (i guess this is kind of like a dictionary in Python?
	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		if (!islower(Letter)) { return false; }
	}

	return true; // for example in cases where /0 is entered
}
