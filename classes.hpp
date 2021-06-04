#pragma once

enum Cry_DATA : uintptr_t
{
	ssge = 0x141E62C98, // update it
	igf = 0x14217C278   // update it
};

class SSystemGlobalEnvironment
{
public:
	ISystem* GetISystem() { return *(ISystem**)((uintptr_t)this + 0xF0); }
	IEntitySystem* GetIEntitySystem() { return *(IEntitySystem**)((uintptr_t)this + 0xE0); }
	I3DEngine* GetI3DEngine() { return *(I3DEngine**)((uintptr_t)this + 0x100); }

	static SSystemGlobalEnvironment* Singleton()
	{
		return *(SSystemGlobalEnvironment**)ssge;
	}
};

class IGameFramework
{
public:
	bool GetClientActor(IActor** pIActor)
	{
		return VIRTUAL<bool(__thiscall*)(PVOID, IActor**)>(this, 142)(this, pIActor);
	}

	IActorSystem* GetIActorSystem()
	{
		return VIRTUAL<IActorSystem* (__thiscall*)(PVOID)>(this, 25)(this);
	}

	static IGameFramework* Singleton()
	{
		return *(IGameFramework**)igf;
	}
};

class I3DEngine
{
public:
	void SetPostEffectParam(const char* pParam, float fValue, bool bForceValue = false)
	{
		return VIRTUAL<void(__thiscall*)(PVOID, const char*, float, bool)>(this, 144)(this, pParam, fValue, bForceValue);
	}
};

class IEntitySystem
{
public:
	IEntityIt* GetIEntityIterator()
	{
		return VIRTUAL<IEntityIt* (__thiscall*)(PVOID)>(this, 21)(this);
	}
};

class IEntityIt
{
public:
	IEntity* Next()
	{
		return VIRTUAL<IEntity* (__thiscall*)(PVOID)>(this, 6)(this);
	}
};

class IEntity
{
public:

	EntityId GetId()
	{
		return VIRTUAL<EntityId(__thiscall*)(PVOID)>(this, 1)(this);
	}

	IEntityProxy* GetIEntityProxy(EEntityProxy proxy)
	{
		return VIRTUAL<IEntityProxy* (__thiscall*)(PVOID, EEntityProxy)>(this, 59)(this, proxy);
	}
};

class IEntityProxy
{
public:

	void SetHUDSilhouettesParams(float a, float r, float g, float b)
	{
		VIRTUAL<void(__thiscall*)(PVOID, float, float, float, float)>(this, 44)(this, a, r, g, b);
		m_dwRndFlags |= ESilhouettesParams::eAllMap;
	}

	char pad_0x0000[0x24]; //0x0000
	__int32 m_dwRndFlags; //0x0024
};

class IActor
{
public:
	void SetRecoilAnimation(int iStatus)
	{
		VIRTUAL<void(__thiscall*)(PVOID, int)>(this, 91)(this, iStatus);
	}

	int GetTeam() { return *(int*)((uintptr_t)this + 0x3E0); }

	char pad_0x0000[0x10]; //0x0000
	IEntity* m_pEntity; //0x0010 
};

class IActorSystem
{
public:
	IActor* GetActor(int entityId)
	{
		return VIRTUAL<IActor* (__thiscall*)(PVOID, int)>(this, 15)(this, entityId);
	}
};
