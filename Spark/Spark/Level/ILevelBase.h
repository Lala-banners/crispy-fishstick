#pragma once

class LevelManager;
class Config;
class Screen;
class ActorWorld;

class ILevelBase
{
	friend class LevelManager;

public:
	const char* Name() const;

	ActorWorld* GetWorld() const;

protected:
	const char* m_name;

	LevelManager* m_levelManager;

protected:
	ILevelBase(const char* _name);
	virtual ~ILevelBase();

protected:
	Config* GetConfig() const;
	Screen* GetScreen() const;

protected:
	virtual void BeginPlay() = 0;
	virtual void Tick(float _dt) = 0;
	virtual void Render() = 0;

	virtual void EndPlay() = 0;

private:
	Config* m_config;
	Screen* m_screen;
	ActorWorld* m_world;

	bool m_isConfigured;

private:
	void Configure(Config* _config, Screen* _screen);
};

