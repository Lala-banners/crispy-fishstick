#pragma once

#include <list>
#include <map>
#include <functional>

using std::list;
using std::map;
using std::function;

class Application;
class ILevelBase;
class Config;
class Screen;
class GameInstance;

class LevelManager
{
	friend class GameInstance; // friends with benefits

public:
	LevelManager(GameInstance* _game);
	~LevelManager();

public:
	void OpenLevel(const char* _name);
	void ExitLevel(const char* _name);

	void AddLevel(ILevelBase* _level);

	Config* GetConfig() const;
	Screen* GetScreen() const;

private:
	map<const char*, ILevelBase*> m_levels;
	list<ILevelBase*> m_openLevels;

	list<function<void()>> m_openListChanges;

	Config* m_config;
	Screen* m_screen;

private:
	void Tick(float _dt);
	void Render() const;
};