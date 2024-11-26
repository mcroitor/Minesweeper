#include "engine.h"

int main(int argc, char* argv[]){
    int width = 20;
    int height = 10;
    int nr_mines = 20;
    if(argc == 4){
        width = std::stoi(argv[1]);
        height = std::stoi(argv[2]);
        nr_mines = std::stoi(argv[3]);
    }
    Engine engine(width, height, nr_mines);
    engine.Run();
    return 0;
}