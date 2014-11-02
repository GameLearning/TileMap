#pragma once
#include "cocos2d.h"
#include "HudLayer.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    virtual bool onTouchBegan(CCTouch *touch, CCEvent *event);
    virtual void onTouchEnded(CCTouch *touch, CCEvent *event);
    
private:
    void setViewPointCenter(Vec2 position);
    Vec2 tileCoordForPosition(Vec2 position);
    void setPlayerPosition(Vec2 position);
    bool isProp(ValueMap valueMap, std::string string);
    
    TMXTiledMap *_tileMap;
    TMXLayer *_background;
    TMXLayer *_meta;
    TMXLayer *_foreground;
    Sprite *_player;
    
    Size _visibleSize;
    
    HudLayer *_hud;
    int _numCollected;
};