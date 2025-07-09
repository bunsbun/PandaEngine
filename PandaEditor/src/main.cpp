#pragma once
#include <iostream>
#include <PandaEngineCore/Application.hpp>
#include "memory"

class MyApp : public PandaEngine::Application
{
	virtual void OnUpdate() override
	{
		//std::cout << "Update frame:" << ++frame << std::endl;
	}

	int frame = 0;

	   

};




int main()
{


	auto myApp = std::make_unique<MyApp>();

	int returnCode = myApp->StartApplicationWindow(1024, 768, "My first App");

	std::cin.get();


	return returnCode;
}