#pragma once

#include <Spark/Common.h>
#include <Spark/Maths/Vec2.h>

#include <functional>
using std::function;

class Actor;
class Config;
class Screen;

class ActorWorld
{
	friend class ILevelBase;
	friend class LevelManager;

	// delete operators to stop from copying + moving memory (safety reasons) 
public:
	ActorWorld(const ActorWorld&) = delete;
	ActorWorld(ActorWorld&&) = delete;

public:
	void Spawn(Actor* _actor, Actor* _parent = nullptr); // Auto parent
	void SpawnWithTransform(Actor* _actor, const Vec2& _pos, float _rot, const Vec2& _scale, Actor* _parent = nullptr); // Give automatic values for easier at specific position
	void Eradicate(Actor* _actor); 

public:
	ActorWorld& operator=(const ActorWorld&) = delete;
	ActorWorld& operator=(ActorWorld&&) = delete;

private:
	// Lambda function WTF
	list<function<void()>> m_worldChanges;

	Actor* m_root;
	Config* m_config;
	Screen* m_screen;

private:
	ActorWorld();
	~ActorWorld();

private:
	void Tick(float _dt);
	void Render();

	void AddActor(Actor* _actor, Actor* _parent);
	void RemoveActor(Actor* _actor);
};

