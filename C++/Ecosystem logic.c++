#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <ctime>

const int GRID_SIZE = 10;
const int NUM_HERBIVORES = 5;
const int NUM_CARNIVORES = 3;
std::mutex grid_mutex;

class Animal {
protected:
    int x, y;
public:
    Animal(int startX, int startY) : x(startX), y(startY) {}
    virtual void move() = 0;
    virtual char getSymbol() = 0;
    int getX() { return x; }
    int getY() { return y; }
};

class Herbivore : public Animal {
public:
    Herbivore(int startX, int startY) : Animal(startX, startY) {}
    void move() override {
        x = (x + (rand() % 3 - 1) + GRID_SIZE) % GRID_SIZE;
        y = (y + (rand() % 3 - 1) + GRID_SIZE) % GRID_SIZE;
    }
    char getSymbol() override { return 'H'; }
};

class Carnivore : public Animal {
public:
    Carnivore(int startX, int startY) : Animal(startX, startY) {}
    void move() override {
        x = (x + (rand() % 3 - 1) + GRID_SIZE) % GRID_SIZE;
        y = (y + (rand() % 3 - 1) + GRID_SIZE) % GRID_SIZE;
    }
    char getSymbol() override { return 'C'; }
};

void printGrid(const std::vector<Animal*>& animals) {
    char grid[GRID_SIZE][GRID_SIZE] = {};
    for (auto& a : animals) {
        grid[a->getX()][a->getY()] = a->getSymbol();
    }
    std::system("clear");
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 'H' || grid[i][j] == 'C')
                std::cout << grid[i][j] << " ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
}

void simulate(std::vector<Animal*>& animals) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::lock_guard<std::mutex> lock(grid_mutex);
        for (auto& a : animals) {
            a->move();
        }
        printGrid(animals);
    }
}

int main() {
    srand(time(0));
    std::vector<Animal*> animals;
    for (int i = 0; i < NUM_HERBIVORES; i++) {
        animals.push_back(new Herbivore(rand() % GRID_SIZE, rand() % GRID_SIZE));
    }
    for (int i = 0; i < NUM_CARNIVORES; i++) {
        animals.push_back(new Carnivore(rand() % GRID_SIZE, rand() % GRID_SIZE));
    }
    
    std::thread simThread(simulate, std::ref(animals));
    simThread.join();
    
    for (auto& a : animals) delete a;
    return 0;
}