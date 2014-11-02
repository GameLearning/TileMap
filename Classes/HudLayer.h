#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class HudLayer : public Layer {
public:
    virtual bool init();  
    CREATE_FUNC(HudLayer);
    
    void numCollectedChanged (int numCollected);
private:
    LabelTTF *_label;
};
