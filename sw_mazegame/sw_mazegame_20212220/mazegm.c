#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

// �ʱ� �̷� ũ�� �� �ܰ� ����
#define INITIAL_WIDTH 11
#define INITIAL_HEIGHT 11
#define MAX_LEVEL 3

// �̷� �迭 ũ�� ����
#define MAX_SIZE 51

int maze[MAX_SIZE][MAX_SIZE]; // �̷� �迭
int width, height;           // ���� �̷� ũ��
int playerX, playerY;        // �÷��̾� ��ġ
int level = 1;               // ���� ����

// ���� �̵� �迭 (��, ��, ��, ��)
int dx[] = { 0, 0, -1, 1 };
int dy[] = { -1, 1, 0, 0 };

// ȭ�� ���
void drawMaze() {
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

// �̷� �ʱ�ȭ
void initializeMaze() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            maze[y][x] = 1; // ��� ĭ�� ������ �ʱ�ȭ
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
            // �߰� ���� ����
            maze[y + dy[directions[i]]][x + dx[directions[i]]] = 0;
            generateMaze(nx, ny);
        }
    }
}

// �Է� ó��
void movePlayer(char input) {
    int nextX = playerX, nextY = playerY;

    if (input == 'w') nextY--; // ���� �̵�
    else if (input == 's') nextY++; // �Ʒ��� �̵�
    else if (input == 'a') nextX--; // �������� �̵�
    else if (input == 'd') nextX++; // ���������� �̵�

    // �̵� ���� ���� Ȯ�� (���� �ƴ� ��� �̵�)
    if (maze[nextY][nextX] != 1) {
        playerX = nextX;
        playerY = nextY;
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
}

int main() {
    srand(time(NULL));

    // �ʱ� �̷� ũ�� ����
    width = INITIAL_WIDTH;
    height = INITIAL_HEIGHT;

    printf("���� �̷� Ż�� ���ӿ� ���� ���� ȯ���մϴ�!\n");
    printf("�÷��̾�� 'P'�� ǥ�õ˴ϴ�. �ⱸ�� 'E'�Դϴ�.\n");
    printf("����Ű(WASD)�� ����Ͽ� �̵��ϼ���.\n");
    printf("���� Ű�� ������ ������ ���۵˴ϴ�!\n");
    getchar();

    while (level <= MAX_LEVEL) {
        startLevel();

        // ���� �ܰ� ����
        while (1) {
            drawMaze();

            // �ⱸ ���� üũ
            if (maze[playerY][playerX] == 3) {
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
