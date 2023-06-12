#include <iostream>
#include <stdio.h>
#include <chrono>
using namespace std;

class Player
{
    int level;
    char keyboard_;

public:
    int run();
    void moveLeft();
    void moveRight();
};

int Player::run()
{ 
        cin>>keyboard_;
        if (keyboard_ =='a'||keyboard_=='A')
    {
        system("cls");
        moveLeft();
    }
    else if (keyboard_ =='d'||keyboard_=='D')
    {

        system("cls");
        moveRight();
    }
    return 0;
    
}

void Player::moveLeft()
{
    cout << "왼쪽입니다." << endl;
    run();
}

void Player::moveRight()
{
    cout << "오른쪽입니다." << endl;
    run();
}

int main()
{
    Player Pl;
    Pl.run();
}
