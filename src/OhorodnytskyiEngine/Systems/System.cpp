#include "OhorodnytskyiEngine/Systems/System.h"

namespace OhorodnytskyiEngine
{
	void System::Start()
	{
		_running = true;
	}

	void System::Stop()
	{
		_running = false;
	}
}