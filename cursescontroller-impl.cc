module;
#include <ncurses.h>
#include <clocale>

module cursescontroller;
import controller;

char CursesController::getInput(){
    return getch();
}
