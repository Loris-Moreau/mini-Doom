#pragma once
#include "Actor.h"
class PlaneActor : public Actor
{
public:
	PlaneActor();
	~PlaneActor();
	class BoxComponent* getBox() { return box; }


private:
	BoxComponent* box;
};

