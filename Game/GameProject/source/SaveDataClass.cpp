#include "SaveDataClass.h"
#include "DxLib.h"
#include "ioJson.h"

sdata::SaveDataClass::SaveDataClass()
	: _Path("res/")
{
	iojson::InputSaveDataJson(_Path,this);
}

sdata::SaveDataClass::~SaveDataClass() {
	iojson::OutputSaveDataJson(_Path,this);
}