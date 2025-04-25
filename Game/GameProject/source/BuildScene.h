#pragma once
#include "UIChipClass.h"
#include <string>
#include "SceneBase.h"

namespace iojson {
	void BuildScene(std::string name,class SceneBase* sc, std::vector<UIChipClass*>& uis,std::vector<UIChipClass*>& buttons);
}