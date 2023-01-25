#include <iostream>
#include <conio.h>
#include <windows.h>

void drawinterface(int x, int y);
bool controls(int *x, int *y);

int main()
{
    int fruitX, fruitY, score = 0;
    int x, y = 10;

    system("CLS"); // We're clearing the console so previous text won't interrupt with our game
    drawinterface(x, y);
    while (!controls(&x, &y))
    {
    }

    return 0;
}

void drawinterface(int x, int y)
{
    int width = 30;
    int height = 25;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j % width == 0) // left border
            {
                printf("%c", 179);
            }
            else if (j == 29) // right border
            {
                printf("%c", 179);
            }
            else if (i % height == 0) // top border
            {
                printf("%c", 196);
            }
            else if (i == 24) // bottom border
            {
                printf("%c", 196);
            }
            else
            {
                printf(" ");
            }

            if (i == y && j == x)
            {
                printf("@");
                continue;
            }
        }
        printf("\n");
    }
}

bool controls(int *x, int *y)
{
    char key = getch();
    switch (key)
    {
    case 'q': // "Q" key is used to exit the game
        // pauseGame(true); // make some function to pause the game eh?
        system("CLS");
        std::cout << "Are you sure you want to quit the game? \n Y - yes N - no \n";
        key = getch();
        switch (key)
        {
        case 'y':
            system("CLS");
            std::cout << "Thanks for playing snake!";
            return true;

        case 'n':
            system("CLS");
            return false;
        }
        break;

    case 'w':
        y++;
        break;
    case 'a':
        x--;
        break;
    case 's':
        y--;
        break;
    case 'd':
        x++;
        break;
    }
    return false;
}
