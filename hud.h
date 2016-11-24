//HUD CLASS
//display hud with help info & control settings
//header file
//ChunpengShao
#include <SDL.h>
#include <vector>
#include "drawable.h"
#include "aaline.h"
#include "ioManager.h"
#include "clock.h"

class Hud {
    public:
        Hud();
        static Hud& getInstance();
        void draw() const;
        //void draw_hpbar() const;
        void draw_line(SDL_Surface*, const Uint32, int, std::vector<Drawable*> ) const;

        void update();

    private:
        const IOManager& io;
        const Clock& clock;
};

