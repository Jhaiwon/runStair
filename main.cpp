#include <iostream>
#include <stdio.h>
using namespace std;

class Player
{
    int level;
    char keyboard_;

public:
    int run();
    int moveLeft();
    int moveRight();
};

int Player::run()
{
    if (keyboard_ = 'a')
    {
        system("cls");
        moveLeft();
    }
    else if (keyboard_ = 'd')
    {
        system("cls");
        moveRight();
    }
    return 0;
}

int Player::moveLeft()
{
    cout<<"왼쪽입니다."<<endl;
    return 0;
}

int Player::moveRight()
{
    cout<<"오른쪽입니다."<<endl;
    return 0;
}

int main()
{
    Player Pl;
    Pl.run();
}
