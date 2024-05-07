#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Função para validar a entrada do usuário
bool isInputValid(const string& input) {
    return input.size() == 5 && count_if(input.begin(), input.end(), [](char c) { return isupper(c); }) == 5;
}

// Função para processar a saída
string processOutput(const string& guess, const string& key, string& missedLetters) {
    string result;

    for (size_t i = 0; i < key.size(); ++i) {
        if (guess[i] == key[i]) {
            result += toupper(guess[i]);
        } else if (key.find(guess[i]) != string::npos) {
            result += tolower(guess[i]);
        } else {
            result += '*';
            if (missedLetters.find(guess[i]) == string::npos) {
                missedLetters += guess[i];
            }
        }
    }

    if (!missedLetters.empty()) {
        result += " (" + missedLetters + ")";
    }

    return result;
}

int main() {
    ifstream file("palavras.txt");
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo de palavras." << endl;
        return 1;
    }

    int numWords;
    file >> numWords;
    vector<string> wordList(numWords);
    for (int i = 0; i < numWords; ++i) {
        file >> wordList[i];
    }
    file.close();

    int wordIndex;
    cout << "";
    cin >> wordIndex;
    if (wordIndex < 1 || wordIndex > numWords) {
        cerr << "Seleção inválida." << endl;
        return 1;
    }

    string keyWord = wordList[wordIndex - 1];

    string missedLetters;
    for (int attempt = 0; attempt < 5; ++attempt) {
        string guess;
        cout << "";
        cin >> guess;

        if (!isInputValid(guess)) {
            cerr << "Entrada inválida. Por favor, tente novamente." << endl;
            --attempt; // Re-tentar a mesma tentativa
            continue;
        }

        string output = processOutput(guess, keyWord, missedLetters);
        cout << output << endl;

        if (output.find('*') == string::npos) {
            cout << "GANHOU!" << endl;
            return 0;
        }
    }

    cout << "PERDEU! " << keyWord << endl;
    return 0;
}


