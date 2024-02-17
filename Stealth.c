#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define WIDTH 20
#define HEIGHT 15
#define NUM_POLICE 4
#define NUM_GOLD 5
#define NUM_WALLS 60

struct Point {
    int x;
    int y;
};

// Fixed wall positions
struct Point fixedWalls[NUM_WALLS] = {
    {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5},
    {3, 1}, {3, 5},
    {5, 1}, {5, 5},
    {7, 1}, {7, 2}, {7, 3}, {7, 5},
    {9, 1}, {9, 5},
    {11, 1}, {11, 5},
    {13, 1}, {13, 2}, {13, 3}, {13, 5},
    {15, 1}, {15, 5},
    {17, 1}, {17, 5},
    {19, 1}, {19, 5},
    {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7},
    {8, 9}, {8, 10}, {8, 11}, {8, 12}, {8, 13},
    {11, 9}, {11, 10}, {11, 11}, {11, 12}, {11, 13},
    {14, 9}, {14, 10}, {14, 11}, {14, 12}, {14, 13},
    {16, 7}, {17, 7}, {18, 7}, {19, 7},
    {16, 3}, {17, 3}, {18, 3}, {19, 3}
};

struct Game {
    int width;
    int height;
    struct Point player;
    struct Point police[NUM_POLICE];
    struct Point gold[NUM_GOLD];
    struct Point walls[NUM_WALLS];
    int score;
};

void initGame(struct Game *game) {
    game->width = WIDTH;
    game->height = HEIGHT;

    game->player.x = rand() % (WIDTH - 2) + 1;
    game->player.y = rand() % (HEIGHT - 2) + 1;

    for (int i = 0; i < NUM_POLICE; ++i) {
        game->police[i].x = rand() % (WIDTH - 2) + 1;
        game->police[i].y = rand() % (HEIGHT - 2) + 1;
    }

    for (int i = 0; i < NUM_GOLD; ++i) {
        game->gold[i].x = rand() % (WIDTH - 2) + 1;
        game->gold[i].y = rand() % (HEIGHT - 2) + 1;
    }

    // Copy fixed wall positions
    for (int i = 0; i < NUM_WALLS; ++i) {
        game->walls[i] = fixedWalls[i];
    }

    game->score = 0;
}

int isAdjacent(struct Point point1, struct Point point2) {
    return abs(point1.x - point2.x) <= 1 && abs(point1.y - point2.y) <= 1;
}

int isWall(struct Game *game, int x, int y) {
    for (int i = 0; i < NUM_WALLS; ++i) {
        if (game->walls[i].x == x && game->walls[i].y == y) {
            return 1;
        }
    }
    return 0;
}

void printBoard(struct Game *game) {
    for (int y = 0; y < game->height; y++) {
        for (int x = 0; x < game->width; x++) {
            if (x == game->player.x && y == game->player.y)
                printf(ANSI_COLOR_RED "P " ANSI_COLOR_RESET);
            else {
                int policeIndex;
                for (policeIndex = 0; policeIndex < NUM_POLICE; ++policeIndex) {
                    if (x == game->police[policeIndex].x && y == game->police[policeIndex].y) {
                        printf(ANSI_COLOR_BLUE "M " ANSI_COLOR_RESET);
                        break;
                    }
                }
                if (policeIndex == NUM_POLICE) {
                    int goldIndex;
                    for (goldIndex = 0; goldIndex < NUM_GOLD; ++goldIndex) {
                        if (x == game->gold[goldIndex].x && y == game->gold[goldIndex].y) {
                            printf(ANSI_COLOR_YELLOW "$ " ANSI_COLOR_RESET);
                            break;
                        }
                    }
                    if (goldIndex == NUM_GOLD) {
                        int wallIndex;
                        for (wallIndex = 0; wallIndex < NUM_WALLS; ++wallIndex) {
                            if (x == game->walls[wallIndex].x && y == game->walls[wallIndex].y) {
                                printf(ANSI_COLOR_GREEN "# " ANSI_COLOR_RESET);
                                break;
                            }
                        }
                        if (wallIndex == NUM_WALLS) {
                            printf(". ");
                        }
                    }
                }
            }
        }
        printf("\n");
    }
}

void movePlayer(struct Game *game, char direction) {
    switch (direction) {
        case 'w':
            if (game->player.y > 0 && !isWall(game, game->player.x, game->player.y - 1))
                game->player.y--;
            break;
        case 's':
            if (game->player.y < game->height - 1 && !isWall(game, game->player.x, game->player.y + 1))
                game->player.y++;
            break;
        case 'a':
            if (game->player.x > 0 && !isWall(game, game->player.x - 1, game->player.y))
                game->player.x--;
            break;
        case 'd':
            if (game->player.x < game->width - 1 && !isWall(game, game->player.x + 1, game->player.y))
                game->player.x++;
            break;
    }
}

void movePolice(struct Game *game) {
    for (int i = 0; i < NUM_POLICE; ++i) {
        int direction = rand() % 4;
        switch (direction) {
            case 0:
                if (game->police[i].y > 0 && !isWall(game, game->police[i].x, game->police[i].y - 1))
                    game->police[i].y--;
                break;
            case 1:
                if (game->police[i].y < game->height - 1 && !isWall(game, game->police[i].x, game->police[i].y + 1))
                    game->police[i].y++;
                break;
            case 2:
                if (game->police[i].x > 0 && !isWall(game, game->police[i].x - 1, game->police[i].y))
                    game->police[i].x--;
                break;
            case 3:
                if (game->police[i].x < game->width - 1 && !isWall(game, game->police[i].x + 1, game->police[i].y))
                    game->police[i].x++;
                break;
        }
    }
}

int checkCollision(struct Game *game) {
    for (int i = 0; i < NUM_GOLD; ++i) {
        if (game->player.x == game->gold[i].x && game->player.y == game->gold[i].y) {
            printf("You stole the gold! Congratulations!\n");
            game->score++;
            return 1;
        }
    }

    for (int i = 0; i < NUM_POLICE; ++i) {
        if (game->player.x == game->police[i].x && game->player.y == game->police[i].y) {
            printf("You were caught by the police! Game over.\n");
            return -1;
        }

        // Check if police is adjacent to the player
        if (isAdjacent(game->player, game->police[i])) {
            printf("The police caught you! Game over.\n");
            return -1;
        }
    }

    // Check if player is on a wall
    if (isWall(game, game->player.x, game->player.y)) {
        printf("You hit a wall! Game over.\n");
        return -1;
    }

    return 0;
}

void resetObjects(struct Game *game) {
    game->player.x = rand() % (game->width - 2) + 1;
    game->player.y = rand() % (game->height - 2) + 1;

    for (int i = 0; i < NUM_POLICE; ++i) {
        game->police[i].x = rand() % (game->width - 2) + 1;
        game->police[i].y = rand() % (game->height - 2) + 1;
    }

    for (int i = 0; i < NUM_GOLD; ++i) {
        game->gold[i].x = rand() % (game->width - 2) + 1;
        game->gold[i].y = rand() % (game->height - 2) + 1;
    }
}

int main() {
    srand(time(NULL));
    struct Game game;
    initGame(&game);

    while (1) {
        system(CLEAR); // Clear the screen
        printBoard(&game);
        printf("Score: %d\n", game.score);

        char move;
        printf("Enter your move (w/a/s/d): ");
        scanf(" %c", &move);

        movePlayer(&game, move);
        movePolice(&game);

        int result = checkCollision(&game);
        if (result == 1) {
            resetObjects(&game);
        } else if (result == -1) {
            break;
        }
    }

    return 0;
}
