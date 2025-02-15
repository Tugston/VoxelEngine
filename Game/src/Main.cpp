#include<Core/Core.h>
#include<Core/Logger.h>


#include <spdlog/fmt/ostr.h>

#include<Core/Header.h>

int main()
{
	int number = 1;
	Engine::Logger::Init();
	Engine::Logger::LogMessage(Engine::Logger::LogType::Message, "Test");
	Engine::Logger::LogMessage(Engine::Logger::LogType::Error, "Error");
	Engine::Logger::LogMessage(Engine::Logger::LogType::Warning, "Warning {}", number);
	Engine::Logger::LogMessage(Engine::Logger::LogType::Critical, "Critical {}", number);

	Engine::func();
}