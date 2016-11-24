#include "hud.h"

Hud& Hud::getInstance() {
    static Hud instance;
    return instance;
}

Hud::Hud():
    io(IOManager::getInstance()),
    clock(Clock::getInstance())
{ }

void Hud::draw() const{
}

void Hud::draw_line(SDL_Surface* screen, const Uint32 RED, int fps, std::vector<Drawable*> sprites) const {
    SDL_Rect rect = {5, 10, 170, 200};
    SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 178, 102));
    SDL_Rect dest = {5, 10, 170, 200};
    SDL_BlitSurface(screen, &rect, screen, &dest);

    Sint16 y1 = 10;
    Sint16 x1 = 5, x2 = 175;
    
    //draw aaline
    Draw_AALine(screen, x1, y1, x2, y1, 2.0f, RED);
    Draw_AALine(screen, x1, y1+200, x2, y1+200, 2.0f, RED);
    Draw_AALine(screen, x2, y1, x2, y1+200, 2.0f, RED);
    Draw_AALine(screen, x1, y1, x1, y1+200, 2.0f, RED);
    
    io.printMessageValueAt("seconds:", clock.getSeconds(), 10, 20);
    io.printMessageValueAt("fps: ", fps, 10, 40);
    io.printMessageValueAt("X-pos:", int(sprites[0]->X()), 10, 60);
    io.printMessageValueAt("Y-pos:", int(sprites[0]->Y()), 10, 80);
    io.printMessageAt("A: Move Left", 10, 100);
    io.printMessageAt("S: Move Down", 10, 120);
    io.printMessageAt("D: Move Right", 10, 140);
    io.printMessageAt("W: Move Up", 10, 160);
    io.printMessageAt("B: Blink 250u right", 10, 180);
}

void Hud::update() {
}

