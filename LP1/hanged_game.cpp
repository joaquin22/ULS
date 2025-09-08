
#include <iostream>
#include <string>
#include <cctype>

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;

static string dictionary[20] = {"CASA", "PERRO", "GATO", "SOL", "MESA", "COCHE", " PAN", " LIBRO", "FLOR", "MAR", "TREN", "SILLA", "RÍO", "MANO", "LUNA", "NIÑO", "PEZ", "CAMA", "LECHE", "BESO"};

void drawGallow(sf::RenderWindow &window)
{
    sf::RectangleShape base(sf::Vector2f(160.f, 7.f));
    base.setPosition(80.f, 430.f);
    base.setFillColor(sf::Color(80, 80, 80));

    sf::RectangleShape stick(sf::Vector2f(7.f, 250.f));
    stick.setPosition(160.f, 180.f);
    stick.setFillColor(sf::Color(80, 80, 80));

    sf::RectangleShape arm(sf::Vector2f(140.f, 7.f));
    arm.setPosition(160.f, 180.f);
    arm.setFillColor(sf::Color(80, 80, 80));

    sf::RectangleShape rope(sf::Vector2f(7.f, 30.f));
    rope.setPosition(300.f, 180.f);
    rope.setFillColor(sf::Color(80, 80, 80));

    window.draw(base);
    window.draw(stick);
    window.draw(arm);
    window.draw(rope);
}

void drawBody(sf::RenderWindow &window, int error)
{
    if (error >= 1)
    {
        // HEAD
        sf::CircleShape head(28.f);
        head.setPosition(275.f, 210.f);
        head.setOutlineThickness(3.f);
        head.setFillColor(sf::Color::Transparent);
        head.setOutlineColor(sf::Color::Black);
        window.draw(head);
    }
    if (error >= 2)
    {
        // LEFT ARM
        sf::RectangleShape lArm(sf::Vector2f(60.f, 7.f));
        lArm.setPosition(250.f, 303.f);
        lArm.setFillColor(sf::Color(80, 80, 80));
        lArm.setRotation(-40.f);
        window.draw(lArm);
    }
    if (error >= 3)
    {
        // RIGHT ARM
        sf::RectangleShape RArm(sf::Vector2f(60.f, 7.f));
        RArm.setPosition(305.f, 265.f);
        RArm.setFillColor(sf::Color(80, 80, 80));
        RArm.setRotation(40.f);
        window.draw(RArm);
    }
    if (error >= 4)
    {
        // BODY
        sf::RectangleShape body(sf::Vector2f(7.f, 80.f));
        body.setPosition(300.f, 265.f);
        body.setFillColor(sf::Color(80, 80, 80));
        window.draw(body);
    }
    if (error >= 5)
    {
        // LEFT LEG
        sf::RectangleShape LLeg(sf::Vector2f(75.f, 7.f));
        LLeg.setPosition(247.f, 385.f);
        LLeg.setFillColor(sf::Color(80, 80, 80));
        LLeg.setRotation(-40.f);
        window.draw(LLeg);
    }
    if (error >= 6)
    {
        // RIGHT LEG
        sf::RectangleShape RLeg(sf::Vector2f(75.f, 7.f));
        RLeg.setPosition(305.f, 338.f);
        RLeg.setFillColor(sf::Color(80, 80, 80));
        RLeg.setRotation(40.f);
        window.draw(RLeg);
    }
}

string getRandomWord()
{
    srand(time(0));
    string word = dictionary[rand() % 20];
    return word;
}

string updateProgress(char letter, string randomWord, string progress)
{
    for (int i = 0; i <= randomWord.length(); i++)
    {
        if (randomWord[i] == letter)
        {
            progress[i] = letter;
        }
    }

    return progress;
}

bool IsLetterInWord(string word, char letter)
{
    return word.find(letter) != string::npos;
}

int main()
{

    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Juego del ahorcado");

    sf::Font font;
    font.loadFromFile("Roboto-Light.ttf");

    // UI TEXTS
    sf::Text txtProgress("", font, 30);
    txtProgress.setFillColor(sf::Color(80, 80, 80));
    txtProgress.setPosition(390.f, 250.f);

    sf::Text txtEnd("", font, 50);
    txtEnd.setFillColor(sf::Color(80, 80, 80));
    txtEnd.setPosition(390.f, 150.f);

    sf::Text txtWrongLetters("", font, 30);
    txtWrongLetters.setFillColor(sf::Color(80, 80, 80));
    txtWrongLetters.setPosition(390.f, 350.f);

    sf::Text txtTries("Errores: 0/6", font, 30);
    txtTries.setFillColor(sf::Color(80, 80, 80));
    txtTries.setPosition(390.f, 450.f);

    sf::Text txtReplay("", font, 30);
    txtReplay.setFillColor(sf::Color(80, 80, 80));
    txtReplay.setPosition(80.f, 550.f);

    string randomWord = getRandomWord();
    string progress(randomWord.length(), '_');

    txtProgress.setString("Palabra(" + to_string(randomWord.length()) + "):" + progress);

    int errorsCount = 0;
    bool finishGame = false;
    string wrongLetters;
    const int MAX_ERRORS = 6;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter && finishGame)
                {
                    errorsCount = 0;
                    randomWord = getRandomWord();
                    wrongLetters = "";
                    progress = string(randomWord.length(), '_');
                    finishGame = false;

                    txtProgress.setString("Palabra: " + progress);
                    txtWrongLetters.setString("");
                    txtTries.setString("Errores: " + to_string(errorsCount) + "/" + to_string(MAX_ERRORS));
                    txtEnd.setString("");
                    txtReplay.setString("");
                }
                else
                {

                    const sf::Keyboard::Key keycode = event.key.code;
                    if (keycode >= sf::Keyboard::A && keycode <= sf::Keyboard::Z && !finishGame)
                    {
                        char letter = static_cast<char>(keycode - sf::Keyboard::A + 'a'); // Equivalete a CIN
                        letter = toupper(letter);
                        if (IsLetterInWord(randomWord, letter))
                        {
                            progress = updateProgress(letter, randomWord, progress);
                            txtProgress.setString("Palabra: " + progress);
                            if (progress == randomWord)
                            {
                                finishGame = true;
                                txtEnd.setString("Ganaste");
                            }
                        }
                        else
                        {

                            if (!IsLetterInWord(wrongLetters, letter))
                            {
                                errorsCount++;
                                if (errorsCount >= MAX_ERRORS)
                                {
                                    finishGame = true;
                                    txtEnd.setString("Perdiste, era: " + randomWord);
                                }
                                wrongLetters.push_back(letter);
                                txtWrongLetters.setString(wrongLetters);
                                txtTries.setString("Errores: " + to_string(errorsCount) + "/" + to_string(MAX_ERRORS));
                            }
                        }

                        if (finishGame)
                        {
                            txtReplay.setString("Para jugar de nuevo presiona la tecla Enter");
                        }
                    }
                }
            }
        }

        window.clear(sf::Color(245, 245, 245));

        drawGallow(window);
        drawBody(window, errorsCount);
        window.draw(txtProgress);
        window.draw(txtEnd);
        window.draw(txtWrongLetters);
        window.draw(txtTries);
        window.draw(txtReplay);
        window.display();
    }
    return 0;
}