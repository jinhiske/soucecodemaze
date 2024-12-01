#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define INITIAL_WIDTH 11
#define INITIAL_HEIGHT 11
#define MAX_LEVEL 3
#define MAX_SIZE 51

int maze[MAX_SIZE][MAX_SIZE];     // �̷� �迭
int visited[MAX_SIZE][MAX_SIZE]; // ������ �� ���
int width, height;               // ���� �̷� ũ��
int playerX, playerY;            // �÷��̾� ��ġ
int level = 1;                   // ���� ����
int difficulty = 0;              // ���̵� (0: �Ϲ�, 1: �����)
time_t totalStartTime, totalEndTime; // ��ü Ÿ�̸�
time_t levelStartTime, levelEndTime; // �ܰ躰 Ÿ�̸�
int levelTimes[MAX_LEVEL];       // �� �ܰ� �ҿ� �ð� (��)

// ���� �̵� �迭 (��, ��, ��, ��)
int dx[] = { 0, 0, -1, 1 };
int dy[] = { -1, 1, 0, 0 };

// �̷� �ʱ�ȭ
void initializeMaze() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            maze[y][x] = 1;      // ������ �ʱ�ȭ
            visited[y][x] = 0;   // �湮 ���� �ʱ�ȭ
        }
    }
}

// �̷� ���� (DFS ���)
void generateMaze(int x, int y) {
    maze[y][x] = 0; // ���� ��ġ�� ��� ����

    // ������ �����ϰ� ����
    int directions[] = { 0, 1, 2, 3 };
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int temp = directions[i];
        directions[i] = directions[r];
        directions[r] = temp;
    }

    // ���� �������� �̵�
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[directions[i]] * 2;
        int ny = y + dy[directions[i]] * 2;

        // �̵��� ��ġ�� ��ȿ�ϰ�, ���� ���
        if (nx > 0 && ny > 0 && nx < width - 1 && ny < height - 1 && maze[ny][nx] == 1) {
            maze[y + dy[directions[i]]][x + dx[directions[i]]] = 0; // �߰� �� ����
            generateMaze(nx, ny);
        }
    }
}

// �ǽð� Ÿ�̸� ���
void displayTimer() {
    time_t currentTime = time(NULL);
    int elapsed = (int)difftime(currentTime, levelStartTime);

    int minutes = elapsed / 60;
    int seconds = elapsed % 60;

    printf("Time: %02d:%02d\n", minutes, seconds);
}

// �̷� �׸��� (�Ϲ� ���)
void drawMazeNormal() {
    system("cls");
    displayTimer(); // Ÿ�̸� ���
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == playerX && y == playerY) {
                printf("P "); // �÷��̾�
            }
            else if (maze[y][x] == 1) {
                printf("- "); // ��
            }
            else if (maze[y][x] == 2) {
                printf("E "); // �ⱸ
            }
            else {
                printf("  "); // �� (����)
            }
        }
        printf("\n");
    }
}

// �÷��̾� �̵�
void movePlayer(char input) {
    int nextX = playerX, nextY = playerY;

    if (input == 'w') nextY--; // ���� �̵�
    else if (input == 's') nextY++; // �Ʒ��� �̵�
    else if (input == 'a') nextX--; // �������� �̵�
    else if (input == 'd') nextX++; // ���������� �̵�

    // �̵� ���� ���� Ȯ��
    if (maze[nextY][nextX] != 1) {
        playerX = nextX;
        playerY = nextY;
        visited[playerY][playerX] = 1; // �湮 ���
    }
}

// ���ٸ� ������ �Ǻ�
int isDeadEnd(int x, int y) {
    if (maze[y][x] != 0) return 0; // ���� �ƴ϶�� false

    int wallCount = 0;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= width || ny >= height || maze[ny][nx] == 1) {
            wallCount++;
        }
    }
    return wallCount >= 3; // ������ ���� 3�� �̻��� �� true
}

// �ܰ� ����
void startLevel() {
    printf("Level %d ����!\n", level);
    getchar();

    // �̷� �ʱ�ȭ �� ����
    initializeMaze();
    generateMaze(1, 1);

    // �ⱸ ���� (������ ���ٸ� �濡 ��ġ)
    int exitX, exitY;
    while (1) {
        exitX = rand() % (width - 2) + 1;  // 1 ~ width-2
        exitY = rand() % (height - 2) + 1; // 1 ~ height-2

        if (isDeadEnd(exitX, exitY) && !(exitX == 1 && exitY == 1)) { // ���ٸ� ���̸� ���� ��ġ�� �ƴ� ���
            break;
        }
    }
    maze[exitY][exitX] = 2; // �ⱸ ����

    // �÷��̾� �ʱ� ��ġ
    playerX = 1;
    playerY = 1;
    visited[playerY][playerX] = 1; // ���� ��ġ �湮 ó��

    // �ܰ躰 Ÿ�̸� ����
    levelStartTime = time(NULL);
}

int main() {
    srand(time(NULL));

    // �ʱ� �̷� ũ�� ����
    width = INITIAL_WIDTH;
    height = INITIAL_HEIGHT;

    // ���̵� ����
    printf("���� �̷� Ż�� ���ӿ� ���� ���� ȯ���մϴ�!\n");
    printf("�÷��̾�� 'P'�� ǥ�õ˴ϴ�. �ⱸ�� 'E'�Դϴ�.\n");
    printf("���̵��� �����ϼ���:\n");
    printf("1. �Ϲ� ���\n");
    printf("2. ����� ���\n");
    printf("����: ");
    scanf_s("%d", &difficulty);
    getchar(); // �Է� ���� ����

    difficulty--; // 0: �Ϲ�, 1: �����

    // ���� ����
    totalStartTime = time(NULL);

    while (level <= MAX_LEVEL) {
        startLevel();

        // ���� �ܰ� ����
        while (1) {
            drawMazeNormal();

            // �ⱸ ���� üũ
            if (maze[playerY][playerX] == 2) {
                levelEndTime = time(NULL); // �ܰ� ���� �ð� ���
                levelTimes[level - 1] = (int)difftime(levelEndTime, levelStartTime); // �ܰ� �ҿ� �ð� ���
                printf("�����մϴ�! Level %d��(��) Ŭ�����߽��ϴ�!\n", level);
                break;
            }

            // �Է� ��� �� ó��
            char input = _getch();
            movePlayer(input);
        }

        // ���� �ܰ�� ����
        level++;
        if (level <= MAX_LEVEL) {
            width += 10;   // �̷� �ʺ� ����
            height += 10;  // �̷� ���� ����
        }
    }

    // �� �ҿ� �ð� ���
    totalEndTime = time(NULL);
    int totalElapsed = (int)difftime(totalEndTime, totalStartTime);

    // ��� ���
    printf("\n=== ���� ��� ===\n");
    for (int i = 0; i < MAX_LEVEL; i++) {
        printf("Level %d �ҿ� �ð�: %02d:%02d\n", i + 1, levelTimes[i] / 60, levelTimes[i] % 60);
    }
    printf("�� �ҿ� �ð�: %02d:%02d\n", totalElapsed / 60, totalElapsed % 60);

    return 0;
}
