#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include <vector>
#include "dict-eng.h"
using namespace std;

bool validFloats(string word, string flts) {
  for (char a: flts) {
    bool found = false;
    for (char b: word) {
      if (a == b) {
        found = true;
        break;
      }
    }
    if (!found) {
      return false;
    }
  }
  return true;
}

bool isWord(string word, const std::set<std::string>& dict) {
  std::set<std::string>::iterator itr;
  itr = dict.find(word);

  if (itr != dict.end()) {
    return true;
  }

  return false;
}

int calcRemainSpots(const string& in) {
  int cnt = 0;
  for (int i = 0; i < in.size(); i ++) {
    if (in[i] == '-') {
      cnt++;
    }
  }
  return cnt;
}

void recurseHelper2(int n, string word, const string& in, const string& floating, string flts, std::set<std::string>& matched, const std::set<std::string>& dict, int lim, int i);

void recurseHelper(int n, string word, const string& in, const string& floating, string flts, std::set<std::string> matched, const std::set<std::string>& dict, int i); 

std::set<std::string> recurse(int n, string word, const string& in, const string& floating, string flts, std::set<std::string> matched, const std::set<std::string>& dict);

void recurseHelper2(int n, string word, const string& in, const string& floating, string flts, string flts_copy, std::set<std::string>& matched, const std::set<std::string>& dict, int lim, int i) {
  if (i < lim) {
    word[word.size() - n] = i;
    flts = flts_copy;

    int j = flts.find(i);
    if (j != string::npos) {
      flts.erase(j, 1);
    }

    std::set<std::string> newSet = recurse(n - 1, word, in, floating, flts, matched, dict);
    matched.insert(newSet.begin(), newSet.end());

    i++;
    recurseHelper2(n, word, in, floating, flts, flts_copy, matched, dict, lim, i);
  }
}

void recurseHelper(int n, string word, const string& in, const string& floating, string flts, std::set<std::string>& matched, const std::set<std::string>& dict, int lim, int i) {
  if (i < lim) {
    word[word.size() - n] = flts[i];
    std::set<std::string> newSet = recurse(n - 1, word, in, floating, flts.substr(0,i) + flts.substr(i+1), matched, dict);
    matched.insert(newSet.begin(), newSet.end());
    i++;
    recurseHelper(n, word, in, floating, flts, matched, dict, lim, i);
  }
}

// return a set of all the possible combos
std::set<std::string> recurse(int n, string word, const string& in, const string& floating, string flts, std::set<std::string> matched, const std::set<std::string>& dict) {
  // check if it has valid floats
  if (n == 0) {
      // cout << word << endl;
    if (validFloats(word, floating) && isWord(word, dict)) {
      matched.insert(word);
    }
    return matched;
  }

  if (word[word.size() - n] == '-') {
    int remainSpots = calcRemainSpots(word);
    if (remainSpots > flts.size()) {
      string flts_copy = flts;
      recurseHelper2(n, word, in, floating, flts, flts_copy, matched, dict, 123, 97);
      /* for (int i = 97; i < 123; i++) {
        word[word.size() - n] = i;
        flts = flts_copy;

        int j = flts.find(i);
        if (j != string::npos) {
          flts.erase(j, 1);
        }

        std::set<std::string> newSet = recurse(n - 1, word, in, floating, flts, matched, dict);
        matched.insert(newSet.begin(), newSet.end());
      } */
    } else if (remainSpots == flts.size()) {
      recurseHelper(n, word, in, floating, flts, matched, dict, flts.size(), 0);
    }
  } else {
    std::set<std::string> newSet = recurse(n - 1, word, in, floating, flts, matched, dict);
    matched.insert(newSet.begin(), newSet.end());
  }

  return matched;
}



// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  
  string word = in;

  std::set<std::string> matched;

  string flts = floating;
  std::set<std::string> words = recurse(word.size(), word, in, floating, flts, matched, dict);
  return words;
}

// Define any helper functions here
