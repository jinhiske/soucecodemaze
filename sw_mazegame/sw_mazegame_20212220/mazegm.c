#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define WIDTH 21
#define HEIGHT 11

// �̷�: 0�� ��, 1�� ��, 2�� �ⱸ
int maze[HEIGHT][WIDTH];

// �÷��̾� ��ġ
int playerX = 1, playerY = 1;

// ���� �̵� �迭 (��, ��, ��, ��)
int dx[] = { 0, 0, -1, 1 };
int dy[] = { -1, 1, 0, 0 };

// ȭ�� ���
void drawMaze() {
    system("cls");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
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
    // ��� ĭ�� ��(1)���� ä��
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            maze[y][x] = 1;
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
        if (nx > 0 && ny > 0 && nx < WIDTH - 1 && ny < HEIGHT - 1 && maze[ny][nx] == 1) {
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

int main() {
    srand(time(NULL));

    // �̷� �ʱ�ȭ �� ����
    initializeMaze();
    generateMaze(1, 1);

    // �ⱸ ����
    maze[HEIGHT - 2][WIDTH - 2] = 2;

    printf("���� �̷� Ż�� ���ӿ� ���� ���� ȯ���մϴ�!\n");
    printf("�÷��̾�� 'P'�� ǥ�õ˴ϴ�. �ⱸ�� 'E'�Դϴ�.\n");
    printf("����Ű(WASD)�� ����Ͽ� �̵��ϼ���.\n");
    printf("���� Ű�� ������ ������ ���۵˴ϴ�!\n");
    getchar();

    while (1) {
        drawMaze();

        // �ⱸ ���� üũ
        if (maze[playerY][playerX] == 2) {
            printf("�����մϴ�! �̷θ� Ż���߽��ϴ�!\n");
            break;
        }

        // �Է� ��� �� ó��
        char input = _getch();
        movePlayer(input);
    }

    return 0;
}
