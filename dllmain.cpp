#include "dllmain.hpp"

typedef INT(WINAPI* m_pUpdate)(ISystem*, INT, INT);
m_pUpdate oUpdate;

VMTHookManager vmtHook;

INT WINAPI hkUpdate(ISystem* pSystem, INT iInfo, INT iPause)
{
	startModule();
	return oUpdate(pSystem, iInfo, iPause);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hModule);

    if (dwReason == 1)
    {
		vmtHook.bInitialize((PDWORD64*)SSystemGlobalEnvironment::Singleton()->GetISystem());
		oUpdate = (m_pUpdate)vmtHook.dwHookMethod((DWORD64)hkUpdate, 4);
    }

    return TRUE;
}

