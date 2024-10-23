#pragma once
#include <vector>
#include "Actor.h"
#include "CubeActor.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Vector2.h"
#include "RendererOGL.h"
#include "InputSystem.h"
#include "PhysicsSystem.h"
#include "PlaneActor.h"
#include "HUD.h"
#include "Door.h"
#include "KeyDoor.h"
#include "Teleporter.h"
#include "EndGame.h"
#include "Key.h"
#include "KeyDoor.h"

using std::vector;

enum class GameState
{
	Gameplay, Pause, Quit
};

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() : state(GameState::Gameplay), isUpdatingActors(false), fps(nullptr), crosshair(nullptr) {}

public:
	bool initialize();
	std::vector<std::vector<int>> loadLevel(const std::string& filename);
	void load();
	void loop();
	void unload();
	void close();

	GameState getState() const { return state; }
	void setState(GameState stateP);

	void addActor(Actor* actor);
	void removeActor(Actor* actor);
	RendererOGL& getRenderer() { return renderer; }
	
	PhysicsSystem& getPhysicsSystem() { return physicsSystem; }
	InputSystem& getInputSystem() { return inputSystem; }
	const vector<class UIScreen*>& getUIStack() { return UIStack; }
	void pushUI(class UIScreen* screen);
	HUD* getHUD() { return hud; }

	// Game-specific
	void addPlane(class PlaneActor* plane);
	void removePlane(class PlaneActor* plane);
	void addCubes(class CubeActor* cube);
	void addDoors(class Door* door);
	void addKeyDoors(class KeyDoor* keydoor);
	void removeCubes(class CubeActor* cube);
	vector<PlaneActor*>& getPlanes() { return planes; }
	vector<CubeActor*>& getCubes() { return cubes; }
	vector<Door*>& getDoors() { return doors; }
	vector<KeyDoor*>& getKeyDoors() { return keyDoors; }
	Teleporter* getTPs() { return teleporter; }
	EndGame* getEnd() { return endGame; }
	Key* getKey() { return key; }
	class FPSActor* getPlayer() { return fps; }

private:
	void processInput();
	void update(float dt);
	void render();

	GameState state;
	Window window;
	RendererOGL renderer;

	InputSystem inputSystem;
	PhysicsSystem physicsSystem;
	vector<class UIScreen*> UIStack;
	HUD* hud;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	// Game specific

	class FPSActor* fps;
	class SpriteComponent* crosshair;
	vector<CubeActor*> cubes;
	vector<Door*> doors;
	vector<KeyDoor*> keyDoors;
	vector<PlaneActor*> planes;
	Teleporter* teleporter;
	EndGame* endGame;
	Key* key;
};

