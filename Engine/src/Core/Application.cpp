#include "Header.h"

namespace Engine
{
	ENGINE_API int func()
	{
		Engine::Logger::LogMessage(Engine::Logger::LogType::Message, "Engine Logger Call");
		return 0;
	}
}