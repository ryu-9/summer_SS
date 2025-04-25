#pragma once
#include <string>
#include <vector>
#include <map>
#include "CharaStruct.h"
#include "SaveDataClass.h"

namespace iojson {
	bool InputMotionFrameJson(const std::string path, std::vector<std::vector<MOTION_FRAME>>& data);
	bool InputSaveDataJson(const std::string path, class sdata::SaveDataClass* sd);
	bool OutputSaveDataJson(const std::string path, class sdata::SaveDataClass* sd);
	bool InputScoreJson(const std::string path, int& bpm, std::vector <int>& score);
	bool InputMotionAttri(std::map<int, uint_fast8_t>& data);
}