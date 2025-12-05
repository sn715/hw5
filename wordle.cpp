#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void findWords(size_t index, string current, string remFloat, const std::set<std::string>& dict, std::set<std::string>& results);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  // Add your code here
	std::set<std::string> results;

	findWords(0, in, floating, dict, results);

	return results;
}

// Define any helper functions here

void findWords(size_t index, string current, string remFloat, const std::set<std::string>& dict, std::set<std::string>& results) {

	//base
	if (index == current.length()) {

		if (remFloat.length() == 0 && dict.find(current) != dict.end()) {
			results.insert(current);
		}

		return;
	}
	//recursive

	size_t remBlanks = 0;

	for (size_t i = 0; i < current.length(); i++) {
		if (current[i] == '-') {
			remBlanks++;
		}
	}

	if (remFloat.length() > remBlanks) {
		return; 
	}

	else {
		//case 1: pos has a set letter
		if (current[index] != '-') {
			findWords(index + 1, current, remFloat, dict, results);
		}

		//case 2: pos is '-' 
		else{
		
			for (char c = 'a'; c <= 'z'; c++) {
				std::string updated = current;
				updated[index] = c;

				std::string updatedRem = remFloat;
				for (size_t i = 0; i < updatedRem.length(); i++) {
					if (c == updatedRem[i]) {
						updatedRem.erase(i, 1);
						break;
					}
				}

				findWords(index + 1, updated, updatedRem, dict, results);
			}
		}
	}
}
