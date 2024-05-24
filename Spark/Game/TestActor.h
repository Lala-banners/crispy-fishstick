#pragma once

#include <Spark/Actors/Actor.h>

class TestActor final : public Actor
{
public:
	TestActor();

protected:
	void OnBeginPlay() override;

	void OnTick(float _dt) override;
	void OnRender() override;

private:
	float m_speed;
};

