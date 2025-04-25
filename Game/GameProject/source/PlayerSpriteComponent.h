#pragma once
#include "SpriteComponent.h"
#include "PlayerClass.h"
#include "CameraClass.h"

class PlayerSpriteComponent : public SpriteComponent {
public:
	PlayerSpriteComponent(class PlayerClass* owner, int drawOrder = 100);
	~PlayerSpriteComponent();
	void Draw() override;
	void SetImage(const TCHAR* filename) override;

	int GetDrawOrder() const { return _DrawOrder; }

protected:
	class PlayerClass* _Player;
	// D‚«‚É•Ï‚¦‚Ä
	std::vector<int> _cgHandle;

private:
	int _ShadowMask[2];
};