#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <map>
#include <list>
#include <sstream>
//#include <time.h>
using namespace std;
// Created by Dillon Jensen on 06/JUL/2022

void FileToSetAndVector(string fileName, vector <string> &tokens, set <string> &unique);
void WriteSetToFile(string fileName, set <string> unique);
void WriteVectorToFile(string fileName, vector <string> tokens);
void VectorToMap(vector <string> tokens, map <list <string>,vector <string> > &wordMap,
                 int refCount);
void WriteMapToFile(string fileName, map <list <string>, vector <string> > wordMap);
void GeneratePredictedWords(int wordCount, map <list <string>, vector <string> > wordMap,
                            string startWord);

int main(int argc, char *argv[]) {
    string fileName = argv[1];
    string predictionStartsWith;    //The input key
    int numWords;                   //The number of words to be output based on the
                                    //   .txt file and the input key.
    int refCount = 1;               //The number of words in the input key

    ////************** PROGRAM SETUP ****************
    cout << endl;
    if(argv[2]) {
        predictionStartsWith = argv[2];
        // Also get the number of words in the input:
        for (int i = 0; i < predictionStartsWith.size(); i++){
            if (predictionStartsWith[i] == ' '){
                refCount++;
            }
        }
        cout << "*** Input string contains " << refCount << " words. ***" << endl;
    } else {
        cout << "*** No startWord argument. Using text file start as default. ***" << endl;
        predictionStartsWith = "";
    }
    if(argv[2] && argv[3]) {
        numWords = stoi(argv[3]);
    } else {
        cout << "*** No numWords argument. Using default of 100. ***" << endl;
        numWords = 100;
    }

    cout << "BEGINNING PROCESS... " << endl;
    ////************* END PROGRAM SETUP **************

    vector <string> tokens;     // All the words in order
    set <string> unique;        // Only keeps the new words
    map <list <string>, vector <string> >wordMap;



    FileToSetAndVector(fileName, tokens, unique);

    WriteSetToFile(fileName, unique);
    WriteVectorToFile(fileName, tokens);

    VectorToMap(tokens, wordMap, refCount);
    WriteMapToFile(fileName, wordMap);

    GeneratePredictedWords(numWords, wordMap, predictionStartsWith);

    cout << endl << "PROCESS COMPLETE." << endl;
    return 0;
}

void FileToSetAndVector(string fileName, vector <string> &tokens, set <string> &unique){
    cout << "Reading file \"" << fileName << "\" to vector & set." << endl;
    cout << "..." << endl;

    ifstream inFile;
    inFile.open (fileName);
    if(inFile.is_open()) {
        string token;
        while (inFile >> token) {
            string nopunct = "";
            for (auto &c: token) { // Reads the file and removes punctuation.
                if (isalpha(c)) {
                    nopunct += c;
                }
            }
            tokens.push_back(nopunct);
            unique.insert(nopunct);

        }

        cout << "Number of words " << tokens.size() << endl;
        cout << "Number of unique words " << unique.size() << endl;

        cout << endl;
    }
    else{
        cout << "Could not open file \"" << fileName << "\"" << endl;
    }
    inFile.close();
}

void WriteSetToFile(string fileName, set <string> unique){
    cout << "Writing set to file \"" << fileName << "_set.txt\"" << endl;
//    cout << "..." << endl;

    string newFileName = fileName + "_set.txt";

    ofstream outFile(newFileName);
    for (set <string>::iterator it = unique.begin(); it != unique.end(); ++it) {
        outFile << " " << *it;
    }
//    for (int i = 0; i != tokens.size(); ++i) {
//        outFile << " " << tokens[i];
//    }
}

void WriteVectorToFile(string fileName, vector <string> tokens){
    cout << "Writing vector to file \"" << fileName << "_vector.txt\"" << endl;
//    cout << "..." << endl;

    string newFileName = fileName + "_vector.txt";

    ofstream outFile(newFileName);
    for (int i = 0; i != tokens.size(); ++i) {
        outFile << " " << tokens[i];
    }
}

void VectorToMap(vector <string> tokens, map <list <string>, vector <string> > &wordMap,
                 int refCount){
    cout << "Writing vector to map." << endl;
    cout << "..." << endl;

    list<string> state;
    for (int i = 0; i < refCount; i++){
        state.push_back("");
    }
    for (int i = 0; i < tokens.size(); i++){
        wordMap[state].push_back(tokens.at(i));
        state.push_back(tokens.at(i));
        state.pop_front();
    }
}

void WriteMapToFile(string fileName, map <list <string>, vector <string> > wordMap){
    cout << "Writing map to file \"" << fileName << "_map.txt\"" << endl;
//    cout << "..." << endl;

    string newFileName = fileName + "_map.txt";

    ofstream outFile(newFileName);
    map <list <string>, vector <string> >::iterator i;
    for (i = wordMap.begin(); i != wordMap.end(); i++) {
        //"key, value\n"
        list <string> temp = i->first;
        for (int j = 0; j < i->first.size(); j++){
            outFile << temp.front() << ", ";
            temp.pop_front();
        }
        outFile << "; ";
        for (int k = 0; k < i->second.size(); k++){
            outFile << i->second.at(k) << ", ";
        }
        outFile << endl;
    }
}

void GeneratePredictedWords(int wordCount, map <list <string>, vector <string> > wordMap,
                            string startWord){
    cout << endl;
    cout << "Generating " << wordCount << " words:" << endl;

    list <string> state;
    istringstream in(startWord);
    string input;
    while(in >> input){
        state.push_back(input);
    }

    if (startWord != "" && wordMap.count(state)!= 0) {
        cout << startWord << " ";
    }
    else{
        cout << "*** START PHRASE \"" << startWord << "\" NOT FOUND IN MAP. ***" << endl;
    }

    for (int i = 0; i < wordCount; i++) {
//        srand (time(0)); //We don't want the output to be the same every time.
        // ^^^^^ RANDOM JUST GETS IT STUCK IN A LOOP AGAIN SO I GUESS WE'LL SETTLE.
//        cout << wordMap[state].size() << " <<< wordMap size at " << startWord << endl;
        int ind = (rand() + time(NULL)) % wordMap[state].size();
        cout << wordMap[state][ind] << " ";
        state.push_back(wordMap[state][ind]);
        state.pop_front();
        if (i % 10 == 0){
            cout << endl; //line break after each 10 words
        }
    }
    cout << endl;
}