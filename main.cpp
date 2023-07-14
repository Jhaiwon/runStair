#include <iostream>
#include <stdio.h>
#include <chrono>
#include <termio.h>
#include <random>
#include <unistd.h>
#include <ctime>

using namespace std;

int selectCase = 0;
int Match = 0;
int KeyCase = 0;
bool buttonPressed = false;
bool gameplay = true;
chrono::steady_clock::time_point startTime;
bool Input = false;

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
    int gamescreen();
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
    Input = true;
    return ch;
}

int Player::gamescreen()
{
    char selectKey;

    cout << "무한 화살표" << endl; // 제목
    cout << endl;
    cout << "1-게임시작" << endl; // 게임시작
    cout << "2-게임설명" << endl; // 게임설명
    cout << "3-게임종료" << endl; // 게임종료

    selectKey = getch();

    if (selectKey == '1')
    {
        system("clear");
        gamestart();
    }

    if (selectKey == '2')
    {
        howToPlay();
    }

    if (selectKey == '3')
    {
        system("clear");
        cout << "게임을 종료합니다." << endl;
    }

    return 0;
}

void Player::howToPlay()
{
    bool collectKey = false;
    system("clear");
    cout << "게임설명 이러쿵저러쿵" << endl;
    cout << "이전 버튼 -b";
    int back;
    back = getch();

    while (back != 'b')
    {
        if (collectKey == false)
        {
            cout << endl;
            cout << "올바른 키가 아닙니다. 다시 입력해주세요." << endl;
            collectKey = true;
        }
        back = getch();
    }
    if (back == 'b')
    {
        system("clear");
        gamescreen();
    }
}

int Player::gamestart()
{
    Input = false;
    screenCommand();
    startTime = chrono::steady_clock::now();
    keyboard_ = getch();

    if (Input == true)
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
        Input = false;
        gameover();
    }
    if (upstair == 0)
    {
        if ((KeyCase == 5 && Match == 7) || (KeyCase == 6 && Match == 8))
        {
            Input = true;
        }
        else
            Input = false, gameover();

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

        /*if (Input == false)
        {
           gameplay = false;
            gameover();
        }*/}

        return 0;
    
}

void Player::moveLeft()
{
    cout << "왼쪽입니다." << endl;
    level++;
    gamestart();
}

void Player::moveRight()
{
    // rightDanceDraw();
    cout << "오른쪽입니다." << endl;
    level++;
    gamestart();
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
    if (upstair == 0)
    {
        chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedSeconds = endTime - startTime;
        double elapsed_time = elapsedSeconds.count();

        cout << endl;
        cout << "gameover~ " << level << "차례에서 죽었습니다." << endl;
        cout << "게임 플레이 시간: " << elapsed_time << endl;
        upstair = 1;
    }
}

int main()
{

    Player Pl;
    Pl.gamescreen();
}
