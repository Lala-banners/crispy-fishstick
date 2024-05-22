#include "GameInstance.h"

#include "Spark/Level/LevelManager.h"

GameInstance::GameInstance()
	: m_config{ nullptr }, m_screen{ nullptr }, m_levelManager{ nullptr }
{
}

// Only need to delete level manager - game gets closed
GameInstance::~GameInstance()
{
	delete m_levelManager;
	m_levelManager = nullptr;
}

void GameInstance::BeginPlay() { }

void GameInstance::EndPlay() { }

Config* GameInstance::GetConfig() const
{
	return m_config; // Returns pointer to Config*
}

Screen* GameInstance::GetScreen() const
{
	return m_screen; // Returns pointer to Screen*
}

LevelManager* GameInstance::GetLevelManager() const
{
	return m_levelManager; // Returns pointer to LevelManager*
}

void GameInstance::Init(Application* _app)
{
	m_levelManager = new LevelManager(_app);
}

void GameInstance::Tick(float _dt) const
{
	m_levelManager->Tick(_dt);
}

void GameInstance::Render() const
{
	m_levelManager->Render();
}