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

class LevelManager
{
public:
	LevelManager(Application* _app);
	~LevelManager();

public:
	void Tick(float _dt);
	void Render() const;

	void OpenLevel(const char* _name);
	void ExitLevel(const char* _name);

	void AddLevel(ILevelBase* _level);

	Application* GetApp() const;
	Config* GetConfig() const;

private:
	map<const char*, ILevelBase*> m_levels;
	list<ILevelBase*> m_openLevels;

	list<function<void()>> m_openListChanges;

	Application* m_app;

};