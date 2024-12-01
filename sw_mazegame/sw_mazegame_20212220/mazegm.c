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

// ���� �̵� �迭 (��, ��, ��, ��)
int dx[] = { 0, 0, -1, 1 };
int dy[] = { -1, 1, 0, 0 };

<<<<<<< HEAD
// ȭ�� ���
void drawMaze() {
    system("cls");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == playerX && y == playerY) {
                printf("* "); // �÷��̾�
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

=======
>>>>>>> mod
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

// �̷� �׸��� (�Ϲ� ���)
void drawMazeNormal() {
    system("cls");
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

// �̷� �׸��� (����� ���: 3x3 �þ� ����)
void drawMazeHard() {
    system("cls");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == playerX && y == playerY) {
                printf("P "); // �÷��̾�
            }
            else if (x == width - 2 && y == height - 2) {
                printf("E "); // �ⱸ�� �׻� ǥ��
            }
            else if (visited[y][x]) {
                printf(". "); // ������ ��
            }
            else if (abs(playerX - x) <= 1 && abs(playerY - y) <= 1) {
                if (maze[y][x] == 1)
                    printf("- "); // ��
                else
                    printf("  "); // ��
            }
            else {
                printf("  "); // ������ �ʴ� ����
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

// �ܰ� ����
void startLevel() {
    printf("Level %d ����!\n", level);
    getchar();

    // �̷� �ʱ�ȭ �� ����
    initializeMaze();
    generateMaze(1, 1);

    // �ⱸ ����
    maze[height - 2][width - 2] = 2;

    // �÷��̾� �ʱ� ��ġ
    playerX = 1;
    playerY = 1;
    visited[playerY][playerX] = 1; // ���� ��ġ �湮 ó��
}

int main() {
    srand(time(NULL));

    // �ʱ� �̷� ũ�� ����
    width = INITIAL_WIDTH;
    height = INITIAL_HEIGHT;

    // ���̵� ����
    printf("���� �̷� Ż�� ���ӿ� ���� ���� ȯ���մϴ�!\n");
<<<<<<< HEAD
    printf("�÷��̾�� '*'�� ǥ�õ˴ϴ�. �ⱸ�� 'E'�Դϴ�.\n");
    printf("����Ű(WASD)�� ����Ͽ� �̵��ϼ���.\n");
    printf("���� Ű�� ������ ������ ���۵˴ϴ�!\n");
    getchar();
=======
    printf("�÷��̾�� 'P'�� ǥ�õ˴ϴ�. �ⱸ�� 'E'�Դϴ�.\n");
    printf("���̵��� �����ϼ���:\n");
    printf("1. �Ϲ� ���\n");
    printf("2. ����� ���\n");
    printf("����: ");
    scanf_s("%d", &difficulty);
    getchar(); // �Է� ���� ����

    difficulty--; // 0: �Ϲ�, 1: �����
>>>>>>> mod

    while (level <= MAX_LEVEL) {
        startLevel();

        // ���� �ܰ� ����
        while (1) {
            if (difficulty == 0) {
                drawMazeNormal(); // �Ϲ� ���
            }
            else {
                drawMazeHard();   // ����� ���
            }

            // �ⱸ ���� üũ
            if (maze[playerY][playerX] == 2) {
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

    printf("�����մϴ�! ��� �ܰ踦 Ŭ�����߽��ϴ�!\n");
    return 0;
}
