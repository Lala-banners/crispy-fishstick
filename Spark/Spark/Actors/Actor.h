#pragma once

#include <Spark/Common.h>
#include <Spark/Maths/Vec2.h>
#include <Spark/Maths/Mat3.h>

#include <functional>
using std::function;

class Config;
class Screen;

class Actor
{
	friend class ActorWorld;

public:
	Actor();
	virtual ~Actor(); // will be automatically called by children

	Actor(const Actor&) = delete;
	Actor(Actor&&) = delete;

	// Functions that cover functionality for all actor information
public:
	Vec2 GetActorPosition() const;
	float GetActorRotation() const;
	Vec2 GetActorScale() const;

	void SetActorPosition(const Vec2& _pos);
	void SetActorRotation(float _rot);
	void SetActorScale(const Vec2& _scale);

	void SetActorTransform(const Mat3& _transform);
	void UpdateActorTransform(const Mat3& _transform);

public:
	Actor& operator=(const Actor&) = delete;
	Actor& operator=(Actor&&) = delete;

protected:
	virtual void OnBeginPlay();

	virtual void OnTick(float _dt);
	virtual void OnRender();

	virtual void OnEndPlay();

	Actor* Parent() const;
	void SetParent(Actor* _newParent);

	Mat3& Transform();
	Mat3 GlobalTransform() const;

	Config* GetConfig() const;
	Screen* GetScreen() const;

private:
	list<function<void()>> m_childListChanges;

	Actor* m_parent;
	list<Actor*> m_children;

	Mat3 m_transform;

	Config* m_config;
	Screen* m_screen;

private:
	void ApplyListChanges();

	void Tick(float _dt);
	void Render();

	void AddChild(Actor* _child);
	void RemoveChild(Actor* _child);

};

