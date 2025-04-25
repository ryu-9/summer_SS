#pragma once
#include "Component.h"
#include <string>
#include <vector>
#include "DxLib.h"

class SynopsisComponent : public Component {
public:
	struct TEXTDATA
	{
		VECTOR pos;
		std::string text;
	};
	SynopsisComponent(class ActorClass* owner, int updateOrder = 100);

	void ProcessInput() override;
	void Update() override;

	std::vector<TEXTDATA> GetTextData()const { return _TextData; }
private:
	std::vector<TEXTDATA> _TextData;
	bool _Endflag;
};