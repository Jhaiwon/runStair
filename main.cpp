#include <iostream>
#include <stdio.h>
#include <chrono>
#include <termio.h>
#include <random>
#include <unistd.h>
#include <ctime>
#include "Dance.h"

using namespace std;

int ConCase = 0;
int Match = 0;
int KeyCase = 0;
bool buttonPressed = false;
bool gameplay = true;

class Player
{
public:
    int level = 0;
    int upstair = 0;
    char keyboard_;
    int controller;
    bool checkPoint = false;
    int randomChar;

public:
    int gamestart();
    void howToPlay();
    int run();
    void moveLeft();
    void moveRight();
    int screenCommand();
};

// 키보드 버퍼를 받는 함수
int getch(void)
{
    int ch;
    struct termios buf, save;
    tcgetattr(0, &save);
    buf = save;
    buf.c_lflag &= ~(ICANON | ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;
}

int Player::gamestart()
{
    char selectKey;

    cout << "" << endl;   // 제목
    cout << "1-" << endl; // 게임시작
    cout << "2-" << endl; // 게임설명
    cout << "3-" << endl; // 게임종료

    cin >> selectKey;

    if (selectKey == '1')
    {
        run();
    }

    if (selectKey == '2')
    {
        howToPlay();
    }

    if (selectKey == '3')
    {
        exit;
    }

    return 0;
}

void Player::howToPlay()
{
}

int Player::run()
{
    const int waitingTime = 3;
    screenCommand();

    chrono::steady_clock::time_point startTime = chrono::steady_clock::now();
    keyboard_ = getch();
    chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    double elapsed_time = elapsedSeconds.count();

    if (elapsed_time < waitingTime)
    {
        switch (keyboard_)
        {
        case 'a':
            KeyCase = 5;
            break;

        case 'A':
            KeyCase = 5;
            break;

        case 'd':

            KeyCase = 6;
            break;

        case 'D':
            KeyCase = 6;
            break;
        }

        if ((KeyCase == 5 && Match == 7) || (KeyCase == 6 && Match == 8))
        {
            if (KeyCase == 5)
            {
                system("clear");
                // leftDanceDraw();
                moveLeft();
            }
            if (KeyCase == 6)
            {
                system("clear");
                // rightDanceDraw();
                moveRight();
            }
        }
        else if (((KeyCase != 5 && Match == 7) || (KeyCase != 6 && Match == 8)))
        {

            if (checkPoint == false)
            {
                cout << endl;
                cout << "게임오버! 당신은 " << level << "계단에서 죽었습니다." << endl;
                // cout << "게임플레이 시간 :" << time << "초" << endl;
                checkPoint = true;
                exit;
            }
        }
    }
    else
    {
        if (checkPoint == false)
        {
            cout << endl;
            cout << "타임오버! 당신은 " << level << "계단에서 죽었습니다." << endl;
            // cout << "게임플레이 시간 :" << time << "초" << endl;
            checkPoint = true;
        }
    }

    return 0;
}

void Player::moveLeft()
{
    cout << "왼쪽입니다." << endl;
    level++;
    run();
}

void Player::moveRight()
{
    // rightDanceDraw();
    cout << "오른쪽입니다." << endl;
    level++;
    run();
}

char command(char LEFT, char RIGHT, char left, char right)
{

    char randomChar = rand() % 4;
    switch (randomChar)
    {
    case 0:
        ConCase = 1; // A
        return LEFT;
        break;
    case 1:
        ConCase = 2; // D
        return RIGHT;
        break;
    case 2:
        ConCase = 3; // a
        return left;
        break;
    case 3:
        ConCase = 4; // d
        return right;
        break;
    default:
        break;
    }

    return ConCase;
}
int Player::screenCommand()
{
    srand(time(0));

    char LEFT = 'A';
    char RIGHT = 'D';
    char left = 'a';
    char right = 'd';

    char random = command(LEFT, RIGHT, left, right);

    if (ConCase == 1 || ConCase == 3)
    {
        cout << "←" << endl; // A 혹은 a일 경우 왼쪽 화살표 출력
        Match = 7;
    }
    else if (ConCase == 2 || ConCase == 4)
    {
        cout << "→" << endl; // d 혹은 D일경우 오른쪽 화살표 출력
        Match = 8;
    }
    return 0;
}

int main()
{

    Player Pl;
    Pl.gamestart();
}
