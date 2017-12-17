#pragma once
#include <string>

using int32 = int;
using FString = std::string;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessWordStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Contains_Special
};

class FBullCowGame
{
public:
	FBullCowGame(); // Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessWordStatus CheckGuessValidity(FString) const;

	void Reset(); // TODO make a more rich return value
	FBullCowCount SubmitValidGuess(FString);



// Please ignore private for now
private:
	// Initialised in constructor
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};