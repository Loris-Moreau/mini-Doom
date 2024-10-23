#pragma once
#include "UIScreen.h"

class HUD : public UIScreen
{
public:
	HUD();
	~HUD();

	void update(float dt) override;
	void updateHP(float dt);
	void updateCondition(float dt);
	void draw(Shader& shader) override;

	void addTargetComponent(class TargetComponent* tc);
	void removeTargetComponent(TargetComponent* tc);


protected:
	void updateCrosshair(float deltaTime);
	void updateRadar(float deltaTime);

	Texture* crosshair;
	Texture* crosshairEnemy;
	Texture* radar;
	Texture* blipTex;
	Texture* radarArrow;

	Texture* healthBar;
	Texture* healthBar1;
	Texture* healthBar2;
	Texture* healthBar3;
	
	Texture* Empty;
	Texture* GameOver;
	Texture* Finished;
	Texture* PressE;
	

	std::vector<TargetComponent*> targetComponents;
	bool isTargetingEnemy;
	bool isDead = false;
	vector<Vector2> blips;
	float radarRange;
	float radarRadius;
};

