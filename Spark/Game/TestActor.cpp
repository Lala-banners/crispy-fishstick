#include "TestActor.h"

#include "Spark/Utility/Config.h"

// Player variables here only!

TestActor::TestActor()
	: m_speed{ 0.f }
{
}

void TestActor::OnBeginPlay()
{
	// if assigned pointer is valid
	if(Config* config = GetConfig())
	{
		m_speed = config->GetValue<float>("player", "speed");
	}
}

void TestActor::OnTick(float _dt)
{
	const Vec2 movement
	{
		static_cast<float>(IsKeyDown(KEY_D)) - static_cast<float>(IsKeyDown(KEY_A)),
		static_cast<float>(IsKeyDown(KEY_S)) - static_cast<float>(IsKeyDown(KEY_W)),
	};

	UpdateActorTransform(Mat3::CreateTranslation(movement * _dt * m_speed));

	const float rotation = static_cast<float>(IsKeyDown(KEY_E)) - static_cast<float>(IsKeyDown(KEY_Q));

	SetActorRotation(GetActorRotation() + rotation * _dt * 90.f);
}

void TestActor::OnRender()
{
	const Vec2 pos = GetActorPosition();
	const Vec2 scale = GetActorScale();
	const float rot = GetActorRotation();

	Rectangle rect
	{
		pos.x,
		pos.y,
		scale.x,
		scale.y
	};

	DrawRectanglePro(rect, scale * .5f, rot, BLACK);
}