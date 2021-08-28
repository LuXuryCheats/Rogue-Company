#include "utils.h"
#include <iostream>

namespace render
{
	void render_hud(void* hud_hook)
	{
		auto UCanvas = *(uint64_t*)((uint64_t)hud_hook + utils::canvas::ucanvas);
		// removed wasnt mine
	}
}

void initalize_hooks()
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);

	// remvoed pattern scanner wasnt mine
	auto sussybaka = Scan::Pattern("", "");
	text_hook = (void**)sussybaka;

	sussybaka = Scan::Pattern("", "");
	line_hook = (void**)sussybaka;
}

bool __stdcall DllMain(void* hModule, unsigned long ul_reason_for_call, void* lpReserved)
{
	if (ul_reason_for_call == 1)
	{
		initalize_hooks();
		return TRUE;
	}
	return 1;
}