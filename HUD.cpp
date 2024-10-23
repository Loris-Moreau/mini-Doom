#include "HUD.h"
#include "Assets.h"
#include "Game.h"
#include "TargetComponent.h"
#include "FPSActor.h"

HUD::HUD():
	UIScreen(),
	isTargetingEnemy(false),
	radarRange(2000.0f),
	radarRadius(92.0f)
{
	crosshair = &Assets::getTexture("Crosshair");
	crosshairEnemy = &Assets::getTexture("CrosshairRed");
	radar = &Assets::getTexture("Radar");
	blipTex = &Assets::getTexture("Blip");
	radarArrow = &Assets::getTexture("RadarArrow");
	
	healthBar = &Assets::getTexture("healthBar");
	healthBar1 = &Assets::getTexture("healthBar1");
	healthBar2 = &Assets::getTexture("healthBar2");
	healthBar3 = &Assets::getTexture("healthBar3");
	
	GameOver = &Assets::getTexture("GameOver");
	Finished = &Assets::getTexture("Finished");
	Empty = &Assets::getTexture("Empty");
	PressE = &Assets::getTexture("PressE");
}

HUD::~HUD()
{
}

void HUD::update(float dt)
{
	UIScreen::update(dt);
	updateCrosshair(dt);
	updateRadar(dt);
	updateHP(dt);
	updateCondition(dt);
}

void HUD::updateHP(float dt)
{
	switch (Game::instance().getPlayer()->getHP())
	{
	case 3:
		healthBar = &Assets::getTexture("healthBar");
		break;
	case 2:
		healthBar = &Assets::getTexture("healthBar1");
		break;
	case 1:
		healthBar = &Assets::getTexture("healthBar2");
		break;
	default:
		healthBar = &Assets::getTexture("GameOver");
		isDead = true;
		break;	
	}

	
}

void HUD::updateCondition(float dt)
{
	if (Game::instance().getPlayer()->getEnd() == true)
	{
		Finished = &Assets::getTexture("Finished");
	}
	else
	{
		Finished = &Assets::getTexture("Empty");
	}
}

void HUD::draw(Shader& shader)
{
	Texture* cross = isTargetingEnemy ? crosshairEnemy : crosshair;
	drawTexture(shader, cross, Vector2::zero, 2.0f);

	const Vector2 radarPosition{ -390.0f, 275.0f };
	drawTexture(shader, radar, radarPosition, 1.0f);
	for (Vector2& blip : blips)
	{
		drawTexture(shader, blipTex, radarPosition + blip, 1.0f);
	}
	drawTexture(shader, radarArrow, radarPosition);
	drawTexture(shader, PressE, Vector2(-210.0f, -350.0f), 0.4f);
	if(!isDead)
	{
		drawTexture(shader, healthBar, Vector2(-410.0f, -345.0f), 0.5f);
	}
	else
	{
		drawTexture(shader, healthBar, Vector2(0.0f, 0.0f), 0.95f);
	}
	drawTexture(shader, Finished, Vector2(0.0f, 0.0f), 0.95f);
}

void HUD::addTargetComponent(TargetComponent* tc)
{
	targetComponents.emplace_back(tc);
}

void HUD::removeTargetComponent(TargetComponent* tc)
{
	auto iter = std::find(begin(targetComponents), end(targetComponents), tc);
	targetComponents.erase(iter);
}

void HUD::updateCrosshair(float dt)
{
	// Reset to regular cursor
	isTargetingEnemy = false;
	// Make a line segment
	const float cAimDist = 5000.0f;
	Vector3 start, dir;
	Game::instance().getRenderer().getScreenDirection(start, dir);
	LineSegment l(start, start + dir * cAimDist);
	// Segment cast
	PhysicsSystem::CollisionInfo info;
	if (Game::instance().getPhysicsSystem().segmentCast(l, info))
	{
		for (auto tc : targetComponents)
		{
			if (&tc->getOwner() == info.actor)
			{
				isTargetingEnemy = true;
				break;
			}
		}
	}
}

void HUD::updateRadar(float dt)
{
	// Clear blip positions from last frame
	blips.clear();

	// Convert player position to radar coordinates (x forward, z up)
	Vector3 playerPos = Game::instance().getPlayer()->getPosition();
	Vector2 playerPos2D{ playerPos.y, playerPos.x };
	// Ditto for player forward
	Vector3 playerForward = Game::instance().getPlayer()->getForward();
	Vector2 playerForward2D{ playerForward.x, playerForward.y };

	// Use atan2 to get rotation of radar
	float angle = Maths::atan2(playerForward2D.y, playerForward2D.x);
	// Make a 2D rotation matrix
	Matrix4 rotMat = Matrix4::createRotationZ(angle);
	
	// Get positions of blips
	for (auto tc : targetComponents)
	{
		Vector3 targetPos = tc->getOwner().getPosition();
		Vector2 actorPos2D{ targetPos.y, targetPos.x };

		// Calculate vector between player and target
		Vector2 playerToTarget = actorPos2D - playerPos2D;

		// See if within range
		if (playerToTarget.lengthSq() <= (radarRange * radarRange))
		{
			// Convert playerToTarget into an offset from
			// the center of the on-screen radar
			Vector3 blipPosition{ playerToTarget.x, playerToTarget.y, 0.0f };
			blipPosition *= radarRadius / radarRange;

			// Rotate blipPosition
			blipPosition = Vector3::transform(blipPosition, rotMat);
			blips.emplace_back(Vector2(blipPosition.x, blipPosition.y));
		}
	}
	
}