#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define WIDTH 80    // ��Ϸ������
#define HEIGHT 25   // ��Ϸ����߶�

// ������ɫ
#define COLOR_BLACK 0
#define COLOR_WHITE 15
#define COLOR_RED 12

// ö�����ͱ�ʾ����
enum Direction {
    UP, DOWN, LEFT, RIGHT
};

// ��������ṹ��
struct Coordinate {
    int x;
    int y;
};

// ����ڵ�ṹ��
struct Node {
    struct Coordinate pos;      // ����
    struct Node *next;          // ��һ���ڵ�
};

// ����̰���߽ṹ��
struct Snake {
    struct Node *head;          // ��ͷ
    struct Node *tail;          // ��β
    enum Direction direction;   // �ƶ�����
    int length;                 // ����
    int speed;                  // �ٶȣ�ÿ���ƶ���������
};

// ������Ϸ״̬�ṹ��
struct Game {
    struct Snake snake;         // ̰����
    struct Coordinate apple;    // ƻ������
    int score;                  // �÷�
    int isOver;                 // ��Ϸ�Ƿ����
};

// ��ʼ����Ϸ״̬
void initGame(struct Game *game) {
    // ��ʼ��̰����
    struct Node *node = malloc(sizeof(struct Node));
    node->pos.x = WIDTH / 2;
    node->pos.y = HEIGHT / 2;
    node->next = NULL;

    game->snake.head = node;
    game->snake.tail = node;
    game->snake.direction = RIGHT;
    game->snake.length = 1;
    game->snake.speed = 10;

    // �������ƻ������
    srand((unsigned int)time(NULL));
    game->apple.x = rand() % (WIDTH - 1) + 1;
    game->apple.y = rand() % (HEIGHT - 1) + 1;

    game->score = 0;
    game->isOver = 0;
}

// ������Ϸ״̬
void destroyGame(struct Game *game) {
    // ����̰���߽ڵ�
    struct Node *node = game->snake.head;
    while (node != NULL) {
        struct Node *temp = node;
        node = node->next;
        free(temp);
    }
}

// ������Ϸ����
void drawGame(struct Game *game) {
    system("cls");      // ����

    // ������Ϸ����
    for (int i = 0; i <= HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) {
            if (i == 0 || i == HEIGHT || j == 0 || j == WIDTH) {
                printf("#");
            } else {
                if (i == game->apple.y && j == game->apple.x) {      // ����ƻ��
                    printf("@");
                } else {
                    int isSnake = 0;
                    struct Node *node = game->snake.head;
                    while (node != NULL) {
                        if (node->pos.x == j && node->pos.y == i) {   // ����̰����
                            printf("*");
                            isSnake = 1;
                            break;
                        }
                        node = node->next;
                    }
                    if (!isSnake) {
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
    }

    // ��ʾ�÷ֺͲ�����ʾ
    printf("Score: %d\t", game->score);
    printf("Press arrow keys to move, ESC to exit.\n");
}

// �ƶ�̰����
void moveSnake(struct Game *game) {
    // �ж��Ƿ���ƻ��
    if (game->snake.head->pos.x == game->apple.x && game->snake.head->pos.y == game->apple.y) {
        // �����µ�ƻ������
        srand((unsigned int)time(NULL));
        game->apple.x = rand() % (WIDTH - 1) + 1;
        game->apple.y = rand() % (HEIGHT - 1) + 1;

        // ����ͷǰ�����½ڵ�
        struct Node *node = malloc(sizeof(struct Node));
        node->pos.x = game->snake.head->pos.x;
        node->pos.y = game->snake.head->pos.y;
        node->next = game->snake.head;
        game->snake.head = node;
        game->snake.length++;

        // ���µ÷�
        game->score++;
    } else {
        // ����ͷǰ�����½ڵ�
        struct Node *node = malloc(sizeof(struct Node));
        node->pos.x = game->snake.head->pos.x;
        node->pos.y = game->snake.head->pos.y;
        node->next = game->snake.head;
        game->snake.head = node;

        // ɾ����β�ڵ�
        if (game->snake.length > 1) {
            struct Node *tail = game->snake.tail;
            struct Node *preTail = game->snake.head;
            while (preTail->next != tail) {
                preTail = preTail->next;
            }
            preTail->next = NULL;
            game->snake.tail = preTail;
            free(tail);
        }
    }

    // ����̰�����ƶ�����
    if (_kbhit()) {     // �ж��Ƿ��м�������
        int key = _getch();
        switch (key) {
            case 72:    // �ϼ�ͷ
                if (game->snake.direction != DOWN) {
                    game->snake.direction = UP;
                }
                break;
            case 80:    // �¼�ͷ
                if (game->snake.direction != UP) {
                    game->snake.direction = DOWN;
                }
                break;
            case 75:    // ���ͷ
                if (game->snake.direction != RIGHT) {
                    game->snake.direction = LEFT;
                }
                break;
            case 77:    // �Ҽ�ͷ
                if (game->snake.direction != LEFT) {
                    game->snake.direction = RIGHT;
                }
                break;
            case 27:    // ESC
                game->isOver = 1;
                break;
            default:
                break;
        }
    }

    // �ƶ�̰����
    struct Coordinate *headPos = &(game->snake.head->pos);
    switch (game->snake.direction) {
        case UP:
            headPos->y--;
            break;
        case DOWN:
            headPos->y++;
            break;
        case LEFT:
            headPos->x--;
            break;
        case RIGHT:
            headPos->x++;
            break;
    }

    // �ж��Ƿ�ײǽ
    if (headPos->x == 0 || headPos->x == WIDTH || headPos->y == 0 || headPos->y == HEIGHT) {
        game->isOver = 1;
    }

    // �ж��Ƿ�ײ�Լ�
    struct Node *node = game->snake.head->next;
    while (node != NULL) {
        if (node->pos.x == headPos->x && node->pos.y == headPos->y) {
            game->isOver = 1;
            break;
        }
        node = node->next;
    }
}

// ��Ϸ��ѭ��
void runGame() {
    struct Game game;
    initGame(&game);

    while (!game.isOver) {
        drawGame(&game);
        moveSnake(&game);
        Sleep(1000 / game.snake.speed);      // ����̰�����ٶ�
    }

    drawGame(&game);
    printf("Game over! Your score is: %d\n", game.score);

    destroyGame(&game);
}

int main() {
    runGame();
    return 0;
}

