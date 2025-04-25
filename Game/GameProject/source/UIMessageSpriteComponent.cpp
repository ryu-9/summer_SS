#include "UIMessageSpriteComponent.h"

UIMessageSpriteComponent::UIMessageSpriteComponent(UIChipClass* owner, int drawOrder)
	:SpriteComponent(owner,drawOrder)
	,_UIchip(owner)
{
	ChangeFont("DFHSMinchoS JP13N W3");
	SetFontSize(64);
	_Owner->SetPosition(VGet(960, 540, 0));
	_Text = "‰sˆÓì¬’†!";
	_cgHandle.emplace_back(LoadGraph("res/UI/menu/talk_R.png"));
	_cgHandle.emplace_back(LoadGraph("res/UI/menu/ok.png"));

}

void UIMessageSpriteComponent::Draw() {
	auto tmp = _UIchip->GetScale();
	auto tmpos = _Owner->GetPosition();
	auto tmpwh = VGet(499 * _UIchip->GetScale().x, 277 * _UIchip->GetScale().y, 0);
	DrawExtendGraph(tmpos.x - tmpwh.x, tmpos.y - tmpwh.y, tmpos.x + tmpwh.x, tmpos.y + tmpwh.y, _cgHandle[0], true);
	if (_UIchip->GetScale().x == 1.0f&& _UIchip->GetScale().y == 1.0f) {
		DrawFormatString(_Owner->GetPosition().x - 199, _Owner->GetPosition().y - 100, GetColor(255, 255, 255), "%s", _Text.c_str());
	}
//	DrawGraph(_Owner->GetPosition().x + (250 * tmp), _Owner->GetPosition().y + (130 * tmp), _cgHandle[1], true);
	tmpwh = VGet(141 * _UIchip->GetScale().x, 71 * _UIchip->GetScale().y, 0);
	tmpos =VAdd(tmpos, VGet(370, 210, 0));
	DrawExtendGraph(tmpos.x - tmpwh.x, tmpos.y - tmpwh.y, tmpos.x + tmpwh.x, tmpos.y + tmpwh.y, _cgHandle[1], true);
}
