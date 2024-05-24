#include "ILevelBase.h"

#include "Spark/Actors/Actor.h"
#include "Spark/Actors/ActorWorld.h"
#include "Spark/Core/Screen.h"
#include "Spark/Utility/Config.h"

const char* ILevelBase::Name() const
{
	return m_name;
}

ActorWorld* ILevelBase::GetWorld() const
{
	return m_world;
}

ILevelBase::ILevelBase(const char* _name)
	: m_name{ _name }, m_levelManager{ nullptr }, m_config{ nullptr }, m_screen{ nullptr }, m_world{ new ActorWorld },
	  m_isConfigured{ false }
{
}

ILevelBase::~ILevelBase()
{
	m_name = nullptr;
	m_levelManager = nullptr;

	delete m_world;
	m_world = nullptr;
}

Config* ILevelBase::GetConfig() const
{
	return m_config;
}

Screen* ILevelBase::GetScreen() const
{
	return m_screen;
}

/// Default Level configurations.
/// @param _config position, rotation, scale of the world.
/// @param _screen size of the screen.
void ILevelBase::Configure(Config* _config, Screen* _screen)
{
	if (m_isConfigured)
		return;

	m_config = _config;
	m_screen = _screen;

	const Vec2 worldOffsetFactor = m_config->GetValue<Vec2>("world", "offsetFactor");
	const Vec2 worldScale = Vec2::one * m_config->GetValue<float>("world", "scale");

	float sW, sH;
	m_screen->GetSize(&sW, &sH);

	const Vec2 worldCenter = Vec2(sW * worldOffsetFactor.x, sH * worldOffsetFactor.y);

	m_world->m_config = _config;
	m_world->m_screen = _screen;
	m_world->m_root->SetActorTransform(Mat3::CreateTransform(worldCenter, 0, &worldScale));

	m_isConfigured = true;
}
