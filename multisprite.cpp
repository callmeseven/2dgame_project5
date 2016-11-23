#include "multisprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "expMultiSprite.h"

void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

MultiSprite::MultiSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  explosion(NULL),
  m_frames( FrameFactory::getInstance().getFrames(name) ),
  worldWidth(WORLD_WIDTH),
  worldHeight(WORLD_HEIGHT),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(m_frames[0]->getWidth()),
  frameHeight(m_frames[0]->getHeight())
{ }

MultiSprite::MultiSprite(const MultiSprite& s) :
  Drawable(s),
  explosion(NULL),
  m_frames(s.m_frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight )
  { }

MultiSprite& MultiSprite::operator=(const MultiSprite& rhs) {
    Drawable::operator=(rhs);
    explosion = rhs.explosion;
    //m_frames = rhs.m_frames;
    frameWidth = rhs.frameWidth;
    frameHeight = rhs.frameHeight;
    worldWidth = rhs.worldWidth;
    worldHeight = rhs.worldHeight;
    return *this;
}
void MultiSprite::explode(){
    if( explosion ) return;
    explosion = new ExplodingMultiSprite(*this);
}


void MultiSprite::draw() const { 
  if( explosion ){
      explosion->draw();
      return;
  }
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  m_frames[currentFrame]->draw(x, y);
}

void MultiSprite::update(Uint32 ticks) { 

  if( explosion ) {
      explosion->update(ticks);
      if(explosion->chunkCount() == 0) {
          delete explosion;
          explosion = NULL;
      }
      return;
  }
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  

}
