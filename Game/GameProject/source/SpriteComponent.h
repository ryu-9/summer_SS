#pragma once
#include <tchar.h>
#include <vector>
#include "Component.h"
#include "Dxlib.h"
#include "CameraClass.h"
#include "LightingComponent.h"

//extern int noimage;

void MyDrawMain(VECTOR pos, VECTOR size, int cg, MATRIX cam, bool rev = FALSE, bool flag = TRUE);
void DrawLighting(class PlayerClass* player, class LightingComponent* Light, int mask1, int mask2, int mask3, int mask4);

class SpriteComponent : public Component {
public:
	SpriteComponent(class ActorClass* owner, int drawOrder = 100, int alpha = 255);
	virtual ~SpriteComponent();

	virtual void Draw();
	virtual void SetImage(const TCHAR* filename);

	int GetDrawOrder() const { return _DrawOrder; }
	int* GetImage() { return _cgHandle.data(); }



protected:
	int _DrawOrder;
	// çDÇ´Ç…ïœÇ¶Çƒ
	std::vector<int> _cgHandle;
};