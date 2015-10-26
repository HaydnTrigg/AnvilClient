#include <Client/AnvilClient.hpp>
#include <Utils/Logger.hpp>
#include <Windows.h>

unsigned long __stdcall Initialize(LPVOID)
{
	// Init our logger
	Anvil::Utils::Logger::GetInstance()->Init();

#ifdef _DEBUG
	WriteLog("Command Line Arguments: %s.", GetCommandLine());
#endif

	// Wait for DirectX 9 to get loaded
	while (!GetModuleHandle("d3dx9_43.dll"))
		Sleep(250);

	// Initialize the Anvil Client.
	Anvil::Client::AnvilClient::GetInstance()->Init();

	return S_OK;
}

bool __stdcall DllMain(void* p_Module, unsigned long p_Reason, void* p_Reserved)
{
	if (p_Reason == DLL_PROCESS_ATTACH)
		CreateThread(nullptr, 0, Initialize, nullptr, 0, nullptr);

	return true;
}