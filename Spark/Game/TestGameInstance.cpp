#include "TestGameInstance.h"

#include <iostream>

#include "LevelNames.h"
#include "TestLevel.h"
#include "Spark/Level/LevelManager.h"

void TestGameInstance::BeginPlay()
{
	if(LevelManager* levelMan = GetLevelManager())
	{
		levelMan->AddLevel(new TestLevel);

		levelMan->OpenLevel(TEST_LEVEL);
	}
}

void TestGameInstance::EndPlay()
{
	std::cout << "End play!\n";
}
