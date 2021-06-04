#pragma once

bool isEnemy(IActor* m_pActor, IActor* pActor)
{
	return ((m_pActor->GetTeam() != pActor->GetTeam() || pActor->GetTeam() == 0) && (pActor != m_pActor));
}

void disableRecoil(IActor* m_pActor)
{
	m_pActor->SetRecoilAnimation(0);
}

void disableFlashbang(I3DEngine* m_p3DEngine)
{
	m_p3DEngine->SetPostEffectParam("Flashbang_Time", 0.f);
	m_p3DEngine->SetPostEffectParam("FlashBang_BlindAmount", 0.f);
	m_p3DEngine->SetPostEffectParam("Flashbang_DifractionAmount", 0.f);
	m_p3DEngine->SetPostEffectParam("Flashbang_Active", 0.f);
	m_p3DEngine->SetPostEffectParam("FilterRadialBlurring_Radius", 0.f);
	m_p3DEngine->SetPostEffectParam("FilterRadialBlurring_Amount", 0.f);
}

void disableAnimationDelay(ICVar* gCVar)
{
	gCVar->Set(3376, 0.f);
	gCVar->Set(3384, 0.f);
	gCVar->Set(132, 0.f);
}

void startModule()
{
	SSystemGlobalEnvironment* gEnv = SSystemGlobalEnvironment::Singleton();
	IActor* m_pActor = nullptr;

	IGameFramework* gGame = IGameFramework::Singleton();
	if (!gGame || !gGame->GetClientActor(&m_pActor)) return;

	ICVar* gCVar = ICVar::Singleton();
	if (!gCVar) return;

	I3DEngine* m_p3DEngine = gEnv->GetI3DEngine();
	if (!m_p3DEngine) return;

	disableRecoil(m_pActor);
	disableAnimationDelay(gCVar);
	disableFlashbang(m_p3DEngine);

	IEntityIt* m_pEntityIt = gEnv->GetIEntitySystem()->GetIEntityIterator();
	while (IEntity* m_pEntity = m_pEntityIt->Next())
	{
		IEntityProxy* m_pEntityProxy = m_pEntity->GetIEntityProxy(ENTITY_PROXY_RENDER);
		if (!m_pEntityProxy) return;

		if (IActor* pActor = gGame->GetIActorSystem()->GetActor(m_pEntity->GetId()))
		{
			if (!isEnemy(m_pActor, pActor)) continue;
			m_pEntityProxy->SetHUDSilhouettesParams(255, 255, 0, 0);
		}
	}
}