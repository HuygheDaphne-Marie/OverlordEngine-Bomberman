#pragma once
#include "D:\Documents\School\DAE\Semester 4.5\Graphics Programming 2\OverlordEngine_x64\OverlordEngine\Components\BaseComponent.h"
class DoThingOnSceneDetach : public BaseComponent
{
public:
	DoThingOnSceneDetach();
	~DoThingOnSceneDetach() override = default;

	DoThingOnSceneDetach(const DoThingOnSceneDetach & other) = delete;
	DoThingOnSceneDetach(DoThingOnSceneDetach && other) noexcept = delete;
	DoThingOnSceneDetach& operator=(const DoThingOnSceneDetach & other) = delete;
	DoThingOnSceneDetach& operator=(DoThingOnSceneDetach && other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void OnSceneDetach(GameScene* /*pScene*/) override;
};

