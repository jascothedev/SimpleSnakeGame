#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 40;
const int height = 20;
int x, y, baitX, baitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    baitX = rand() % width;
    baitY = rand() % height;
    score = 0;
}
void Draw()
{
    system("cls"); // Clear the console screen.
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O"; // Display the snake's head.
            else if (i == baitY && j == baitX)
                cout << "*"; // Display the bait.
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o"; // Display the snake's tail.
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl; // Display the player's score.
}
void Input()
{
    if (_kbhit()) // Check if a key pressed.
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 'x':
            gameOver = true; // Exit the game if 'x' is pressed.
            break;
        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;

    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x > width || x < 0 || y > height || y < 0)
        gameOver = true; // Check for collision with the game boundaries.
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y) // Check for collusion with the snake's tail.
            gameOver = true;
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        baitX = rand() % width;
        baitY = rand() % height;
        nTail++;
    }
}
int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(165); // Control the game speed.
    }
    return 0;
}



