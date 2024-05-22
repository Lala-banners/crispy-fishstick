#pragma once
#include <Spark/Common.h>

class GameInstance;
class Config;
class Screen;

class Application
{
public:
	Application(GameInstance* _game);
	~Application();

	Application(const Application&) = delete;
	Application(Application&&) = delete;

public:
	void Run();

public:
	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) = delete;

private:
	Config* m_config;
	Screen* m_screen;
	GameInstance* m_game; 
};

