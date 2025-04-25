#pragma once
#include <vector>
#include "CharaStruct.h"

class CommonDataClass
{
public:
	static CommonDataClass* GetInstance() {
		static CommonDataClass _instance;
		return &_instance;
	}
	

	bool _pSynopsis = false;
	bool _pSelect = false;
	bool _pDialogue = false;
	bool _IsDuoMode = false;
	bool _IsPractice = false;
	std::vector<int> _PlayerSelectChara = {0,1};
	int _WinnerPlayerNum = 0;
	std::vector<std::vector<int>> _SoloOrder;
	// ソロモード用
	int _WinningStreak = 0;
	std::vector<std::vector<MOTION_FRAME>> _CopyData;

};

