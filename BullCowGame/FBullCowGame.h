/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once

#include <string>

// TODO FOR FUTURE: to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

// all values initializes to 0
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus // The "class" part basically puts this enum into its own scope, preventing it from being a global scope, thus eliminating naming conflicts
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
	public:
		FBullCowGame(); // constructor
		
		int32 GetMaxTries() const;
		int32 GetCurrentTry() const; // const after the method like this only works with class member functions, and disables the method from setting any other variable to some other value. the "const" must also be added to the definition of the method (FBullCowGame.cpp).
		int32 GetHiddenWordLength() const;
		bool IsGameWon() const;
		EGuessStatus CheckGuessValidity(FString) const; // TODO make a more rich return value.

		void Reset(); // TODO make a more rich return value.
		// counts bulls & cows, and increases try # assuming valid guess
		FBullCowCount SubmitValidGuess(FString);

	private:
		// see constructor for initialization
		int32 MyCurrentTry;
		int32 MyMaxTries;
		FString MyHiddenWord;
		bool bGameIsWon;

		bool IsIsogram(FString) const;
		bool IsLowercase(FString) const;
};