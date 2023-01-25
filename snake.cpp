#include <iostream>
#include <conio.h>
#include <windows.h>

/*Calling them here so we can use them after main*/
void drawinterface(int x, int y, int width, int height, int fruitX, int fruitY, int score);
bool gamelogic(int &x, int &y, int &width, int &height, int &fruitX, int &fruitY, int &score);

int main()
{
    /*Init of variables*/
    int x = 10, y = 10, width = 30, height = 25, fruitX = rand() % width, fruitY = rand() % height, score = 0;
    bool yt = false;

    system("CLS"); // Clean screen
    drawinterface(x, y, width, height, fruitX, fruitY, score);
    while (!gamelogic(x, y, width, height, fruitX, fruitY, score))
    {
        drawinterface(x, y, width, height, fruitX, fruitY, score);
    }
    return 0;
}

/*Function to display whole interface(border and score)*/
void drawinterface(int x, int y, int width, int height, int fruitX, int fruitY, int score)
{
    system("CLS"); // Clean screen
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /*Spawn snake on x,y coordinates*/
            if (i == y && j == x)
            {
                std::cout << '&';
                continue;
            }
            /*Spawn fruit on fruitX,fruitY coordinates*/
            if (i == fruitY && j == fruitX)
            {
                std::cout << '#';
                continue;
            }
            /*Left border*/
            if (j % width == 0)
            {
                std::cout << (char)179;
            }
            /*Right border*/
            else if (j == 29)
            {
                std::cout << (char)179;
            }
            /*Top border*/
            else if (i % height == 0)
            {
                std::cout << (char)196;
            }
            /*Bottom border*/
            else if (i == 24)
            {
                std::cout << (char)196;
            }
            else
            {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
    /*Displaying player's score*/
    std::cout << std::endl;
    std::cout << "Score: " << score << std::endl;
}

/*Whole gamelogic responsible for movement and logic of the game*/
bool gamelogic(int &x, int &y, int &width, int &height, int &fruitX, int &fruitY, int &score)
{
    char key = getch();
    switch (key)
    {
    case 'q': // Q - Quit Game

        system("CLS"); // Clean screen
        std::cout << "Are you sure you want to quit the game? \n Y - yes N - no \n";
        key = getch();
        switch (key)
        {
        case 'y': // Closing game if pressed y key
            system("CLS");
            std::cout << "Thanks for playing snake!";
            return true;

        case 'n': // Closing game if pressed n key
            system("CLS");
            return false;

        default: // If we pick incorrect key we're just returing to game
            system("CLS");
            return false;
        }
        break;

        /*Movement*/
    case 'w': // W- UP
        y--;
        break;
    case 'a': // A - LEFT
        x--;
        break;
    case 's': // S - DOWN
        y++;
        break;
    case 'd': // D- RIGHT
        x++;
        break;
    }

    /*If snake touch border endgame*/
    if (x == width - 1 || x < 1 || y == height - 1 || y < 1)
    {
        system("CLS");
        std::cout << "Game Over!\nScore: " << score;
        return true;
    }

    /*If x,y cordinates of snake equals fruit x,y then fruit changing its position and our score is incremented*/
    if (x == fruitX && y == fruitY)
    {
        fruitX = rand() % 19;
        fruitY = rand() % 19;
        score++;
    }

    return false;
}