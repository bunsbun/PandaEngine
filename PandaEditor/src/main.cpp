#include <iostream>
#include <PandaEngineCore/Utils/test.hpp>


int main()
{
	std::cout << "Hello! It's PandaEditor!"<<std::endl;

	PandaEngine::checkGLFW();

	std::cin.get();
}