#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <conio.h>

#include "snake.h"


void Game::spawn_apple() {
    while (true) {
        int new_x = rand() % width;
        int new_y = rand() % height;

        bool inside_snake = false;

        for (int i = 0; i < (int)snake.size(); i++) {
            if (snake[i].first == new_x && snake[i].second == new_y) {
                inside_snake = true;
                break;
            }
        }

        if (!inside_snake) {
            apple_x = new_x;
            apple_y = new_y;
            break;
        }
    }
}

bool Game::game_over(int new_x, int new_y) {
    if (new_x < 0 || new_x >= width || new_y < 0 || new_y >= height) {
        Game_over = true;
        return true;
    }

    for (int i = 1; i < (int)snake.size(); i++) {
        if (snake[i].first == new_x && snake[i].second == new_y) {
            Game_over = true;
            return true;
        }
    }

    return false;
}

void Game::print() {
    while (!Game_over) {
        {
            std::lock_guard<std::mutex> lock(mtx);

            system("cls");


            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    char cell = '*';

                    if (x == apple_x && y == apple_y) {
                        cell = '0';
                    }

                    for (int i = 1; i < (int)snake.size(); i++) {
                        if (snake[i].first == x && snake[i].second == y) {
                            cell = 'x';
                        }
                    }

                    if (snake[0].first == x && snake[0].second == y) {
                        cell = '@';
                    }

                    std::cout << cell << ' ';
                }
                std::cout << '\n';
            }

            std::cout << "\ncontrol: w a s d, quit: q\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }
}

void Game::move() {
    while (!Game_over) {
        {
            std::lock_guard<std::mutex> lock(mtx);

            int new_x = snake[0].first;
            int new_y = snake[0].second;

            if (direction == 'w') new_y--;
            if (direction == 's') new_y++;
            if (direction == 'a') new_x--;
            if (direction == 'd') new_x++;

            if (game_over(new_x, new_y)) {
                break;
            }

            bool ate_apple = (new_x == apple_x && new_y == apple_y);

            if (ate_apple) {
                snake.push_back(snake.back());
            }

            for (int i = (int)snake.size() - 1; i > 0; i--) {
                snake[i] = snake[i - 1];
            }

            snake[0] = {new_x, new_y};

            if (ate_apple) {
                spawn_apple();
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

void Game::read_keys() {
    while (!Game_over) {
        int c = getch();

        std::lock_guard<std::mutex> lock(mtx);

        if (c == 'q') {
            Game_over = true;
        }
        else if (c == 'w' && direction != 's') {
            direction = 'w';
        }
        else if (c == 's' && direction != 'w') {
            direction = 's';
        }
        else if (c == 'a' && direction != 'd') {
            direction = 'a';
        }
        else if (c == 'd' && direction != 'a') {
            direction = 'd';
        }
    }
}
