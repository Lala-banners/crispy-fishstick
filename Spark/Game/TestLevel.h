#pragma once

#include <Spark/Level/ILevelBase.h>

class TestLevel final : public ILevelBase
{
public:
	TestLevel();

protected:
	void BeginPlay() override;
	void Tick(float _dt) override;
	void Render() override;
	void EndPlay() override;
};