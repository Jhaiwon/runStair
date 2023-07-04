#include <iostream>
#include <stdio.h>
#include <chrono>
#include <termio.h>
#include <random>
#include <unistd.h>
#include <ctime>
#include "Dance.h"

using namespace std;

int selectCase = 0;
int Match = 0;
int KeyCase = 0;
bool buttonPressed = false;
bool gameplay=true; 

class Player
{
public:
    int level = 0;
    int upstair = 0;
    char keyboard_;
    int controller;
    int randomChar;

public:
    int gamestart();
    void howToPlay();
    int run();
    void moveLeft();
    void moveRight();
    int screenCommand();
    void gameover();
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

    cout << "무한 화살표" << endl;   // 제목
    cout <<endl;
    cout << "1-게임시작" << endl; // 게임시작
    cout << "2-게임설명" << endl; // 게임설명
    cout << "3-게임종료" << endl; // 게임종료

    selectKey = getch();

    if (selectKey == '1')
    {
        system("clear");
        run();
    }

    if (selectKey == '2')
    {
        howToPlay();
    }

    if (selectKey == '3')
    {
        system("clear");
        cout<<"게임을 종료합니다."<<endl;
        exit;
    }

    return 0;
}

void Player::howToPlay()
{
}

int Player::run()
{
    bool Input = false;
    
    const double waitingTime = 1.2;
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
    }
    else
    {
        Input=false;
       gameover();
    }

    if ((KeyCase == 5 && Match == 7) || (KeyCase == 6 && Match == 8))
    {
        Input = true;
    }
    else Input=false,gameover();

    while (Input == true)
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
        break;
    }
   

    if (Input == false)
    {
        gameplay=false;
        gameover();
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
        selectCase = 1; // A
        return LEFT;
        break;
    case 1:
        selectCase = 2; // D
        return RIGHT;
        break;
    case 2:
        selectCase = 3; // a
        return left;
        break;
    case 3:
        selectCase = 4; // d
        return right;
        break;
    default:
        break;
    }

    return selectCase;
}
int Player::screenCommand()
{
    srand(time(0));

    char LEFT = 'A';
    char RIGHT = 'D';
    char left = 'a';
    char right = 'd';

    char random = command(LEFT, RIGHT, left, right);

    if (selectCase == 1 || selectCase == 3)
    {
        cout << "←" << endl; // A 혹은 a일 경우 왼쪽 화살표 출력
        Match = 7;
    }
    else if (selectCase == 2 || selectCase == 4)
    {
        cout << "→" << endl; // d 혹은 D일경우 오른쪽 화살표 출력
        Match = 8;
    }
    return 0;
}

void Player::gameover()
{
    if(gameplay==false)
    {
        cout<<endl;
        cout<<"gameover~ "<<level<<"에서 죽었습니다."<<endl;
        gameplay=true;
    }

}

int main()
{

    Player Pl;
    Pl.gamestart();
}
