#include "UICharaSpriteComponent.h"

UICharaSpriteComponent::UICharaSpriteComponent(UICharaClass* owner, int drawOrder)
	:UIChipSpriteComponent(owner,drawOrder)
	,_UIChara(owner)
{
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/00_0.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/01_0.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/02_0.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/03_0.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/04_0.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/05_0.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/00_1.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/01_1.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/02_1.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/03_1.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/04_1.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/05_0.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/00_2.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/01_2.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/02_2.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/03_2.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/04_2.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/chara/05_0.png"));
	if (CheckHandleASyncLoad(_cgHandle[0])) {
		_Width = 2160;
		_Height = 3840;
	}
	else {
		GetGraphSize(_cgHandle[0], &_Width, &_Height);
	}
}

void UICharaSpriteComponent::Draw()
{
	switch (_DrawType)
	{
		{
	case 0:
		auto tmpos = _Owner->GetPosition();
		auto tmpwh = VGet(_Width * _UIc->GetScale().x, _Height * _UIc->GetScale().y, 0);
		DrawExtendGraph(tmpos.x, tmpos.y, tmpos.x + tmpwh.x, tmpos.y + tmpwh.y, _cgHandle[_UIChara->GetCharaType() + _UIChara->GetFaceType() * 6], TRUE);
		break;
		}
		{
	case 1:
		auto tmpos = _Owner->GetPosition();
		auto tmpwh = VGet(_Width * _UIc->GetScale().x, _Height * _UIc->GetScale().y, 0);
		DrawExtendGraph(tmpos.x - tmpwh.x, tmpos.y - tmpwh.y, tmpos.x + tmpwh.x, tmpos.y + tmpwh.y, _cgHandle[_UIChara->GetCharaType() + _UIChara->GetFaceType() * 6], TRUE);
		break;
		}
	case 2:
		break;
	default:
		break;
	}
}
