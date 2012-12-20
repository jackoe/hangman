#include <iostream>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;
/*
 
 
 Lower-level description:
 
 for (i < wordLength) {
 
 make a set bigSet with all words in the dictionary that have i instances of the guess
 divide this set into its subsets and find the largest of them.
 
 compare this subset to the runningBest by size
 
 }
 
 
 */





void PopulateDictionary(set<string> *dictionary) {
	std::ifstream myfile;
	myfile.open ("dictionary.txt");
	insert_iterator<set<string> > itr(*dictionary, dictionary->begin());
	copy(istream_iterator<string>(myfile), istream_iterator<string>(), itr);
	
	myfile.close();
	return;
}

string GetLine() {
	string result;
	getline(cin, result);
	
	return result;
}

int GetInteger() {
	stringstream converter;
	converter << GetLine();
	
	int result;
	converter >> result;
	
	if(converter.fail())
		cout << "Please enter an integer." << endl;
	else {
		char remaining;
		converter >> remaining;
		
		if(converter.fail())
			return result;
		else
			cout << "Unexpected character: " << remaining << endl;
		
	}
	return result;
}

string UpToLow(string str) {
	for (int i = 0; i < str.length(); i++) 
		if (str[i] >= 0x41 && str[i] <= 0x5A) 
			str[i] = str[i] + 0x20;
	return str;
}

void SizeifyDictionary(set<string> *dictionary, int wordLength) {
	set<string> *newDict = new set<string>;
	
	for (set<string>::iterator itr = dictionary -> begin();itr != dictionary -> end(); itr++)
		if (itr->length() == wordLength)
			newDict->insert(*itr);
	
	delete dictionary;
	dictionary = newDict;
	cout << dictionary->size();
	return;
}

bool StringContainsChar(string theString, char theChar) {
	for (size_t i = 0; i < theString.length(); i++)
		if (theString[i] == theChar)
			return true;
	
	return false;
}

bool PlayHangman(int &numGuesses, const string theWord, string wordInProgress, int wordLength, string &guessedChars){
	
	while (numGuesses>0) {
		cout << "\nEnter a guess: ";
		char guess = GetLine()[0]; //watch out for bad input
		
		if (StringContainsChar(guessedChars, guess)) {
			cout << "You already guessed this character.\n";
		} else {
			guessedChars += guess;
			for (size_t i = 0; i < theWord.length(); i++) {
				if (theWord[i] == guess) {
					numGuesses++;
					wordInProgress[i] = guess;
				}
			}
			
			if (wordInProgress == theWord) { // User wins game
				cout << "When this thing turn goes dynamic on you, that won't happen.\nNice job, though.\n" << theWord << endl;
				return true;
			}
			
			cout << wordInProgress;
			numGuesses--;
			
		}
	}
	
	return false;
}

int main (int argc, char * const argv[]) {
	cout<< "Welcome to hangman!\n\n";
	cout << "What length word do you want? ";
	int wordLength = GetInteger();
	string word = "qwerty";
	//cout << "how many guesses would you like?";
	int numGuesses = 4/* GetInteger()*/; 
	
	set<string> *dictionary = new set<string>;
	PopulateDictionary(dictionary);
	SizeifyDictionary(dictionary, wordLength);
	
	string guessedChars, wordInProgress;
	for (size_t i = 0; i < word.length(); i++)
		wordInProgress += '_';
	
	
	bool gameOutcome = PlayHangman(numGuesses, word, wordInProgress, wordLength, guessedChars);
	
	return 0;
}
