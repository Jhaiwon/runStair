#include <iostream>
#include <stdio.h>
#include <chrono>
#include <termio.h>

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

int main() {
    std::cout << "스톱워치를 시작하려면 아무 키나 누르세요." << std::endl;
    getch(); // 아무 키 입력 대기
    
    // 스톱워치 시작
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    
    std::cout << "스톱워치를 종료하려면 다시 아무 키나 누르세요." << std::endl;
    getch(); // 아무 키 입력 대기
    
    // 스톱워치 종료
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    // 경과 시간 계산
    std::chrono::duration<double> duration = end - start;
    
    // 경과 시간 출력
    std::cout << "경과 시간: " << duration.count() << "초" << std::endl;
    
    return 0;
}
