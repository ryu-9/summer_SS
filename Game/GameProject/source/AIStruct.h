#pragma once
#include <vector>
#include <string>
#include "PlayerClass.h"


struct AIINPUT {
	int delay;
	int duration;
	int act;
};

struct RULE_INPUT {
	int player;
	std::string name;
	int judgetype;
	float criteria;
};

struct RULE_CRITERIA {
	int playerType;
	PlayerClass* player;
	int dataType;
	int judgeType;
	float criteria;
};

struct RULE_DATA {
	RULE_INPUT data;
	int key;
};

struct KEYORDER {
	float priority;
	float actual;
	std::vector<float> criteria;
};

struct RULEDATA {
	RULE_CRITERIA data;
	int key;
};