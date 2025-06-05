#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;

// Terminal Roguelike Dungeon Crawler

const int WIDTH = 30;
const int HEIGHT = 15;
const int NUM_ENEMIES = 5;
const int NUM_TREASURES = 4;

enum Tile { EMPTY, WALL, PLAYER, ENEMY, TREASURE, EXIT };

struct Entity {
    int x, y, hp, atk;
    char symbol;
    bool alive;
};

struct Game {
    vector<vector<Tile>> map;
    Entity player;
    vector<Entity> enemies;
    vector<pair<int, int>> treasures;
    pair<int, int> exit;
    int score;
    bool running;
};

void clearScreen() {
    // Windows
    system("cls");
}

void initMap(Game &game) {
    game.map = vector<vector<Tile>>(HEIGHT, vector<Tile>(WIDTH, EMPTY));
    // Borders
    for (int i = 0; i < HEIGHT; ++i) {
        game.map[i][0] = WALL;
        game.map[i][WIDTH-1] = WALL;
    }
    for (int j = 0; j < WIDTH; ++j) {
        game.map[0][j] = WALL;
        game.map[HEIGHT-1][j] = WALL;
    }
    // Random walls
    for (int i = 0; i < HEIGHT * WIDTH / 8; ++i) {
        int x = rand() % (WIDTH-2) + 1;
        int y = rand() % (HEIGHT-2) + 1;
        game.map[y][x] = WALL;
    }
}

void placeEntity(Game &game, Entity &e, Tile t) {
    while (true) {
        int x = rand() % (WIDTH-2) + 1;
        int y = rand() % (HEIGHT-2) + 1;
        if (game.map[y][x] == EMPTY) {
            e.x = x; e.y = y;
            game.map[y][x] = t;
            break;
        }
    }
}

void placeTreasures(Game &game) {
    game.treasures.clear();
    for (int i = 0; i < NUM_TREASURES; ++i) {
        while (true) {
            int x = rand() % (WIDTH-2) + 1;
            int y = rand() % (HEIGHT-2) + 1;
            if (game.map[y][x] == EMPTY) {
                game.map[y][x] = TREASURE;
                game.treasures.push_back({x, y});
                break;
            }
        }
    }
}

void placeExit(Game &game) {
    while (true) {
        int x = rand() % (WIDTH-2) + 1;
        int y = rand() % (HEIGHT-2) + 1;
        if (game.map[y][x] == EMPTY) {
            game.map[y][x] = EXIT;
            game.exit = {x, y};
            break;
        }
    }
}

void initGame(Game &game) {
    srand((unsigned)time(0));
    game.score = 0;
    game.running = true;
    initMap(game);

    // Player
    game.player = {0, 0, 20, 5, '@', true};
    placeEntity(game, game.player, PLAYER);

    // Enemies
    game.enemies.clear();
    for (int i = 0; i < NUM_ENEMIES; ++i) {
        Entity e = {0, 0, 10 + rand()%6, 2 + rand()%4, 'E', true};
        placeEntity(game, e, ENEMY);
        game.enemies.push_back(e);
    }

    // Treasures
    placeTreasures(game);

    // Exit
    placeExit(game);
}

void drawMap(const Game &game) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (game.player.x == x && game.player.y == y)
                cout << game.player.symbol;
            else {
                bool enemyHere = false;
                for (const auto &e : game.enemies)
                    if (e.x == x && e.y == y && e.alive) { cout << e.symbol; enemyHere = true; break; }
                if (enemyHere) continue;
                switch (game.map[y][x]) {
                    case WALL: cout << '#'; break;
                    case EMPTY: cout << '.'; break;
                    case TREASURE: cout << '$'; break;
                    case EXIT: cout << '>'; break;
                    default: cout << ' '; break;
                }
            }
        }
        cout << endl;
    }
    cout << "HP: " << game.player.hp << "  Score: " << game.score << endl;
    cout << "Controls: WASD to move, Q to quit" << endl;
}

bool isWalkable(Tile t) {
    return t == EMPTY || t == TREASURE || t == EXIT;
}

void movePlayer(Game &game, int dx, int dy) {
    int nx = game.player.x + dx;
    int ny = game.player.y + dy;
    if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT) return;
    Tile t = game.map[ny][nx];
    if (t == WALL) return;

    // Enemy collision
    for (auto &e : game.enemies) {
        if (e.x == nx && e.y == ny && e.alive) {
            // Combat
            e.hp -= game.player.atk;
            if (e.hp <= 0) {
                e.alive = false;
                game.map[ny][nx] = EMPTY;
                game.score += 10;
            } else {
                game.player.hp -= e.atk;
                if (game.player.hp <= 0) {
                    game.running = false;
                }
            }
            return;
        }
    }

    // Treasure
    if (t == TREASURE) {
        game.score += 5;
        game.player.hp += 2;
        game.map[ny][nx] = EMPTY;
    }

    // Exit
    if (t == EXIT) {
        cout << "You found the exit! Score: " << game.score << endl;
        game.running = false;
        return;
    }

    // Move player
    game.map[game.player.y][game.player.x] = EMPTY;
    game.player.x = nx;
    game.player.y = ny;
    game.map[ny][nx] = PLAYER;
}

void moveEnemies(Game &game) {
    for (auto &e : game.enemies) {
        if (!e.alive) continue;
        int dx = 0, dy = 0;
        // Simple AI: move towards player if close
        if (abs(e.x - game.player.x) + abs(e.y - game.player.y) < 8) {
            if (e.x < game.player.x) dx = 1;
            else if (e.x > game.player.x) dx = -1;
            if (e.y < game.player.y) dy = 1;
            else if (e.y > game.player.y) dy = -1;
        } else {
            // Random move
            int dir = rand() % 4;
            if (dir == 0) dx = 1;
            else if (dir == 1) dx = -1;
            else if (dir == 2) dy = 1;
            else dy = -1;
        }
        int nx = e.x + dx, ny = e.y + dy;
        if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT) continue;
        if (game.map[ny][nx] == EMPTY && !(nx == game.player.x && ny == game.player.y)) {
            game.map[e.y][e.x] = EMPTY;
            e.x = nx; e.y = ny;
            game.map[ny][nx] = ENEMY;
        }
    }
}

void gameLoop(Game &game) {
    while (game.running) {
        clearScreen();
        drawMap(game);

        char c = _getch();
        if (c == 'q' || c == 'Q') break;
        int dx = 0, dy = 0;
        if (c == 'w' || c == 'W') dy = -1;
        else if (c == 's' || c == 'S') dy = 1;
        else if (c == 'a' || c == 'A') dx = -1;
        else if (c == 'd' || c == 'D') dx = 1;

        movePlayer(game, dx, dy);
        moveEnemies(game);

        if (game.player.hp <= 0) {
            clearScreen();
            cout << "You died! Final score: " << game.score << endl;
            break;
        }
    }
}

int main() {
    Game game;
    initGame(game);
    gameLoop(game);
    cout << "Thanks for playing!" << endl;
    return 0;
}