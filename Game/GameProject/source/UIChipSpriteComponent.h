#pragma once
#include "SpriteComponent.h"
#include "UIChipClass.h"

class UIChipClass;
class UIChipSpriteComponent : public SpriteComponent
{
public:
	UIChipSpriteComponent(class UIChipClass* owner, int drawOrder = 100);
	void Draw() override;
	void SetImage(const TCHAR* filename) override;
	int GetImageSize() { return _cgHandle.size(); }
	void SetBlendMode(int type) { _BlendMode = type; }
	void SetBlendPalam(int palam) { _BlendPalam = palam; }
protected:
	int _BlendMode;
	int _BlendPalam;
	class UIChipClass* _UIc;

	// ”z—ñ‚É‚·‚é
	int _Width;
	int _Height;
	int _DrawType;

};

