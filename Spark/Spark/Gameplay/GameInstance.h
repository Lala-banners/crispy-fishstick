#pragma once
#pragma region Pre-declarations
class Config;
class Screen;
class LevelManager;
#pragma endregion

// Bridge between framework and game project (entry point of the program)
class GameInstance
{
	// Specify friend (if predeclared, no need for [friend class name])
	// best practise anyway
	friend class Application;
	friend class LevelManager;

	// Marked for delete (only in public) to save memory being moved or copied by functions that are not being used.
public:
	GameInstance(const GameInstance&) = delete;
	GameInstance(GameInstance&&) = delete;

public:
	GameInstance& operator=(const GameInstance&) = delete;
	GameInstance& operator=(GameInstance&&) = delete;

protected:
	GameInstance();
	virtual ~GameInstance();

protected:
	virtual void BeginPlay();
	virtual void EndPlay();

	// Owned and controlled by the Application but being used in GameInstance (except LevelManager)
	Config* GetConfig() const;
	Screen* GetScreen() const;
	LevelManager* GetLevelManager() const;

private:
	Config* m_config;
	Screen* m_screen;
	LevelManager* m_levelManager;

private:
	void Init();
	void Tick(float _dt) const;			// Calls LevelManager Tick()
	void Render() const;					// Calls LevelManager Render()
};

