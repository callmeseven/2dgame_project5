#include "pool.h"
#include <iostream>

Bullet::Bullet(const std::string& s) :
    Sprite(s),
    life(false),
    life_time(0)
{ }

void Bullet::reset(){
    life_time = 0;
    life = false;

}

void Bullet::end_life(){
    life = false;
}

void Bullet::set_lifetime(){
    life_time = SDL_GetTicks();
    life = true;
}


Pool& Pool::getInstance(){
    static Pool instance;
    return instance;
}

Pool::Pool() : bullets(), b_inuse() {
    for (int i=0; i<6; i++)
    {
      bullets.push_back(new Bullet("bullet"));
    }
}

Bullet* Pool::getBullet(){
    Bullet* temp = bullets.front();
    bullets.pop_front();
    return temp;
}

void Pool::returnBullet(Bullet* s) {
    s->reset();
    bullets.push_back(s);
    std::cout << "bullet size after return" << bullets.size() << std::endl;
}

void Pool::draw_b() const {
    std::list<Bullet*>::const_iterator ptr = b_inuse.begin();
    while ( ptr != b_inuse.end() ){
        if((*ptr)->is_alive())
        (*ptr)->Sprite::draw();
        ptr++;
    }
}

void Pool::update_b(Uint32 ticks) {
   if(b_inuse.size() != 0){
        std::list<Bullet*>::iterator ptr = b_inuse.begin();
        while (ptr != b_inuse.end() ) {
            if (SDL_GetTicks() - (*ptr)->get_lifetime() > 3000)
                (*ptr)->end_life();
            (*ptr)->Sprite::update(ticks);
            if(!(*ptr)->is_alive()){
                (*ptr)->reset();
                std::list<Bullet*>::iterator temp = ptr;
                bullets.push_back((*ptr));
                ptr++;
                b_inuse.erase(temp);
            }
            else{
                ptr++;
            }

        }
    }
}

void Pool::shoot(Drawable* s) {
    
    if (bullets.size()>0){
        if(b_inuse.size()<6){
            b_inuse.push_back((*this).getBullet());
            b_inuse.back()->set_lifetime();
            b_inuse.back()->Drawable::velocityX(abs(s->velocityX())+300);
            b_inuse.back()->Drawable::velocityY(0);
            b_inuse.back()->Drawable::X(s->X()+10);
            b_inuse.back()->Drawable::Y(s->Y()+10);
        }
    }
}

void Pool::printsize() {

    std::cout<< bullets.size() << std::endl;
    std::cout<< b_inuse.size() << std::endl;
}
