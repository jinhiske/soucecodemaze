#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define INITIAL_WIDTH 11
#define INITIAL_HEIGHT 11
#define MAX_LEVEL 3
#define MAX_SIZE 51

int maze[MAX_SIZE][MAX_SIZE];     // 미로 배열
int visited[MAX_SIZE][MAX_SIZE]; // 지나온 길 기록
int width, height;               // 현재 미로 크기
int playerX, playerY;            // 플레이어 위치
int level = 1;                   // 현재 레벨
int difficulty = 0;              // 난이도 (0: 일반, 1: 어려움)
time_t totalStartTime, totalEndTime; // 전체 타이머
time_t levelStartTime, levelEndTime; // 단계별 타이머
int levelTimes[MAX_LEVEL];       // 각 단계 소요 시간 (초)

// 방향 이동 배열 (상, 하, 좌, 우)
int dx[] = { 0, 0, -1, 1 };
int dy[] = { -1, 1, 0, 0 };

// 미로 초기화
void initializeMaze() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            maze[y][x] = 1;      // 벽으로 초기화
            visited[y][x] = 0;   // 방문 여부 초기화
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
        if (nx > 0 && ny > 0 && nx < width - 1 && ny < height - 1 && maze[ny][nx] == 1) {
            maze[y + dy[directions[i]]][x + dx[directions[i]]] = 0; // 중간 벽 제거
            generateMaze(nx, ny);
        }
    }
}

// 실시간 타이머 출력
void displayTimer() {
    time_t currentTime = time(NULL);
    int elapsed = (int)difftime(currentTime, levelStartTime);

    int minutes = elapsed / 60;
    int seconds = elapsed % 60;

    printf("Time: %02d:%02d\n", minutes, seconds);
}

// 미로 그리기 (일반 모드)
void drawMazeNormal() {
    system("cls");
    displayTimer(); // 타이머 출력
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
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

// 플레이어 이동
void movePlayer(char input) {
    int nextX = playerX, nextY = playerY;

    if (input == 'w') nextY--; // 위로 이동
    else if (input == 's') nextY++; // 아래로 이동
    else if (input == 'a') nextX--; // 왼쪽으로 이동
    else if (input == 'd') nextX++; // 오른쪽으로 이동

    // 이동 가능 여부 확인
    if (maze[nextY][nextX] != 1) {
        playerX = nextX;
        playerY = nextY;
        visited[playerY][playerX] = 1; // 방문 기록
    }
}

// 막다른 길인지 판별
int isDeadEnd(int x, int y) {
    if (maze[y][x] != 0) return 0; // 길이 아니라면 false

    int wallCount = 0;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= width || ny >= height || maze[ny][nx] == 1) {
            wallCount++;
        }
    }
    return wallCount >= 3; // 인접한 벽이 3개 이상일 때 true
}

// 단계 시작
void startLevel() {
    printf("Level %d 시작!\n", level);
    getchar();

    // 미로 초기화 및 생성
    initializeMaze();
    generateMaze(1, 1);

    // 출구 설정 (무작위 막다른 길에 배치)
    int exitX, exitY;
    while (1) {
        exitX = rand() % (width - 2) + 1;  // 1 ~ width-2
        exitY = rand() % (height - 2) + 1; // 1 ~ height-2

        if (isDeadEnd(exitX, exitY) && !(exitX == 1 && exitY == 1)) { // 막다른 길이며 시작 위치가 아닌 경우
            break;
        }
    }
    maze[exitY][exitX] = 2; // 출구 설정

    // 플레이어 초기 위치
    playerX = 1;
    playerY = 1;
    visited[playerY][playerX] = 1; // 시작 위치 방문 처리

    // 단계별 타이머 시작
    levelStartTime = time(NULL);
}

int main() {
    srand(time(NULL));

    // 초기 미로 크기 설정
    width = INITIAL_WIDTH;
    height = INITIAL_HEIGHT;

    // 난이도 선택
    printf("랜덤 미로 탈출 게임에 오신 것을 환영합니다!\n");
    printf("플레이어는 'P'로 표시됩니다. 출구는 'E'입니다.\n");
    printf("난이도를 선택하세요:\n");
    printf("1. 일반 모드\n");
    printf("2. 어려움 모드\n");
    printf("선택: ");
    scanf_s("%d", &difficulty);
    getchar(); // 입력 버퍼 제거

    difficulty--; // 0: 일반, 1: 어려움

    // 게임 시작
    totalStartTime = time(NULL);

    while (level <= MAX_LEVEL) {
        startLevel();

        // 현재 단계 진행
        while (1) {
            drawMazeNormal();

            // 출구 도달 체크
            if (maze[playerY][playerX] == 2) {
                levelEndTime = time(NULL); // 단계 종료 시간 기록
                levelTimes[level - 1] = (int)difftime(levelEndTime, levelStartTime); // 단계 소요 시간 계산
                printf("축하합니다! Level %d을(를) 클리어했습니다!\n", level);
                break;
            }

            // 입력 대기 및 처리
            char input = _getch();
            movePlayer(input);
        }

        // 다음 단계로 진행
        level++;
        if (level <= MAX_LEVEL) {
            width += 10;   // 미로 너비 증가
            height += 10;  // 미로 높이 증가
        }
    }

    // 총 소요 시간 계산
    totalEndTime = time(NULL);
    int totalElapsed = (int)difftime(totalEndTime, totalStartTime);

    // 결과 출력
    printf("\n=== 게임 결과 ===\n");
    for (int i = 0; i < MAX_LEVEL; i++) {
        printf("Level %d 소요 시간: %02d:%02d\n", i + 1, levelTimes[i] / 60, levelTimes[i] % 60);
    }
    printf("총 소요 시간: %02d:%02d\n", totalElapsed / 60, totalElapsed % 60);

    return 0;
}
