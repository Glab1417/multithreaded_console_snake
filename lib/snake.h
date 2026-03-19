#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <conio.h>


class Game{
    public:
        bool Game_over = false;
        std::mutex mtx;

        int width = 20;
        int height = 10;

        int apple_x;
        int apple_y;

        char direction = 'd';

        std::vector<std::pair<int, int>> snake = {
            {5, 5}, 
            {4, 5},
            {3, 5}
        };
        void spawn_apple();
        bool game_over(int new_x, int new_y);
        void print();
        void move();
        void read_keys();
};
