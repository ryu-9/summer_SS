#include "SynopsisComponent.h"
#include "winmain.h"
#include "Main.h"

SynopsisComponent::SynopsisComponent(ActorClass* owner, int updateOrder)
	:Component(owner,updateOrder)
{
	SetFontSize(48);
	float fsize = 48;
	int m = 0;
	std::string t;
	for (auto i = 0; i < 9; i++) {
		switch (i)
		{
		case 0:
			t = "前回の大会から1年が経過した。";
			break;
		case 1:
			t = "そして、今回もこの時期がやってきた。";
			break;
		case 2:
			t = "";
			break;
		case 3:
			t = "数多の歓声と熱狂を、音楽人としての栄光を、掴み取れ。";
			break;
		case 4:
			t = "――その弦で、限界を超え限度を超え、現状を超えろ。";
			break;
		case 5:
			t = "";
			break;
		case 6:
			t = "弦骨の開催をここに宣言する。";
			break;
		case 7:
			t = "";
			break;
		case 8:
			t = "開催者　バイ・O・リン";
			break;
		default:
			break;
		}
		// 中央揃え
		m = (int)(t.length());
		m = 960.0f - (m * 24 / 2.0f);
		_TextData.push_back({ VGet(m,fsize*2 * i ,0),t });
	}
}

void SynopsisComponent::ProcessInput() {
	// 決定キーが押されたらあらすじ終了
	if (gPad._m[0]._trg & PAD_INPUT_1) {
		_Owner->SetState(_Owner->eDead);
		_Owner->GetScene()->SetSceneFlag(1);
	}
}

void SynopsisComponent::Update()
{
	for (auto i = 0; i < _TextData.size();i++) {
		_TextData[i].pos.y -= 2.8f;
	}
	// 表示し終わったらあらすじ終了
	if(_TextData.back().pos.y <= -1080 - 72){
		_Owner->SetState(_Owner->eDead);
		_Owner->GetScene()->SetSceneFlag(1);
	}
}
