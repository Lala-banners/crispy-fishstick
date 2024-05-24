#include "TestLevel.h"

#include "LevelNames.h"
#include "TestActor.h"
#include "Spark/Actors/ActorWorld.h"

TestLevel::TestLevel()
	: ILevelBase(TEST_LEVEL)
{
}

void TestLevel::BeginPlay()
{
	// will only be true if world is real
	if(ActorWorld* world = GetWorld())
	{
		world->SpawnWithTransform(new TestActor, Vec2::zero, 45.f * DEG2RAD, Vec2::one * 2.f);
	}
}

void TestLevel::Tick(float _dt)
{
}

void TestLevel::Render()
{
}

void TestLevel::EndPlay()
{
}
