#pragma once
#include "ActorClass.h"
#include "Dxlib.h"

#define ZOOM_MAX	(0.7)
#define CAMERA_ADJ	(1000)

class CameraClass : public ActorClass {

public:

	CameraClass(class SceneBase* scene);
	virtual ~CameraClass();

	void UpdateActor() override;
	MATRIX GetView() const { return _View; };
	float GetZomm() const { return zoom; }
	void init();

private:
	float zoom;
	MATRIX _View;
};

