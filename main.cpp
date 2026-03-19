#include <C:\Users\016Aip25_2\snake.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>

int main() {
    srand(time(0));

    Game game;
    game.spawn_apple();

    std::thread t1(&Game::print, &game);
    std::thread t2(&Game::move, &game);
    std::thread t3(&Game::read_keys, &game);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "Game over!\n";

    return 0;
}