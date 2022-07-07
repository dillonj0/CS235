#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <map>
#include <time.h>
using namespace std;
// Created by Dillon Jensen on 06/JUL/2022

void FileToSetAndVector(string fileName, vector <string> &tokens, set <string> &unique);
void WriteSetToFile(string fileName, set <string> unique);
void WriteVectorToFile(string fileName, vector <string> tokens);
void VectorToMap(vector <string> tokens, map <string, vector <string> > &wordMap);
void WriteMapToFile(string fileName, map <string, vector <string> > wordMap);
void GeneratePredictedWords(int wordCount, map <string, vector <string> > wordMap, string startWord);

int main(int argc, char *argv[]) {
    string fileName = argv[1];
    string predictionStartsWith;
    int numWords;

    ////************** PROGRAM SETUP ****************
    cout << endl;
    if(argv[2]) {
        predictionStartsWith = argv[2];
    } else{
        cout << "*** No startWord argument. Using text file start as default. ***" << endl;
        predictionStartsWith = "";
    }
    if(argv[2] && argv[3]) {
        numWords = stoi(argv[3]);
    } else{
        cout << "*** No numWords argument. Using default of 100. ***" << endl;
        numWords = 100;
    }
    cout << "BEGINNING PROCESS... " << endl;
    ////************* END PROGRAM SETUP **************

    vector <string> tokens;     // All the words in order
    set <string> unique;        // Only keeps the new words
    map <string, vector <string> >wordMap;



    FileToSetAndVector(fileName, tokens, unique);

    WriteSetToFile(fileName, unique);
    WriteVectorToFile(fileName, tokens);

    VectorToMap(tokens, wordMap);
    WriteMapToFile(fileName, wordMap);

    GeneratePredictedWords(numWords, wordMap, predictionStartsWith);

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

void VectorToMap(vector <string> tokens, map <string, vector <string> > &wordMap){
    cout << "Writing vector to map." << endl;
    cout << "..." << endl;

    string last = "";
    for (int i = 0; i < tokens.size(); i++){
        wordMap[last].push_back(tokens.at(i));
        last = tokens.at(i);
    }
}

void WriteMapToFile(string fileName, map <string, vector <string> > wordMap){
    cout << "Writing map to file \"" << fileName << "_map.txt\"" << endl;
//    cout << "..." << endl;

    string newFileName = fileName + "_map.txt";

    ofstream outFile(newFileName);
    map<string, vector <string> >::iterator i;
    for (i = wordMap.begin(); i != wordMap.end(); i++) {
        //"key, value\n"
        outFile << i->first << ", ";
        for (int j = 0; j < i->second.size(); j++){
            outFile << i->second.at(j) << ", ";
        }
        outFile << endl;
    }
}

void GeneratePredictedWords(int wordCount, map <string, vector <string> > wordMap, string startWord){
    cout << endl;
    cout << "Generating " << wordCount << " words:" << endl;
    string state = startWord;
    if (startWord != "" && wordMap.count(startWord)!= 0) {
        cout << startWord << " ";
    }
    else{
        cout << "*** START WORD \"" << startWord << "\" NOT FOUND IN MAP. ***" << endl;
    }
    for (int i = 0; i < wordCount; i++) {
        srand (time(NULL)); //We don't want the output to be the same every time.
        int ind = rand() % wordMap[state].size();
        cout << wordMap[state][ind] << " ";      /////todo problematic
        state = wordMap[state][ind];             /////todo problematic
    }
    cout << endl;
}