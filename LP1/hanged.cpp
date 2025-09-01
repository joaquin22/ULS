#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool hanged(char letter, string word, string &wordFound, int &tries)
{

    cout << "Ingrese una letra: ";
    cin >> letter;
    bool has_occurences = false;
    for (int i = 0; i <= word.length(); i++)
    {
        if (word[i] == letter)
        {
            wordFound[i] = letter;
            has_occurences = true;
        }
    }

    if (!has_occurences)
    {
        tries++;
    }

    cout << wordFound << endl;

    if (word == wordFound)
    {
        return true;
    }

    return false;
}


int main()
{
    const unsigned int maxTries = 5;
    const string wordList[2] = {"hola", "adias"};
    string word = wordList[rand() % 2];
    cout << "Palabra de " << word.length() << " letras" << endl;
    string wordFound(word.length(), '*');
    char letter;
    char replayInput;
    int tries = 0;
    while (true)
    {
        bool find = hanged(letter, word, wordFound, tries);
        if (find)
        {
            cout << "Desea jugar de nuevo(S/N):";
            cin >> replayInput;
            if (toupper(replayInput) == 'S')
            {
                tries = 0;
                word = wordList[rand() % 2];
                cout << "Palabra de " << word.length() << endl;
                wordFound = string(word.length(), '*');
            }
            else if (toupper(replayInput) == 'N')
                break;
        }
        else
        {
            cout << "Te quedan " << maxTries - tries << " intentos" << endl;
            if (tries == maxTries)
            {
                cout << "Perdiste la palabra era " << word << endl;
                find = true;
            }
        }
    }

    cout << "Juego terminado";

    return 0;
}