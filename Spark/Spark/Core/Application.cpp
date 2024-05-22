#include "Application.h"

#include "Screen.h"
#include "Spark/Gameplay/GameInstance.h"
#include "Spark/Utility/Config.h"

Application::Application(GameInstance* _game)
	: m_config{ new Config }, m_game{ _game }
{
	m_screen = new Screen(m_config);
}

Application::~Application()
{
	delete m_config;
	delete m_game;
	delete m_screen;
}

void Application::Run()
{
	m_config->Load();

	m_screen->Open();
	m_game->m_config = m_config;
	m_game->m_screen = m_screen;

	m_game->Init();

	m_game->BeginPlay();

	while(!m_screen->ShouldQuit())
	{
		m_game->Tick(GetFrameTime());

		m_screen->NewFrame();

		m_game->Render();

		m_screen->EndFrame();
	}

	m_game->EndPlay();
	m_screen->Close();
}
