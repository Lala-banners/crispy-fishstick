#include <Spark/Core/Application.h>

#include "TestGameInstance.h"

int main()
{
	Application* app = new Application(new TestGameInstance);

	app->Run();

	delete app;

	return 0;
}