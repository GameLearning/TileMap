#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    _visibleSize = Director::getInstance()->getVisibleSize();
    _tileMap = TMXTiledMap::create("TileMap.tmx");
    _background = _tileMap->layerNamed("Background");
    _meta = _tileMap->layerNamed("Meta");
    _meta->setVisible(false);
    this->addChild(_tileMap);
    
    TMXObjectGroup *objectGroup = _tileMap->objectGroupNamed("Objects");
    if(objectGroup == NULL){
        CCLog("tile map has no objects object layer");
        return false;
    }
    
    auto spawnPoint = objectGroup->getObject("SpawnPoint");
    
    int x = ((String)spawnPoint.at("x").asString()).intValue();
    int y = ((String)spawnPoint.at("y").asString()).intValue();
    
    _player = Sprite::create("Player.png");
    _player->setPosition(Vec2(x,y));
    this->addChild(_player);
    this->setViewPointCenter(_player->getPosition());
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void HelloWorld::setViewPointCenter(Vec2 position){
    int x = MAX(position.x, _visibleSize.width/2);
    int y = MAX(position.y, _visibleSize.height/2);
    
    x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - _visibleSize.width / 2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - _visibleSize.height/2);
    Vec2 actualPosition = Vec2(x, y);
    
    Vec2 centerOfView = Vec2(_visibleSize.width/2, _visibleSize.height/2);
    Vec2 viewPoint = centerOfView - actualPosition;
    this->setPosition(viewPoint);
}

bool HelloWorld::onTouchBegan(Touch *touch, Event * event){
    return true;
}
void HelloWorld::onTouchEnded(Touch *touch, Event * event){
    Vec2 touchLocation = touch->getLocation();
    touchLocation = this->convertToNodeSpace(touchLocation);
    
    Vec2 playerPos = _player->getPosition();
    Vec2 diff = touchLocation -  playerPos;
    
    if ( abs(diff.x) > abs(diff.y) ) {
        if (diff.x > 0) {
            playerPos.x += _tileMap->getTileSize().width;
        } else {
            playerPos.x -= _tileMap->getTileSize().width;
        }
    } else {
        if (diff.y > 0) {
            playerPos.y += _tileMap->getTileSize().height;
        } else {
            playerPos.y -= _tileMap->getTileSize().height;
        }
    }
    
    // safety check on the bounds of the map
    if (playerPos.x <= (_tileMap->getMapSize().width * _tileMap->getTileSize().width) &&
        playerPos.y <= (_tileMap->getMapSize().height * _tileMap->getTileSize().height) &&
        playerPos.y >= 0 &&
        playerPos.x >= 0 )
    {
        this->setPlayerPosition(playerPos);
    }
 
    this->setViewPointCenter(_player->getPosition());
}

void HelloWorld::setPlayerPosition(Vec2 position){
    Vec2 tileCoord = tileCoordForPosition(position);
    int tileGid = _meta->getTileGIDAt(tileCoord);
    
    if(tileGid){
        CCLOG("1");
        auto properties = _tileMap->getPropertiesForGID(tileGid);
        
        CCLOG("2");
        if(!properties.isNull()){
            CCLOG("3");
            if(properties.asValueMap().at("Collidable").asString().compare("True") == 0){
                CCLOG("4");
                return;
            }
        }
    }
    _player->setPosition(position);
}

Vec2 HelloWorld::tileCoordForPosition(Vec2 position)
{
    int x = position.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
    return Vec2(x, y);
}