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
			t = "�O��̑���1�N���o�߂����B";
			break;
		case 1:
			t = "�����āA��������̎���������Ă����B";
			break;
		case 2:
			t = "";
			break;
		case 3:
			t = "�����̊����ƔM�����A���y�l�Ƃ��Ẳh�����A�͂ݎ��B";
			break;
		case 4:
			t = "�\�\���̌��ŁA���E�𒴂����x�𒴂��A����𒴂���B";
			break;
		case 5:
			t = "";
			break;
		case 6:
			t = "�����̊J�Â������ɐ錾����B";
			break;
		case 7:
			t = "";
			break;
		case 8:
			t = "�J�Îҁ@�o�C�EO�E����";
			break;
		default:
			break;
		}
		// ��������
		m = (int)(t.length());
		m = 960.0f - (m * 24 / 2.0f);
		_TextData.push_back({ VGet(m,fsize*2 * i ,0),t });
	}
}

void SynopsisComponent::ProcessInput() {
	// ����L�[�������ꂽ�炠�炷���I��
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
	// �\�����I������炠�炷���I��
	if(_TextData.back().pos.y <= -1080 - 72){
		_Owner->SetState(_Owner->eDead);
		_Owner->GetScene()->SetSceneFlag(1);
	}
}
