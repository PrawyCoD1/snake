#include <windows.h>
#include <algorithm>
#include <iostream>
#include <conio.h>
#include <random>
#include <vector>
#include <cstdlib>
#include <ctime>

const int GAME_H = 25;
const int GAME_W = 30;

struct Point
{
    int x, y;
};

enum Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};
Direction dir;

void antiflicker()
{
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

struct AppleContainer
{
    int apple_x;
    int apple_y;
    bool collected;
};

struct PositionContainer
{
    int head_x, head_y, seg_len, score = 0;
    std::vector<int> x_segments;
    std::vector<int> y_segments;
    std::vector<int> directions;
};

struct PositionContainer init_continer(int head_x, int head_y)
{
    struct PositionContainer new_container;
    new_container.head_x = head_x;
    new_container.head_y = head_y;
    new_container.seg_len = 0;
    return new_container;
}

void add_segment(PositionContainer &container, int seg_x, int seg_y, int direction)
{
    container.x_segments.push_back(seg_x);
    container.y_segments.push_back(seg_y);
    container.directions.push_back(direction);
    container.seg_len++;
}

bool drawinterface(PositionContainer container, AppleContainer apple_container);
bool gamelogic(PositionContainer &container, AppleContainer &apple_container);
void update_pos(PositionContainer &container);

int main()
{
    antiflicker();
    system("CLS");
    std::srand(std::time(0));
    PositionContainer snake_container = init_continer(15, 13);
    AppleContainer apple_container;
    apple_container.apple_x = -1;
    apple_container.apple_y = -1;
    apple_container.collected = true;
    drawinterface(snake_container, apple_container);
    while (true)
    {
        if (gamelogic(snake_container, apple_container))
        {
            break;
        }
        drawinterface(snake_container, apple_container);
        update_pos(snake_container);
    }
    return 0;
}
bool drawinterface(PositionContainer container, AppleContainer apple_container)
{
    antiflicker(); // Clean screen
    char printed_char;
    for (int i = 0; i < GAME_H; i++)
    {
        for (int j = 0; j < GAME_W; j++)
        {
            /*Spawn tail*/
            for (int seg_index = 0; seg_index < container.seg_len; seg_index++)
            {
                if (container.x_segments[seg_index] == j && container.y_segments[seg_index] == i)
                {
                    std::cout << 'o';
                    j++;
                }
            }
            /*Spawn snake on x,y coordinates*/
            if (i == container.head_y && j == container.head_x)
            {
                std::cout << '&';
                continue;
            }
            else if (i == apple_container.apple_x && j == apple_container.apple_y && apple_container.collected == false)
            {
                std::cout << '#';
                continue;
            }
            /*Left Borer*/
            else if (j % GAME_W == 0)
            {
                printed_char = 179;
            }
            /*Right border*/
            else if (j == 29)
            {
                printed_char = 179;
            }
            /*Top border*/
            else if (i % GAME_H == 0)
            {
                printed_char = 196;
            }
            /*Bottom border*/
            else if (i == 24)
            {
                printed_char = 196;
            }
            else
            {
                printed_char = ' ';
            }
            std::cout << printed_char;
        }
        std::cout << '\n';
    }

    // Display player's score
    std::cout << std::endl;
    std::cout << "Score: " << container.score << std::endl;

    return false;
}

bool gamelogic(PositionContainer &snake_container, AppleContainer &apple_container)
{
    /*Controls*/
    switch (getch())
    {
    case 'q':
        system("CLS");
        std::cout << "Are you sure you want to quit the game? \n Y - yes N - no \n";
        switch (getch())
        {
        case 'y':
            system("CLS");
            std::cout << "Thanks for playing snake!";
            return true;
        default:
            system("CLS");
            return false;
        }
    case 72: // UP
        dir = UP;
        if (dir != DOWN)
        {
            snake_container.head_y--;
        }
        break;
    case 75: // LEFT
        dir = LEFT;
        if (dir != RIGHT)
        {
            snake_container.head_x--;
        }
        break;
    case 80: // DOWN
        dir = DOWN;
        if (dir != UP)
        {
            snake_container.head_y++;
        }
        break;
    case 77: // RIGHT
        dir = RIGHT;
        if (dir != LEFT)
        {
            snake_container.head_x++;
        }
        break;
    }
    /*Spawn apple on random x,y*/
    if (apple_container.collected)
    {
        std::vector<Point> apple_space;
        for (int y = 0, y_pos; y < GAME_H - 4; y++)
        {
            y_pos = y + 1;
            for (int x = 0, x_pos; x < GAME_W - 7; x++)
            {
                x_pos = x + 1;
                if (
                    std::find(snake_container.x_segments.begin(), snake_container.x_segments.end(), x_pos) == snake_container.x_segments.end() &&
                    std::find(snake_container.y_segments.begin(), snake_container.y_segments.end(), y_pos) == snake_container.y_segments.end() &&
                    y_pos != snake_container.head_y &&
                    x_pos != snake_container.head_x)
                {
                    Point free_point;
                    free_point.x = x_pos;
                    free_point.y = y_pos;
                    apple_space.push_back(free_point);
                }
            }
        }
        int random_point_index = std::rand() % apple_space.size();
        Point random_point = apple_space[random_point_index];
        apple_container.apple_x = random_point.x;
        apple_container.apple_y = random_point.y;
        std::cout << "x:" << apple_container.apple_x;
        std::cout << "y:" << apple_container.apple_y;
        apple_container.collected = false;
    }
    else if (apple_container.apple_x == snake_container.head_y && apple_container.apple_y == snake_container.head_x)
    {
        apple_container.collected = true;
        snake_container.score++;
        int x, y, new_dir;
        if (snake_container.seg_len == 0)
        {
            x = snake_container.head_x;
            y = snake_container.head_y;
            new_dir = dir;
        }
        else
        {
            x = snake_container.x_segments.back();
            y = snake_container.y_segments.back();
            new_dir = snake_container.directions.back();
        }
        switch (new_dir)
        {
        case UP:
            y++;
            break;
        case DOWN:
            y--;
            break;
        case LEFT:
            x++;
            break;
        case RIGHT:
            x--;
            break;
        }
        add_segment(snake_container, x, y, new_dir);
    }
    /*GAMEOVER*/
    if (snake_container.head_x >= GAME_W - 1 || snake_container.head_y >= GAME_H - 1 || snake_container.head_x <= 0 || snake_container.head_y <= 0)
    {
        system("CLS");
        std::cout << "GameOver\n";
        return true;
    }

    return false;
}

/*Update tail's position*/
void update_pos(PositionContainer &snake_container)
{
    if (snake_container.seg_len > 0)
    {
        int x, y, n_dir;
        for (int i = snake_container.seg_len - 1; i > 0; i--)
        {
            x = snake_container.x_segments[i - 1];
            y = snake_container.y_segments[i - 1];
            n_dir = snake_container.directions[i - 1];
            snake_container.x_segments[i] = x;
            snake_container.y_segments[i] = y;
            snake_container.directions[i] = n_dir;
        }
        x = snake_container.head_x;
        y = snake_container.head_y;
        n_dir = dir;
        snake_container.x_segments[0] = snake_container.head_x;
        snake_container.y_segments[0] = snake_container.head_y;
        snake_container.directions[0] = n_dir;
    }
}