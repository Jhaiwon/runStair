#include <iostream>
#include <stdio.h>
#include <chrono>
#include <termio.h>
#include <random>
using namespace std;

int ConCase = 0;
int Match = 0;

class Player
{public:

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
    int screenCommand();
};

//키보드 버퍼를 받는 함수
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
    int KeyCase = 0;
    screenCommand();
    keyboard_ = getch();

    //오른쪽 왼쪽 값을 KeyCase에 반환
    if (keyboard_ == 'a' || keyboard_ == 'A')
    {
        KeyCase = 5;
    }
    else if (keyboard_ == 'd' || keyboard_ == 'D')
    {
        KeyCase = 6;
    }


    //키보드 버퍼와 랜덤 값의 비교
    if ((KeyCase == 5 && Match == 7)|| (KeyCase == 6 && Match == 8))
    {
        if (KeyCase==5)
        {
            system("clear");
            moveLeft();

        }
        if (KeyCase == 6)
        {
            system("clear");
            moveRight();
        }
        
    }
    else if((KeyCase != 5 && Match == 7) || (KeyCase != 6 && Match == 8))
    {
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
    cout << "오른쪽입니다." << endl;
    level++;
    run();
}

void Player:: gameover()
{
    if (print == 0)
    {
        cout << endl;
        cout << "게임오버! 당신은 " << level << "계단에서 죽었습니다." << endl;
        cout << "게임플레이 시간 :" << level << "초" << endl;
        print++;
    }
    exit;
}

char command(char LEFT,char RIGHT, char left, char right) {
    
    char 
    randomChar = rand() % 4;
    switch (randomChar)
    {
    case 0:
        ConCase = 1;//A
        return LEFT;
        break;
    case 1:
        ConCase = 2;//D
        return RIGHT;
        break;
    case 2:
        ConCase = 3;//a
        return left;
        break;
    case 3:
        ConCase = 4;//d
        return right;
        break;
    default:
        break;
    }

    return ConCase;
}
int Player:: screenCommand() {
    srand(time(0));

    char LEFT = 'A';
    char RIGHT = 'D';
    char left = 'a';
    char right = 'd';

    char random = command(LEFT, RIGHT, left, right);

    if (ConCase==1||ConCase==3)
    {
        cout << "←" << endl;//A 혹은 a일 경우 왼쪽 화살표 출력
        Match = 7;

    }
    else if (ConCase==2||ConCase==4)
    {
        cout << "→" << endl;//d 혹은 D일경우 오른쪽 화살표 출력
        Match = 8;
    }
    return 0;
}

int main()
{
    Player Pl;
    Pl.run();
}
