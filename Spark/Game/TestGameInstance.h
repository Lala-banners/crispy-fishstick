#pragma once

#include <Spark/Gameplay/GameInstance.h>

class TestGameInstance : public GameInstance
{
public:
	void BeginPlay() override;
	void EndPlay() override;
};

