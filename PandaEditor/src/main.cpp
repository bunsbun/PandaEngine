import application;
#include <memory>
#include <iostream>
//class MyApp : Application
//{
//	virtual void OnUpdate() override
//	{
//		//std::cout << "Update frame:" << ++frame << std::endl;
//	}
//
//	int frame = 0;
//};

int main()
{
	auto app = std::make_unique<Application>();
	int returnCode = app->StartApplicationWindow(1024, 768, "Window");
	std::cin.get();

	return 0;
}