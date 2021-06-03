﻿#include "dllmain.hpp"

typedef INT(WINAPI* m_pUpdate)(ISystem*, INT, INT);
m_pUpdate oUpdate;

VMTHookManager* vmtHook = new VMTHookManager;

INT APIENTRY hkUpdate(ISystem* pSystem, INT iInfo, INT iPause)
{
	startModule();
	return oUpdate(pSystem, iInfo, iPause);
}

// for using ddraw method u need create void where u set hook on isystem, and then in if (dwReason == 1) createthread

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == 1)
    {
		vmtHook->bInitialize((PDWORD64*)SSystemGlobalEnvironment::Singleton()->GetISystem());
		oUpdate = (m_pUpdate)vmtHook->dwHookMethod((DWORD64)hkUpdate, 4);
    }

    return TRUE;
}

