import application;
#include <memory>
#include <iostream>

int main()
{
	auto app = std::make_unique<Application>();
	int returnCode = app->StartApplicationWindow(1024, 768, "Window");
	std::cin.get();

	return 0;
}