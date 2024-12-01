#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define WIDTH 21
#define HEIGHT 11

// 미로: 0은 길, 1은 벽, 2는 출구
int maze[HEIGHT][WIDTH];

// 플레이어 위치
int playerX = 1, playerY = 1;

// 방향 이동 배열 (상, 하, 좌, 우)
int dx[] = { 0, 0, -1, 1 };
int dy[] = { -1, 1, 0, 0 };

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

// 미로 초기화
void initializeMaze() {
    // 모든 칸을 벽(1)으로 채움
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            maze[y][x] = 1;
        }
    }
}

// 미로 생성 (DFS 기반)
void generateMaze(int x, int y) {
    maze[y][x] = 0; // 현재 위치를 길로 설정

    // 방향을 랜덤하게 섞음
    int directions[] = { 0, 1, 2, 3 };
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int temp = directions[i];
        directions[i] = directions[r];
        directions[r] = temp;
    }

    // 섞은 방향으로 이동
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[directions[i]] * 2;
        int ny = y + dy[directions[i]] * 2;

        // 이동할 위치가 유효하고, 벽인 경우
        if (nx > 0 && ny > 0 && nx < WIDTH - 1 && ny < HEIGHT - 1 && maze[ny][nx] == 1) {
            // 중간 벽도 제거
            maze[y + dy[directions[i]]][x + dx[directions[i]]] = 0;
            generateMaze(nx, ny);
        }
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
    srand(time(NULL));

    // 미로 초기화 및 생성
    initializeMaze();
    generateMaze(1, 1);

    // 출구 설정
    maze[HEIGHT - 2][WIDTH - 2] = 2;

    printf("랜덤 미로 탈출 게임에 오신 것을 환영합니다!\n");
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
