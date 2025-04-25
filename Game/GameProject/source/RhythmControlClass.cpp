#include "RhythmControlClass.h"
#include "AudienceComponent.h"
#include "ioJson.h"
#include "SceneMain.h"
#include "mymath.h"

RhythmControlClass::RhythmControlClass()
{
}

RhythmControlClass::RhythmControlClass(SceneBase* scene)
	:ActorClass(scene)
	, _Start(0)
	, _End(PSYLLIUM_MAX / 2)
	//,_Easing(0)
	, _Angle(0)
	, _Arm(200)
	, _Height(1500)
	, _Type(0)
	, _Slope(30)
	, _MeasureCnt(0)
	, _OldNotes(nullptr)
	,_BBFlag(FALSE)
	,_IsPlay(false)
	, _Center(850)
{
	_Cg = LoadGraph("res/stage/PSYLLIUM.png");
	_CgF = LoadGraph("res/stage/PSYLLIUM_F.png");
	_CgP = LoadGraph("res/stage/otaku.png");


	sndManager.AddSound(new SoundItemSE("res/sound/se/notes_suc.m4a", "nsuc"));
	sndManager.GetSound("nsuc")->SetVolume(200);
	_Angle = 45;
	_Height = 0;
	_Slope = 0;
	GetColor2(GetScene()->GetPlayer(0)->GetMyColor(), &_Color[0][0], &_Color[0][1], &_Color[0][2]);
	GetColor2(GetScene()->GetPlayer(1)->GetMyColor(), &_Color[1][0], &_Color[1][1], &_Color[1][2]);

	new AudienceComponent(this);
	auto nsc = new NoteSpriteComponent(this);
	nsc->SetImage("test");
	
	
	//Init();

	int drawOrder = 79;
	int j;
		for (int i = 0; i < PSYLLIUM_MAX; i++) {
		j = rand() % PSYLLIUM_MAX;
		for (int ii = j; i < j+PSYLLIUM_MAX;ii++) {
			if (Psyllium[ii % PSYLLIUM_MAX] == nullptr) {
				int x, z;
				x = i * PSYLLIUM_DIST*2 + (rand()%20-10); z = 20 + (rand() % 20 - 10) / 10;
				if(i>=28){
					drawOrder = 78;
					x = (i - 28) * PSYLLIUM_DIST*1; z = 40;
					if (i >= 84) {
						drawOrder = 77;
						x = (i-84) * PSYLLIUM_DIST/2; z = 80;
					}
				}
				Psyllium[ii%PSYLLIUM_MAX] = new PsylliumSpriteComponent(_Cg, _CgF, _CgP,&_StageColor, x,z,this,&_Easing.point,&_Angle,&_Arm, &_Height, &_Slope, drawOrder);
				if(ii<_End){ Psyllium[ii % PSYLLIUM_MAX]->SetColor(_Color[0][0], _Color[0][1], _Color[0][2]); }
				else { Psyllium[ii % PSYLLIUM_MAX]->SetColor(_Color[1][0], _Color[1][1], _Color[1][2]);
				}
				break;
			}
		}
	}
		_OldNotes = nullptr;

}

RhythmControlClass::~RhythmControlClass()
{
	auto size = _Notes.size();
	for (int i = 0; i < size; i++) {
		std::deque<NOTE> tmp;
		std::swap(tmp, _Notes.back());
	_Notes.pop_back();
	}
	_Notes.resize(2);
	size = _Score.size();
	for (int i = 0; i < size; i++) {
		std::vector<int> tmp;
		std::swap(tmp, _Score.back());
		_Score.pop_back();
	}
	size = _LoadScore.size();
	for (int i = 0; i < size; i++) {
		std::vector<int> tmp;
		std::swap(tmp, _LoadScore);
	}
	size = _DonePlayNum.size();
	for (int i = 0; i < size; i++) {
		std::vector<int> tmp;
		std::swap(tmp, _DonePlayNum);
	}
	DeleteSoundMem(_MusicHandle);
	DeleteGraph(_Cg);
	DeleteGraph(_CgF);
	DeleteGraph(_CgP);
}

void RhythmControlClass::ActorInput()
{
	if (CheckSoundMem(_MusicHandle) == TRUE) {
	CreateNotes();
	UpdateNotes();

	}
}

void RhythmControlClass::UpdateActor()
{
	


	//ここにイージングの更新とサイリウムの色変更を記述

	int tmp = _End - _Start;
	float tmpTension = (float)GetScene()->GetTension() / 100.0f * PSYLLIUM_MAX;
	if (_Start > _End) { tmp =100* PSYLLIUM_MAX- (_Start - _End); }
	if (tmpTension > tmp) { 
		_End += tmpTension - tmp;
		while (_End > PSYLLIUM_MAX) { _End -= PSYLLIUM_MAX; }
	}
	if (tmpTension < tmp) { 
		_Start += tmp - tmpTension;
		while (_Start > PSYLLIUM_MAX) { _Start -= PSYLLIUM_MAX; }
	}
	for (int i = 0; i < PSYLLIUM_MAX;i++) {
		Psyllium[i]->SetColor(_Color[0][0], _Color[0][1], _Color[0][2]);
		if(_Start<_End){
			if(_Start<=i&&i<_End){ Psyllium[i]->SetColor(_Color[1][0], _Color[1][1], _Color[1][2]);}
		}
		if (_Start > _End) {
			if(_Start <= i || i < _End){ Psyllium[i]->SetColor(_Color[1][0], _Color[1][1], _Color[1][2]);}
		}
		if (_Start == _End) {
			if(GetScene()->GetTension()==100){
				Psyllium[i]->SetColor(_Color[1][0], _Color[1][1], _Color[1][2]);
			}
			else {
				Psyllium[i]->SetColor(_Color[0][0], _Color[0][1], _Color[0][2]);
			}
		}

	}

	int height = 0;
	int angle = 45;
	int arm = 250;

	switch (_Type) {
	case 1:
		arm = 0;
		break;

	case 2:
		angle = 0;
		arm = 0;


	}

	if (CheckSoundMem(_MusicHandle) == TRUE) {
		_Easing.now = GetSoundCurrentTime(_MusicHandle);
				}
				else {
		_Easing.now = GetNowCount();
				}

	if (_Easing.end <= _Easing.now) {
		_Easing.start = _Easing.end;
		int i = 0;
		bool tmpFlag;
		while (_Easing.start + 10 >= _Easing.end) {

			if (i >= _Notes[0].size()) {
				_Easing.end = _Easing.start + _MeasureTime + 1;
				while (_Easing.now >= _Easing.end) {
					_Easing.end += _MeasureTime;
				}
				_Easing.start = _Easing.end - _MeasureTime - 1;
				_Easing.off = _Easing.end;
				_OldNotes = nullptr;
				// ノーツがないとき
				break;
			}

			else if (_OldNotes == nullptr && _MeasureTime - _Notes[0][i].easingcnt < _MeasureTime / 8) {
				_OldNotes = &_Notes[0][0].easingcnt;
				}
			if (_OldNotes == &_Notes[0][i].easingcnt) {
				i++;
				continue;
				}
			_Easing.end = _Easing.start + (_MeasureTime - _Notes[0][i].easingcnt) + 1;	//切り捨て対策
			_Easing.off = _Easing.end;
			_OldNotes = &_Notes[0][i].easingcnt;
			i++;
			}


		int tmptime = _Easing.end - _Easing.start;
				if (_BBFlag == TRUE) {
					_Easing.start -= tmptime;
					_BBFlag = FALSE;
				}
		else {
			_Easing.off += tmptime;
			_BBFlag = TRUE;
			}
		if (_BBFlag == TRUE && _Easing.end == _Easing.off) {
			int test = 0;
		}
		if (_BBFlag == FALSE && _Easing.end != _Easing.off) {
			int test = 0;
		}

		if (_Easing.end - _Easing.start < 0.05) {
			int test = 0;
	}

	}

		

	_Easing.point = 2 * (float)(_Easing.now - _Easing.start) / (_Easing.off - _Easing.start) - 0.1;

	auto s = GetScene();
	auto main = dynamic_cast<SceneMain*>(s);
	if (_IsPlay == TRUE && CheckSoundMem(_MusicHandle)==FALSE) {
		main->SetBCnt(-100);
	}
	_StageColor = main->GetMyColor();

	//会場の色味を設定
	int tension = GetScene()->GetTension();
	int color[6];
	GetColor2(GetScene()->GetPlayer(1)->GetMyColor(), &color[0], &color[1], &color[2]);
	GetColor2(GetScene()->GetPlayer(0)->GetMyColor(), &color[3], &color[4], &color[5]);
	for (int i = 0; i < 6; i++) {
		if (i < 3) { color[i] *= tension; }
		else { color[i] *= 100 - tension; }
	}
	main->SetMyColor(GetColor((color[0] + color[3]) / 200 + 128, (color[1] + color[4]) / 200 + 128, (color[2] + color[5]) / 200 + 128));
	

}

void RhythmControlClass::Init() {
	DeleteSoundMem(_MusicHandle);
	auto size = _Notes.size();
	for (int i = 0; i < size; i++) {
		std::deque<NOTE> tmp;
		std::swap(tmp, _Notes.back());
		_Notes.pop_back();
	}
	_Notes.resize(2);
	size = _Score.size();
	for (int i = 0; i < size; i++) {
		std::vector<int> tmp;
		std::swap(tmp, _Score.back());
		_Score.pop_back();
	}
	size = _LoadScore.size();
	for (int i = 0; i < size; i++) {
		std::vector<int> tmp;
		std::swap(tmp, _LoadScore);
	}
	_MeasureCnt = 0;
	_IsPlay = false;

	std::string path;
	if (GetScene()->GetCommonData()->_IsPractice) {
		auto tmp = GetScene()->GetCommonData()->_PlayerSelectChara[0];
		path = "res/sound/BGM/0" + std::to_string(tmp);
		_MusicHandle = LoadSoundMem((path + ".m4a").c_str());
	}
	else {
		switch (_DonePlayNum.size()) {
			{
		case 0:
			_DonePlayNum.emplace_back(rand() % 2);
			auto tmp = GetScene()->GetCommonData()->_PlayerSelectChara[_DonePlayNum[0]];
			path = "res/sound/BGM/0" + std::to_string(tmp);
			_MusicHandle = LoadSoundMem((path + ".m4a").c_str());
			break;
			}
			{
		case 1:
			auto n = 1 - _DonePlayNum[0];
			auto tmp = GetScene()->GetCommonData()->_PlayerSelectChara[n];
			path = "res/sound/BGM/0" + std::to_string(tmp);
			_DonePlayNum.emplace_back(n);
			_MusicHandle = LoadSoundMem((path + ".m4a").c_str());
			break;
			}
			{
		case 2:
			// 三曲目
			path = "res/sound/BGM/05";
			_MusicHandle = LoadSoundMem((path + ".m4a").c_str());
			break;
			}
		}
	}

	
	_OldNotes = nullptr;
	iojson::InputScoreJson(path, _Bpm, _LoadScore);
	SyncSystem.SetBasisBGMHandle(_MusicHandle, _Bpm);
	_MeasureTime = 1000.0f * (60.f / (_Bpm / 4.0f));
	CreateScore();

	_BBFlag = TRUE;
	_Easing.end = GetNowCount() + 2500;
	_Easing.off = _Easing.end + _MeasureTime -500;
	_Easing.start = _Easing.end - _MeasureTime;

}

void RhythmControlClass::Play() {

	if (CheckSoundMem(_MusicHandle) == FALSE) {
		ChangeNextPlayVolumeSoundMem(150, _MusicHandle);
		PlaySoundMem(_MusicHandle, DX_PLAYTYPE_BACK);

		_IsPlay = TRUE;
		CreateNotes();
		_Easing.end = GetSoundCurrentTime(_MusicHandle);
		_Easing.start = -_MeasureTime;
		_Easing.off = _MeasureTime;
		_OldTime = 0;

	}
	SyncSystem.SetLoopSE(true,"guide");
	FrameNum = GetScene()->GetFPSCon()->GetNowTime() / GetScene()->GetFPSCon()->GetDeltaTime();
}

void RhythmControlClass::SucFrontNote(int type, bool flag)
{
	
	if (_Notes[type].size() != 0) {
//		_Notes[type].pop_front();
		if (_Notes[type].front().notetype > -1 && flag == TRUE) {
			_Notes[type].front().notetype = -2;
		}
		auto main = dynamic_cast<SceneMain*>(GetScene());
		main->GetEffectCon()->AddScreenEffect(VGet(5 + 1920 / 2 + 102, 1011, 0), 55 + type);
		GetScene()->GetPlayer(type)->SetNotesType(-2);
		sndManager.GetSound("nsuc")->Play();
	}
}

void RhythmControlClass::CreateScore() {
	for (auto j = 0; j < _LoadScore.size(); j++) {
		_Score.emplace_back();
		for (auto i = 7; i > -1; i--) {
			_Score[j].emplace_back((_LoadScore[j] >> i) & 1);		//二進数のデータを分割して入れる
		}


		if ((_LoadScore[j] & 0b01010101) >= 1) {
			auto tmp = 0;
			for (auto i = 0; i < 8; i++) {
				if (tmp == 1 && i % 2 == 1) {
					_Score[j][i] = 2;
				}
				tmp = _Score[j][i];
			}
		}
	}
}

void RhythmControlClass::CreateNotes() {
	int nowtime = GetSoundCurrentTime(_MusicHandle);
	if (_MeasureCnt < _Score.size()) {

		// 現在のBGM再生時間が、生成された小節の再生時間を越えたら一小節分ノーツを生成
		if (_MeasureTime * _MeasureCnt <= nowtime) {
			float ntime = _MeasureTime / _Score[_MeasureCnt].size();
			float diff = (nowtime) - (_MeasureTime * _MeasureCnt);
			for (auto i = 0; i < _Score[_MeasureCnt].size(); i++) {
				if (_Score[_MeasureCnt][i] != 0) {
					NOTE note = { 0, _Score[_MeasureCnt][i] - 1 , (-(i * ntime) + diff) };
					_Notes[0].emplace_back(note);
					_Notes[1].emplace_back(note);
				}
			}
			_MeasureCnt++;
		}
	}
}

void RhythmControlClass::UpdateNotes() {

	int FPSNow = GetScene()->GetFPSCon()->GetNowTime();
	float frametime = GetScene()->GetFPSCon()->GetDeltaTime();

	if (GetScene()->GetFPSCon()->GetUpdateFlag() == TRUE|| GetScene()->GetFPSCon()->GetInputUDFlag() == TRUE) {
		FrameNum++;
	}

	int nowtime = GetSoundCurrentTime(_MusicHandle);
	int deltatime = nowtime - _OldTime;
	for (auto i = 0; i < _Notes.size(); i++) {

		int FPSNow = GetScene()->GetFPSCon()->GetNowTime();
		float frametime = GetScene()->GetFPSCon()->GetDeltaTime();
		int j = 0;
		int num = 0;
		while (GetScene()->GetPlayer(i)->GetFrame(num).type >= 10000) {
			num++;
			if (num + GetScene()->GetPlayer(i)->GetFrameCnt() >= GetScene()->GetPlayer(i)->GetMotionDataSize()) {
				break;
			}
			if (GetScene()->GetPlayer(i)->GetFrame(num).type >= 30000) {
				j++;
			}

		} 
		num--;


		float tmpTime = (FrameNum -1) * frametime;
		if (FPSNow < tmpTime ||FPSNow-tmpTime>frametime) {
			FrameNum = FPSNow / frametime;
			tmpTime = (FrameNum - 1) * frametime;
		}
		if (GetScene()->GetSceneFlag() == 3) {
			tmpTime = (FrameNum/10 - 1) * frametime;
			FPSNow /= 10;
		}

		j += GetScene()->GetPlayer(i)->GetStunTime();
		Inoperable[i][0] = EasingLinear(_MeasureTime + (FPSNow - tmpTime - j * frametime - GetScene()->GetFPSCon()->GetSession() * frametime), 0, _Center, _MeasureTime);
		Inoperable[i][1] = EasingLinear(_MeasureTime + (FPSNow - tmpTime - (j - 6) * frametime - GetScene()->GetFPSCon()->GetSession() * frametime), 0, _Center, _MeasureTime);
		Inoperable[i][2] = EasingLinear(_MeasureTime + (FPSNow - tmpTime - num * frametime - GetScene()->GetFPSCon()->GetSession() * frametime), 0, _Center, _MeasureTime);

		if (1920 / 2 < Inoperable[i][1]) { Inoperable[i][1] = 1920 / 2; }

		for (auto j = 0; j < _Notes[i].size(); j++) {

			// イージング描画
			_Notes[i][j].easingcnt += deltatime;
			_Notes[i][j].x = EasingLinear(_Notes[i][j].easingcnt, 0, _Center, _MeasureTime);
			auto fr = GetScene()->GetFPSCon()->GetFrameNum();
			if (_Notes[i][j].easingcnt >= _MeasureTime + fr * 30.0f) {
				_Notes[i].pop_front();
			}
		}
	}
	_OldTime = nowtime;

	if (CheckSoundMem(_MusicHandle) == TRUE) {
		for (auto i = 0; i < 2; i++) {
			if (_Notes[i].size() != 0) {
				auto fr = GetScene()->GetFPSCon()->GetFrameNum();
				GetScene()->GetPlayer(i)->SetNotesType(-1);

				if (fabs(_Notes[i].front().easingcnt - _MeasureTime) <= fr * 20.0f) {

					GetScene()->GetPlayer(i)->SetNotesType(_Notes[i].front().notetype);
					auto key = GetScene()->GetMain()->GetSaveData()->_KeyData;

				}
			}
		}


	}




}





