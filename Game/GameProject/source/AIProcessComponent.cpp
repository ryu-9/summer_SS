#include "AIProcessComponent.h"
#include "Main.h"
#include "SceneMain.h"
#include "ActorClass.h"
#include "RhythmControlClass.h"
#include "MyFunc.h"
#include "FPSControlClass.h"
#include "ioJson.h"

AIProcessComponent::AIProcessComponent(class ActorClass* owner, int updateOrder)
	: Component(owner, updateOrder)
	, _CPUPlayer(owner->GetScene()->GetPlayer(1))
	, _Enemy(owner->GetScene()->GetPlayer(0))
	, _State(NOMAL)
	, _Action(-1)
	
{
	_InfS.resize(3);
	_Situation.resize(3);
	_Frame = _Owner->GetScene()->GetFPSCon()->GetFrameNum();
	_Rhythm = dynamic_cast<SceneMain*>(_Owner->GetScene())->GetRhythm();
	iojson::InputMotionAttri(_MotionDatafl);
}

AIProcessComponent::~AIProcessComponent()
{
}


void AIProcessComponent::Init() {
	_Enemy = _Owner->GetScene()->GetPlayer(0);
	_CPUPlayer = _Owner->GetScene()->GetPlayer(1);
	_Rhythm = dynamic_cast<SceneMain*>(_Owner->GetScene())->GetRhythm();
			
	switch (_CPUPlayer->GetType())
	{
	case 0:
		_Weight.push_back({ 55,50,30 });
		_WeightRatio = { 3,7 };
		break;
	case 1:
		_Weight.push_back({ 20,80,20 });
		_WeightRatio = { 7,3 };
		break;
	case 2:
		_Weight.push_back({ 50,50,30 });
		_WeightRatio = { 3,2 };
		break;
	case 3:
		if (_Enemy->GetType() == 0 || _Enemy->GetType() == 2) {
			_Weight.push_back({ 50,30,50 });
			_WeightRatio = { 7,3 };
		}
		else {
			_Weight.push_back({ 40,50,20 });
			_WeightRatio = { 2,3 };
		}
		break;
	case 4:
		_Weight.push_back({ 40,50,15 });
		_WeightRatio = { 3,2 };
		break;
	default:
//		_ActWeight.push_back({ 10,30,50,30 });
		break;
	}
	_Weight.push_back({ 0,0,0 });
	_Situation[0]["位置"] = 0;
	_Situation[0]["テンション"] = 0;
	_Situation[1]["ノーツ"] = 0;
	_Situation[1]["位置"] = 0;
	_Situation[1]["テンション"] = 0;
	_Situation[1]["スーパーアーマー"] = 0;
	_Situation[1]["モーション"] = 0;
	_Situation[2]["距離"] = 0;
}

void AIProcessComponent::ProcessInput() {

	if (_Owner->GetScene()->GetSceneFlag() == 0) {
		Inference();

		/*if (_InputKey.size() == 0) {
			DecAction();
		}
		*/
		DecAction();
		InputKeyData();
		if (_InputKey.size() == 0) {
			ResetAction();
		}
	}
}


void AIProcessComponent::Inference() {
	_InfS[1]["モーション"] = InfMotion();
}

// 情報取得
void AIProcessComponent::GetSituation() {

	_Situation[0]["位置"] = _CPUPlayer->GetPosition().x;
	_Situation[0]["テンション"] = _Owner->GetScene()->GetTension();
	_Situation[1]["位置"] = _Enemy->GetPosition().x;
	_Situation[2]["距離"] = fabs(_Situation[0]["位置"]- _Situation[1]["位置"]);
}

void AIProcessComponent::DecAction() {

	auto createKey = 0;
	auto key = _Owner->GetScene()->GetMain()->GetSaveData()->_KeyData;
	if (_Action < 0) {
		if (_MotionDatafl[_CPUPlayer->GetMotionID()] & (1)) {
			if (_CPUPlayer->GetMotionID() >= MotionComponent::MOT_R_DAMAGE_RISE) {
				if (_Rhythm->GetNotes()[1].size() > 0) {
					auto f = (_Rhythm->GetMeasureTime() - _Rhythm->GetNotes()[1].front().easingcnt) / 16.7f;

					createKey |= key[_CPUPlayer->GetPlayerNo()][3];
					_InputKey.push({ (int)(f + rand() % 3),0, createKey });
					_Action = 0;
				}
			}
				return;
		}
		_Action = Waiting;
		
		if ((_MotionDatafl[_Enemy->GetMotionID()] & (1 << 1))) {
			_Action = Avoid;
		}
		auto tmp = (_Situation[2]["距離"] / 3000.0f) * 100.0f;
		if (((_Situation[2]["距離"] / 3000.0f) * 100.0f) < (rand() % 70)) {
			_Action = Attack;
			
		}
	}
		switch (_Action)
		{
		case NON:
			break;
		case Waiting:
			if (_ActProgress == 0) {
				if (_InfS[0]["ノーツ"] < -1) {
					if (rand() % 100 > 20) {
						if (_Rhythm->GetNotes()[1].size() > 0) {
							auto f = (_Rhythm->GetMeasureTime() - _Rhythm->GetNotes()[1].front().easingcnt) / 16.7f;
							createKey |= key[_CPUPlayer->GetPlayerNo()][3];
							_InputKey.push({ (int)(f + rand() % 3),0, createKey });
						}
					}
					else {
						if (ModiPLArrow()) { createKey |= PAD_INPUT_RIGHT; }
						else { createKey |= PAD_INPUT_LEFT; }
						_InputKey.push({ (int)(_Frame + rand() % 3), (int)(_Frame * 2 + rand() % 20), createKey });
					}
				}
				else {
					if (rand() % 100 > 80) {
						if (_Rhythm->GetNotes()[1].size() > 0) {
							auto f = (_Rhythm->GetMeasureTime() - _Rhythm->GetNotes()[1].front().easingcnt) / 16.7f;
							createKey |= key[_CPUPlayer->GetPlayerNo()][3];
							_InputKey.push({ (int)(f + rand() % 3),0, createKey });
						}
					}
					else {
						if (ModiPLArrow()) { createKey |= PAD_INPUT_RIGHT; }
						else { createKey |= PAD_INPUT_LEFT; }
						_InputKey.push({ (int)(_Frame + rand() % 3), (int)(_Frame * 2 + rand() % 20), createKey });
					}
				}
				_ActProgress++;
			}
			break;
			{
		case Avoid:
			if (_ActProgress == 0) {
				int respF = 0;		// 猶予計算
				for (auto i = 0; i + _Enemy->GetFrameCnt() < _Enemy->GetMotionDataSize(); i++) {
					if (_Enemy->GetFrame(i).at.size() != 0) {
						break;
					}
					else {

					}
					respF++;
				}

				if (respF > 0) {
					auto f = 0.0f;
					if (_Rhythm->GetNotes()[1].size() > 0) {
						f = (_Rhythm->GetMeasureTime() - _Rhythm->GetNotes()[1].front().easingcnt) / 16.7f;
					}
					if (respF * _Owner->GetScene()->GetFPSCon()->GetDeltaTime() > f) {
						if (ModiPLArrow()) { createKey |= PAD_INPUT_LEFT; }
						else { createKey |= PAD_INPUT_RIGHT; }
						createKey |= key[1][3];
						_InputKey.push({ (int)(f + rand() % 3),0, createKey });
					}
					else if ((_MotionDatafl[_Enemy->GetMotionID()] & (1 << 5))) {
						createKey |= PAD_INPUT_UP;
						_InputKey.push({ rand() % 5, 0, createKey });
					}
					_ActProgress++;
				}
				else {

				}
			}
			else {
				if (!(_MotionDatafl[_Enemy->GetMotionID()] & (1 << 1))) {
					ResetAction();
				}
			}
			break;
			
		case Attack:

			// 先に攻撃キーを決定

				std::vector<float> tmpWeight = { 0,0,0 };
				if (_CPUPlayer->GetSACnt() > 0) {
					tmpWeight[1] += 70;
				}
				if (_InfS[0]["ノーツ"] < -1) {
					tmpWeight[1] += 50;
				}
				if (_Situation[2]["距離"] > 700) {
					tmpWeight[0] += 40;
					tmpWeight[2] -= 60;
				}
				if (_Situation[0]["テンション"] >= 95) {
					tmpWeight[2] += 50;
				}
				for (auto i = 0; i < tmpWeight.size(); i++) {
					tmpWeight[i] = (tmpWeight[i] * _WeightRatio[0] + _Weight[0][i] * _WeightRatio[1] + _Weight[1][i]);
				}
				auto w = Weighted_Lottery(tmpWeight);
				_ActType = w;
				_Action = w + 4;
			

			float tmpd = _Situation[2]["距離"] - 600;
			if (ModiPLArrow()) { createKey |= PAD_INPUT_RIGHT; }
			else { createKey |= PAD_INPUT_LEFT; }
			// 距離決定
			auto tmp = ((tmpd / 50) * _Owner->GetScene()->GetFPSCon()->GetFrameNum());
			_InputKey.push({ 0,(int)((tmpd / 50.0f) * _Frame), createKey });
			if (_Rhythm->GetNotes()[1].size() > 0) {
				auto f = (_Rhythm->GetMeasureTime() - _Rhythm->GetNotes()[1].front().easingcnt) / 16.7f;
				createKey |= key[1][_ActType];
				_InputKey.push({ (int)(f + rand() % 3),0, createKey });
			}
			else {
				createKey |= key[1][_ActType];
				_InputKey.push({ (int)(_Frame + rand() % 3),0, createKey });
			}

			break;
			}
			{
		case ATTACK1:
		case ATTACK2:
		case GRAB:
			if (_MotionDatafl[_Enemy->GetMotionID()] & (1)) {
				_Weight[1][_ActType]++;
			}
			if (_MotionDatafl[_CPUPlayer->GetMotionID()] & (1)) {
				_Weight[1][_ActType]--;
			}
			break;
			}
		case RISE:
			break;
		default:
			break;
		}
	

}

// キューから入力
void AIProcessComponent::InputKeyData() {
	gPad._m[_CPUPlayer->GetPlayerNo()]._key = 0;
	gPad._m[_CPUPlayer->GetPlayerNo()]._trg = 0;
	if (_InputKey.size() != 0) {
		while (_InputKey.front().delay <= 0) {
			gPad._m[_CPUPlayer->GetPlayerNo()]._key |= _InputKey.front().act;
			gPad._m[_CPUPlayer->GetPlayerNo()]._trg |= _InputKey.front().act;
			if (_InputKey.front().duration <= 0) {
				_InputKey.pop();
				_ActProgress++;
				if (_InputKey.size() == 0) { break; }
				continue;
			}
			_InputKey.front().duration--;
			break;
		}
		if (_InputKey.size() != 0) {
			_InputKey.front().delay--;
		}
	}
	else {
		gPad._m[_CPUPlayer->GetPlayerNo()]._key = 0;
		gPad._m[_CPUPlayer->GetPlayerNo()]._trg = 0;

	}
}


void AIProcessComponent::ResetInputKey() {
	while (!_InputKey.empty()) { _InputKey.pop(); }		// 入力予定のキーをクリア
}

void AIProcessComponent::ResetAction() {

	_Action = -1;
	_ActType = -1;
	_ActProgress = 0;

}

int AIProcessComponent::InfMotion()
{
	// 相手のモーションに気付けるか
	auto cnt = (_Enemy->GetFrameCnt() / _Enemy->GetMotionDataSize()) * 100;
	
	if (rand() % 100 - 5 < cnt) {
		return _Enemy->GetMotionID();
	}
	return -1;
}

int AIProcessComponent::ModiPLArrow() {
	if (_CPUPlayer->GetPosition().x - _Enemy->GetPosition().x > 0) {
		return 0;
	}
	return 1;
}


