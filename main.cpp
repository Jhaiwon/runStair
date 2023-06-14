#include <iostream>
#include <stdio.h>
#include <chrono>
#include <termio.h>
#include <random>
using namespace std;

class Player
{
    int level = 0;
    int upstair = 0;
    char keyboard_;
    int controller;
    int print = 0;
    int randomChar;

public:
    int run();
    void moveLeft();
    void moveRight();
    void gameover();
    char command();
};

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

int Player::run()
{
    command();
    keyboard_ = getch();
    if (keyboard_ == 'a' || keyboard_ == 'A')
    {
        system("cls");
        moveLeft();
    }
    else if (keyboard_ == 'd' || keyboard_ == 'D')
    {

        system("cls");
        moveRight();
    }
    /*if (keyboard_ != controller)
    {
        gameover();
    }*/

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
    cout << "오른쪽입니다." << endl;
    level++;
    run();
}

void Player::gameover()
{
    if (print == 0)
    {
        cout << "게임오버! 당신은 " << level << "계단에서 죽었습니다." << endl;
        cout << "게임플레이 시간 :" << level << "초" << endl;
        print++;
    }
    exit;
}

char Player::command(){
    char LEFT='A';
    char RIGHT='D';
    char left='a';
    char right='d';

    randomChar = rand() % 4;
    switch (randomChar)
    {
    case 0:
        return LEFT;
        break;
    case 1:
        return RIGHT;
        break;
    case 2:
        return left;
        break;
    case 3:
        return right;
        break;
    default:
        gameover();
        break;
    }
       
       cout << randomChar<<endl;

    return 0;
}

int main()
{
    Player Pl;
    Pl.run();
}
