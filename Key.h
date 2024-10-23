#pragma once
#include "Actor.h"
#include "BoxComponent.h"

class Key : public Actor
{
public:
    Key();
    ~Key();
    BoxComponent* getBox() { return box; }

private:
    BoxComponent* box;
};
