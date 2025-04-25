#pragma once
#include <vector>

bool Compare(int type,float n,float m);

/**
* @brief 重みつき抽選
* @param data それぞれの重み
* @return int 抽選結果
**/
int Weighted_Lottery(std::vector<float>& data);


