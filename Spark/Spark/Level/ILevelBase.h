#pragma once


class LevelManager;


class ILevelBase
{
	friend class LevelManager;

public:
	const char* Name() const;

	//SceneObject* GetWorld() const;

protected:
	const char* m_name;

	LevelManager* m_levelManager;
	//SceneObject* m_world;

protected:
	ILevelBase(const char* _name);
	virtual ~ILevelBase();

protected:
	virtual void BeginPlay() = 0;

	virtual void Tick(float _dt) = 0;
	virtual void Render() = 0;

	virtual void EndPlay() = 0;

};

