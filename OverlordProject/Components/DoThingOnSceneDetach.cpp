#include "stdafx.h"
#include "DoThingOnSceneDetach.h"

DoThingOnSceneDetach::DoThingOnSceneDetach()
{
}

void DoThingOnSceneDetach::Initialize(const SceneContext& /*sceneContext*/)
{
}

void DoThingOnSceneDetach::OnSceneDetach(GameScene*)
{
	Logger::LogInfo(L"Ayo I got deleted son");
}
