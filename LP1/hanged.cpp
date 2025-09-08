#include <iostream>
#include <string>
#include <cctype>
using namespace std;

static string dictionary[20] = {"CASA", "PERRO", "GATO", "SOL", "MESA", "COCHE", " PAN", " LIBRO", "FLOR", "MAR", "TREN", "SILLA", "RÍO", "MANO", "LUNA", "NIÑO", "PEZ", "CAMA", "LECHE", "BESO"};

string updateProgress(char letter, string word, string progress)
{

    for (int i = 0; i <= word.length(); i++)
    {
        if (word[i] == letter)
        {
            progress[i] = letter;
        }
    }
    cout << progress << endl;
    return progress;
}

bool IsLetterInWord(string word, char letter)
{
    return word.find(letter) != string::npos;
}

bool replay(string &randomWord, int &errors, string &progress)
{
    char replayInput;

    cout << "Desea jugar de nuevo(S/N):";
    cin >> replayInput;
    if (toupper(replayInput) == 'S')
    {
        errors = 0;
        randomWord = dictionary[rand() % 20];
        cout << "Palabra de " << randomWord.length() << endl;
        progress = string(randomWord.length(), '*');
        return true;
    }
    else
        return false;
}

int main()
{

    srand(time(0));
    string randomWord = dictionary[rand() % 2];
    cout << "Palabra de " << randomWord.length() << " letras" << endl;
    string progress(randomWord.length(), '*');
    char letter;
    int errors = 0;
    const int MAX_ERRORS = 6;
    while (true)
    {

        cout << "Ingrese una letra: ";
        cin >> letter;
        if (IsLetterInWord(randomWord, letter))
        {

            progress = updateProgress(letter, randomWord, progress);
            if (progress == randomWord)
            {
                bool canReplay = replay(randomWord, errors, progress);
                if (!canReplay)
                    break;
            }
        }
        else
        {

            errors++;

            if (errors >= MAX_ERRORS)
            {
                cout << "Perdiste, la palabra era: " << randomWord << endl;

                bool canReplay = replay(randomWord, errors, progress);
                if (!canReplay)
                    break;
            }

            cout << "Errores: " << errors << "/" << MAX_ERRORS << endl;
        }
    }
    cout << "Juego terminado";
    return 0;
}