#ifndef POOL__H
#define POOL__H
#include <list>
#include "sprite.h"
#include <SDL.h>
#include "player.h"

class Bullet: public Sprite {
    public:
        Bullet(const std::string& s);
        void reset();
        ~Bullet() {} ;
        void end_life();
        bool is_alive() {return life;};
        void set_lifetime();
        unsigned int get_lifetime(){ return life_time; }
    private:
        bool life;
        unsigned int life_time;

};
       
class Pool {
    public:
        
        static Pool& getInstance();
        Pool(); 
        Bullet* getBullet();

        ~Pool() { }
        void returnBullet(Bullet* s);
        void draw_b() const;
        void update_b(Uint32 ticks);
        void shoot(Drawable* s);
        void printsize();
        int get_inuse_number() {return b_inuse.size();}
        int get_bullet_number() {return bullets.size();}

    private:
        std::list<Bullet*> bullets;
        std::list<Bullet*> b_inuse;
        
};

#endif
