#include "AudienceComponent.h"
#include "RhythmControlClass.h"
#include "CameraClass.h"
#include "mymath.h"
#include "Main.h"

AudienceComponent::AudienceComponent(ActorClass* owner, int updateOrder)
	:Component(owner,updateOrder)
	, _Angle(0)
	, _DistMax(600)
{
	_RhythmCon = dynamic_cast<RhythmControlClass*>(owner);
	_ListenerPos = VGet(0, 0, 0);
	SetCreate3DSoundFlag(TRUE);
//	_ClapSEHandle.emplace_back(LoadSoundMem("res/sound/se/clap/clap.ogg",10));
	_ClapSEHandle.emplace_back(LoadSoundMem("res/sound/se/clap/clap2.wav", 10));
	_ClapSEHandle.emplace_back(LoadSoundMem("res/sound/se/clap/clap3.wav", 10));

	for (auto i = 0; i < 12; i++) {
		_ClapSEHandle.emplace_back(DuplicateSoundMem(_ClapSEHandle[i%2]));
	}
	InitSE();

	
	SetCreate3DSoundFlag(FALSE);
}

AudienceComponent::~AudienceComponent() {
	auto s = _ClapSEHandle.size();
	for (auto i = 0; i < s; i++) {
		DeleteSoundMem(_ClapSEHandle[0]);
		_ClapSEHandle.erase(_ClapSEHandle.begin());
		_ClapSEPos.erase(_ClapSEPos.begin());
	}
}

void AudienceComponent::ProcessInput() {
	
}

void AudienceComponent::Update() {
	if (CheckSoundMem(_RhythmCon->GetBGMHandle())) {
		auto m = _Owner->GetScene()->GetCamera()->GetMove();
		_Angle = _Angle + ((m.x / 3000) * PI);
		VECTOR angle = VGet(sin(_Angle), 0.0f, cos(_Angle));
		Set3DSoundListenerPosAndFrontPos_UpVecY(_ListenerPos, VAdd(_ListenerPos, angle));
		auto notes = _RhythmCon->GetNotes();
		if (notes[0].size() > 0) {
			auto tmp = _RhythmCon->GetMeasureTime() - notes[0].front().easingcnt;
			if (tmp < 100) {
				for (auto i = 0; i < _ClapSEHandle.size(); i++) {
					auto tmplag = 0.0f;
					tmplag = VSize(VSub(_ListenerPos, _ClapSEPos[i]));		// ƒJƒƒ‰‚©‚ç‚Ì‹——£Žæ“¾
					tmplag = (tmplag / 30.0f) / 340.0f * 1000;					// ‹——£ƒ‰ƒOŒvŽZ
					SetSoundCurrentTime(500 - tmp - tmplag, _ClapSEHandle[i]);
					PlaySoundMem(_ClapSEHandle[i], DX_PLAYTYPE_BACK, FALSE);
				}
			}
		}
	}
}

void AudienceComponent::InitSE() {
	for (auto i = 0; i < _ClapSEHandle.size(); i++) {
		auto tmpdist = rand() % _DistMax;
		auto tmprad = (rand() % 360) * (PI / 180);
		_ClapSEPos.emplace_back(VGet(sin(tmprad)*tmpdist, 0.0f, cos(tmprad) * tmpdist));
		Set3DPositionSoundMem(_ClapSEPos[i], _ClapSEHandle[i]);
		Set3DRadiusSoundMem(_DistMax, _ClapSEHandle[i]);
		ChangeVolumeSoundMem(150, _ClapSEHandle[i]);
	}
}

