module;
#include <ncurses.h>

module cursesview;
import view;
import boxtexture;
import bitmaptexture;
import pixel;
import sprite;
import gameobjectcomponent;
import <vector>;
import <string>;
import <variant>;
import <cmath>;
import <iostream>;

CursesView::CursesView(int width, int height, int maxLines): height{height}, width{width}, maxLines{maxLines} {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak(); 
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    // Draw view border
    for (int i = 0; i < width + 2; ++i){
        mvwaddch(stdscr, 0, i, '-');
        mvwaddch(stdscr, height+1, i, '-');
    }
    for (int i = 0; i < height + 2; ++i){
        mvwaddch(stdscr, i, 0, '|');
        mvwaddch(stdscr, i, width+1, '|');
    }
    mvwaddch(stdscr, 0, 0, '+');
    mvwaddch(stdscr, 0, width+1, '+');
    mvwaddch(stdscr, height+1, 0, '+');
    mvwaddch(stdscr, height+1, width+1, '+');
    for(int i=1; i < height+1; ++i){
        for(int j=1; j < width+1; ++j){
            mvwaddch(stdscr, i, j, ' ');
        }
    }
}

bool CursesView::isInView(int x, int y){
    if(1 <= x && x < width+1 && 1 <= y && y < height+1) return true;
    return false;
}

bool CursesView::isInView(double x, double y, Sprite* sprite){
    int rx = std::lround(x);
    int ry = std::lround(y);
    // Loops through each pixel that would be drawn, and checks if they are in view
    // If any are in view, the sprite is in view
    if(std::holds_alternative<char>(sprite->texture)){
        return isInView(1+rx, 1+ry);
    }
    
    else if(std::holds_alternative<BoxTexture*>(sprite->texture)){
        bool flag = false;
        const BoxTexture *texture = std::get<BoxTexture*>(sprite->texture);
        for(int i=std::lround(texture->top); i<std::lround(texture->bottom); ++i){
            for(int j=std::lround(texture->left); j<std::lround(texture->right); ++j){
                if(isInView(1+rx+j, 1+ry+i)) flag = true;
            }
        }
        return flag;
    }
    
    else if(std::holds_alternative<BitmapTexture*>(sprite->texture)){
        bool flag = false;
        const BitmapTexture *texture = std::get<BitmapTexture*>(sprite->texture);
        for(const Pixel &pixel : *texture){
            if(isInView(1+rx+pixel.x, 1+ry+pixel.y)) flag = true;
        }
        return flag;
    }

    return false;
}

void CursesView::drawSprite(double x, double y, Sprite* sprite) {
    int rx = std::lround(x);
    int ry = std::lround(y);
    if(sprite->getVisibility()){
        // If the texture is a char
        if(std::holds_alternative<char>(sprite->texture)){
            if(isInView(1+rx, 1+ry))
            mvwaddch(stdscr, 1 + ry, 1 + rx, std::get<char>(sprite->texture));
        }
        
        // If the texture is a BoxTexture
        else if(std::holds_alternative<BoxTexture*>(sprite->texture)){
            const BoxTexture *texture = std::get<BoxTexture*>(sprite->texture);
            // Loop through all pixels that fall in the dimensions of BoxTexture
            for(int i=std::lround(texture->top); i<std::lround(texture->bottom); ++i){
                for(int j=std::lround(texture->left); j<std::lround(texture->right); ++j){
                    if(isInView(1+rx+j, 1+ry+i)){
                        mvwaddch(stdscr, 1 + ry + i, 1 + rx + j, texture->fill);
                    }
                }
            }
        }
        
        // If the texture is a BitmapTexture
        else if(std::holds_alternative<BitmapTexture*>(sprite->texture)){
            const BitmapTexture *texture = std::get<BitmapTexture*>(sprite->texture);
            // Loop through all Pixels
            for(const Pixel &pixel : *texture){
                if(isInView(1+rx+pixel.x, 1+ry+pixel.y)){
                    mvwaddch(stdscr, 1 + ry + pixel.y, 1 + rx + pixel.x, pixel.fill);
                }
            }
        }
        refresh();
    }
}

void CursesView::drawText(int line, const std::string &msg) {
    if(line >= 0 && line < maxLines){
        wmove(stdscr, height + 2 + line, 0);
        wclrtoeol(stdscr);
        mvwprintw(stdscr, height + 2 + line, 0, "%s", msg.c_str());
    }
}

void CursesView::clearSprites() {
   for(int i=1; i < height+1; ++i){
        for(int j=1; j < width+1; ++j){
            mvwaddch(stdscr, i, j, ' ');
        }
    }
    refresh();
}

void CursesView::clearText () {
    wmove(stdscr, height + 2, 0);
    for(int i=0; i<maxLines; i++){
        wdeleteln(stdscr);
    }
    refresh();
}
