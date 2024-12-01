#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define WIDTH 10
#define HEIGHT 10

// 미로: 0은 길, 1은 벽, 2는 출구
int maze[HEIGHT][WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// 플레이어 위치
int playerX = 1, playerY = 1;

// 화면 출력
void drawMaze() {
    system("cls");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == playerX && y == playerY) {
                printf("P "); // 플레이어
            }
            else if (maze[y][x] == 1) {
                printf("- "); // 벽
            }
            else if (maze[y][x] == 2) {
                printf("E "); // 출구
            }
            else {
                printf("  "); // 길 (공백)
            }
        }
        printf("\n");
    }
}

// 입력 처리
void movePlayer(char input) {
    int nextX = playerX, nextY = playerY;

    if (input == 'w') nextY--; // 위로 이동
    else if (input == 's') nextY++; // 아래로 이동
    else if (input == 'a') nextX--; // 왼쪽으로 이동
    else if (input == 'd') nextX++; // 오른쪽으로 이동

    // 이동 가능 여부 확인 (벽이 아닌 경우 이동)
    if (maze[nextY][nextX] != 1) {
        playerX = nextX;
        playerY = nextY;
    }
}

int main() {
    printf("미로 탈출 게임에 오신 것을 환영합니다!\n");
    printf("플레이어는 'P'로 표시됩니다. 출구는 'E'입니다.\n");
    printf("방향키(WASD)를 사용하여 이동하세요.\n");
    printf("엔터 키를 누르면 게임이 시작됩니다!\n");
    getchar();

    while (1) {
        drawMaze();

        // 출구 도달 체크
        if (maze[playerY][playerX] == 2) {
            printf("축하합니다! 미로를 탈출했습니다!\n");
            break;
        }

        // 입력 대기 및 처리
        char input = _getch();
        movePlayer(input);
    }

    return 0;
}
