#include "HudLayer.h"
USING_NS_CC;

bool HudLayer::init()
{
    if (Layer::init()) {
        Size winSize = Director::getInstance()->getWinSize();
 
        _label = LabelTTF::create("0", "Verdana-Bold", 18.0);
        _label->setColor(Color3B(0,0,0));
 
        int margin = 10;
        _label->setPosition(Vec2(winSize.width - (_label->getContentSize().width/2) - margin, _label->getContentSize().height/2 + margin));
        this->addChild(_label);
    }
 
    return true;
}

void HudLayer::numCollectedChanged(int numCollected)
{
    String *labelCollected = String::createWithFormat("%d",numCollected);
    _label->setString(labelCollected->getCString());
}