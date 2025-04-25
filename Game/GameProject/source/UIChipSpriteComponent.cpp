#include "UIChipSpriteComponent.h"

UIChipSpriteComponent::UIChipSpriteComponent(UIChipClass* owner, int drawOrder)
	:SpriteComponent(owner,drawOrder)
	,_UIc(owner)
	,_BlendMode(DX_BLENDMODE_NOBLEND)
	,_BlendPalam(255)
{
	_DrawType = _UIc->GetType();
}

void UIChipSpriteComponent::Draw() {
	_DrawType = _UIc->GetType();
	if (_Owner->GetState() == _Owner->ePaused) {
		_UIc->ResetScale();
		
	}

//	SetDrawBlendMode(_BlendMode, _BlendPalam);
	switch (_DrawType)
	{
		{
	case 0:
		auto tmpos = _Owner->GetPosition();
	//	auto tmpwh = VGet(_Width * _UIc->GetScale().x, _Height * _UIc->GetScale().y, 0);
		DrawGraph(tmpos.x, tmpos.y , _cgHandle[_UIc->GetImageNum()], TRUE);
		break;
		}
		{
	case 1:
	auto tmpos = _Owner->GetPosition();
		auto tmpwh = VGet(_Width * _UIc->GetScale().x, _Height * _UIc->GetScale().y, 0);
		DrawExtendGraph(tmpos.x - tmpwh.x, tmpos.y - tmpwh.y, tmpos.x + tmpwh.x, tmpos.y + tmpwh.y, _cgHandle[_UIc->GetImageNum()], TRUE);
		break;
		}
		{
	case 3:
		auto tmpos = _Owner->GetPosition();
		auto tmpwh = VGet(_Width * _UIc->GetScale().x, _Height * _UIc->GetScale().y, 0);
		DrawModiGraph(tmpos.x - tmpwh.x, tmpos.y - _Height - tmpwh.y , tmpos.x + tmpwh.x, tmpos.y - _Height - tmpwh.y, tmpos.x + tmpwh.x, tmpos.y + _Height + tmpwh.y, tmpos.x - tmpwh.x, tmpos.y + _Height - tmpwh.y, _cgHandle[_UIc->GetImageNum()], TRUE);
		break;
		}
	default:
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	
}

void UIChipSpriteComponent::SetImage(const TCHAR* filename)
{
	SpriteComponent::SetImage(filename);
	GetGraphSize(_cgHandle[0], &_Width, &_Height);
	if (_DrawType == 0) {

	}
	else {
	_Width /= 2;
	_Height /= 2;
	}
}