#include "MotionComponent.h"
#include "PlayerClass.h"
#include "ActorClass.h"
#include "Main.h"
#include "SceneMain.h"
#include "SaveDataClass.h"
#include "SoundManager.h"

MotionComponent::MotionComponent(class PlayerClass* owner,int updateOrder)
	:PlayerComponentBase(owner,updateOrder)
	,_MotionChange(MOT_R_STAND)
	,_Arrow(1)		// ここプレイヤー番号で変える
	,_Gravity(0)
	//,_Stand(1)
{
	_OldMotionChange.resize(6);
	std::fill(_OldMotionChange.begin(), _OldMotionChange.end(), -2);
}

void MotionComponent::ProcessInput() {



	if (_Player->GetMotTrgFlag() == FALSE) {
	_MotionChange = -1;

	auto scene = dynamic_cast<SceneMain*>(_Owner->GetScene());
	if (scene != nullptr) {
		if (scene->GetSceneFlag() > 0) { return; }
	}


	int i = _Player->GetPlayerNo();
	int type = _Player->GetNotesType();
	// 操作なければ立ち
	/*
		if (_Arrow < 0) { _MotionChange = MOT_L_STAND; }
	else { _MotionChange = MOT_R_STAND; }
	
	*/


	// 十字キー操作
	if (gPad._m[i]._key & PAD_INPUT_LEFT) { _MotionChange = MOT_L_RUN; _Arrow = -1; }
	if (gPad._m[i]._key & PAD_INPUT_RIGHT) { _MotionChange = MOT_R_RUN; _Arrow = 1; }

	if (gPad._m[i]._trg & _SaveData()->_KeyData[i][4]) {
		if (_Arrow < 0) { _MotionChange = MOT_L_JUMP_UP; }
		else { _MotionChange = MOT_R_JUMP_UP; }
	}
	if (gPad._m[i]._key & _SaveData()->_KeyData[i][5]) {
		if (_Arrow < 0) { _MotionChange = MOT_L_CROUCH; }
		else { _MotionChange = MOT_R_CROUCH; }
	}

	// ボタン操作
	if (gPad._m[i]._trg & _SaveData()->_KeyData[i][0]) {
		if (_MotionChange == MOT_L_CROUCH || _MotionChange == MOT_R_CROUCH) {
			if (_Arrow < 0) { _MotionChange = MOT_L_ATTACK1_CROUCH; }
			else { _MotionChange = MOT_R_ATTACK1_CROUCH; }
		}
		else {
			if (_Arrow < 0) { _MotionChange = MOT_L_ATTACK1_STAND; }
			else { _MotionChange = MOT_R_ATTACK1_STAND; }
		}

	}
	if (gPad._m[i]._trg & _SaveData()->_KeyData[i][1]) {
		if (type != -1) {
			if (_MotionChange == MOT_L_CROUCH || _MotionChange == MOT_R_CROUCH) {
				if (_Arrow < 0) { _MotionChange = MOT_L_ATTACK2_CROUCH_SUC; }
				else { _MotionChange = MOT_R_ATTACK2_CROUCH_SUC; }
			}
			else {
				if (_Arrow < 0) { _MotionChange = MOT_L_ATTACK2_STAND_SUC; }
				else { _MotionChange = MOT_R_ATTACK2_STAND_SUC; }
			}
		}
		else {
			if (_MotionChange == MOT_L_CROUCH || _MotionChange == MOT_R_CROUCH) {
				if (_Arrow < 0) { _MotionChange = MOT_L_ATTACK2_CROUCH_FAIL; }
				else { _MotionChange = MOT_R_ATTACK2_CROUCH_FAIL; }
			}
			else {
				if (_Arrow < 0) { _MotionChange = MOT_L_ATTACK2_STAND_FAIL; }
				else { _MotionChange = MOT_R_ATTACK2_STAND_FAIL; }
			}
		}

	}
	if (gPad._m[i]._trg & _SaveData()->_KeyData[i][2]) {
		if (_Arrow < 0) { _MotionChange = MOT_L_GRAB_TRY; }
		else { _MotionChange = MOT_R_GRAB_TRY; }
	}
	if (gPad._m[i]._trg & _SaveData()->_KeyData[i][3]) {
		if (type != -1) {
			if (_Arrow < 0) { _MotionChange = MOT_L_STEP_SUC; }
			else { _MotionChange = MOT_R_STEP_SUC; }
		}
		else {
			if (_Arrow < 0) { _MotionChange = MOT_L_STEP_FAIL; }
			else { _MotionChange = MOT_R_STEP_FAIL; }
	}
		
		//PlaySoundMem(sndManager.GetSound(std::to_string(_MotionChange - (_MotionChange % 2)))->GetSoundHandle(),DX_PLAYTYPE_BACK, TRUE);
		}



	// 落下
	if (_Gravity > 0) {
		if (_Arrow < 0) { _MotionChange = MOT_L_JUMP_DOWN; }
		else { _MotionChange = MOT_R_JUMP_DOWN; }
	}

	if (_MotionChange > MOT_L_JUMP_DOWN) { 
		_Player->SetMotTrgFlag(TRUE); 
	}

	}



}

void MotionComponent::Update() {
	bool OldMotTrgFlag = _Player->GetMotTrgFlag();
	if (_Owner->GetScene()->GetFPSCon()->GetUpdateFlag() == TRUE ||
		_Owner->GetScene()->GetFPSCon()->GetInputUDFlag() == TRUE) {
		if (_Player->GetMotTrgFlag() == TRUE) {
			_OldMotionChange.emplace_front(_MotionChange);
			while (_OldMotionChange.size() > 6) {
				_OldMotionChange.pop_back();
			}
		}
		else {
			_OldMotionChange.emplace_front(-2);
			while (_OldMotionChange.size() > 6) {
				_OldMotionChange.pop_back();
			}
			_OldMotionChange[5] = _MotionChange;
		}


		_Player->SetMotTrgFlag(FALSE);
	}

	if (_Owner->GetScene()->GetFPSCon()->GetUpdateFlag() == FALSE) {
		return;
	}

	if (_Player->GetSlowFlag() > 1) {
		return;
	}

	if (_Player->GetComboFlag() == TRUE) {
		int test = 0;
	}

	bool MotionProcessFlag = TRUE;

	if (_Owner->GetScene()->GetFPSCon()->GetUpdateFlag() == TRUE) {
		MotionProcessFlag = _Player->FrameProcess();
	}
	MOTION_FRAME frame = _Player->GetFrame();


	int i = 0;
	for (auto motionChange : _OldMotionChange) {
		i++;
		if (motionChange == -2) {
			continue;
		}


		if (_Player->GetStandFlag() == FALSE) {

			if (_Player->GetMotionID() >= MOT_R_JUMP_DOWN && _Player->GetMotionID() <= MOT_L_JUMP_UP) {		//空中処理
				if (motionChange == MOT_R_RUN ) {
					_Player->SetMove(VGet(80, 0, 0));		//空中の移動速度を設定
					motionChange = MOT_R_JUMP_DOWN;
				}
				if (motionChange == MOT_L_RUN) {
					_Player->SetMove(VGet(-80, 0, 0));		//空中の移動速度を設定
					motionChange = MOT_L_JUMP_DOWN;
				}
			}




			if (motionChange == MOT_L_ATTACK1_STAND || motionChange == MOT_L_ATTACK1_CROUCH) {
				motionChange = MOT_L_ATTACK1_JUMP;
			}
			if (motionChange == MOT_R_ATTACK1_STAND || motionChange == MOT_R_ATTACK1_CROUCH) {
				motionChange = MOT_R_ATTACK1_JUMP;
			}
			if (motionChange == MOT_R_ATTACK2_STAND_SUC) {
				motionChange = MOT_R_ATTACK2_JUMP_SUC;
			}
			if (motionChange == MOT_L_ATTACK2_STAND_SUC) {
				motionChange = MOT_L_ATTACK2_JUMP_SUC;
			}
			if (motionChange == MOT_R_ATTACK2_STAND_FAIL) {
				motionChange = MOT_R_ATTACK2_JUMP_FAIL;
			}
			if (motionChange == MOT_L_ATTACK2_STAND_FAIL) {
				motionChange = MOT_L_ATTACK2_JUMP_FAIL;
			}
		}
		if (MotionProcessFlag == TRUE) {
			if (frame.type >= 30000) {

				continue;
			}
			if (frame.type >= 20000)
			{
				switch (motionChange) {

				case MOT_L_ATTACK1_STAND:
				case MOT_R_ATTACK1_STAND:
					if (_Player->GetComboFlag() == TRUE) {
						if (_Player->GetMotionID() == MOT_L_ATTACK2_STAND_SUC || _Player->GetMotionID() == MOT_R_ATTACK2_STAND_SUC
							|| _Player->GetMotionID() == MOT_L_ATTACK2_COMBO1_SUC || _Player->GetMotionID() == MOT_R_ATTACK2_COMBO1_SUC) {
							motionChange += 8;
						}
					}
					if (motionChange == MOT_L_ATTACK1_STAND || motionChange == MOT_R_ATTACK1_STAND) { motionChange = -2; }
					break;

				case MOT_L_ATTACK2_STAND_SUC:
				case MOT_R_ATTACK2_STAND_SUC:
					//case MOT_L_ATTACK2_STAND_FAIL:
					//case MOT_R_ATTACK2_STAND_FAIL:
					if (_Player->GetComboFlag() == TRUE) {
						if (_Player->GetMotionID() == MOT_L_ATTACK2_STAND_SUC || _Player->GetMotionID() == MOT_R_ATTACK2_STAND_SUC) {
							motionChange += 6;
						}//コンボ二段目に変化
						if (_Player->GetMotionID() == MOT_L_ATTACK2_COMBO1_SUC || _Player->GetMotionID() == MOT_R_ATTACK2_COMBO1_SUC) {
							motionChange += 8;
						}//コンボ三段目に変化
					}
					break;

				case MOT_L_ATTACK2_STAND_FAIL:
				case MOT_R_ATTACK2_STAND_FAIL:
					if (_Player->GetComboFlag() == TRUE) {
						if (_Player->GetMotionID() == MOT_L_ATTACK2_STAND_SUC || _Player->GetMotionID() == MOT_R_ATTACK2_STAND_SUC) {
							motionChange += 8;
						}//コンボ二段目に変化
						if (_Player->GetMotionID() == MOT_L_ATTACK2_COMBO1_SUC || _Player->GetMotionID() == MOT_R_ATTACK2_COMBO1_SUC) {
							motionChange += 10;
						}//コンボ三段目に変化
					}
					break;

				case MOT_L_ATTACK2_CROUCH_SUC:
				case MOT_L_ATTACK2_CROUCH_FAIL:
					if (_Player->GetComboFlag() == TRUE) {
						if (_Player->GetMotionID() == MOT_L_ATTACK2_CROUCH_SUC || _Player->GetMotionID() == MOT_R_ATTACK2_CROUCH_SUC) {
							motionChange = MOT_L_ATTACK2_CROUCH_COMBO_FAIL;
						}//コンボ二段目に変化
					}
					break;
				case MOT_R_ATTACK2_CROUCH_SUC:
				case MOT_R_ATTACK2_CROUCH_FAIL:
					if (_Player->GetComboFlag() == TRUE) {
						if (_Player->GetMotionID() == MOT_L_ATTACK2_CROUCH_SUC || _Player->GetMotionID() == MOT_R_ATTACK2_CROUCH_SUC) {
							motionChange = MOT_R_ATTACK2_CROUCH_COMBO_FAIL;
						}//コンボ二段目に変化
					}
					break;

				case MOT_L_ATTACK2_JUMP_SUC:
				case MOT_R_ATTACK2_JUMP_SUC:
				case MOT_L_ATTACK2_JUMP_FAIL:
				case MOT_R_ATTACK2_JUMP_FAIL:
					break;

				default:
					motionChange = -2;
					break;
				}
			}
			else if (frame.type >= 10000) {
				switch (motionChange) {

				case MOT_L_ATTACK2_STAND_SUC:
				case MOT_R_ATTACK2_STAND_SUC:
					//case MOT_L_ATTACK2_STAND_FAIL:
					//case MOT_R_ATTACK2_STAND_FAIL:
					if (_Player->GetComboFlag() == TRUE) {
						if (_Player->GetMotionID() == MOT_L_ATTACK2_STAND_SUC || _Player->GetMotionID() == MOT_R_ATTACK2_STAND_SUC) {
							motionChange += 6;
						}//コンボ二段目に変化
						if (_Player->GetMotionID() == MOT_L_ATTACK2_COMBO1_SUC || _Player->GetMotionID() == MOT_R_ATTACK2_COMBO1_SUC) {
							motionChange += 8;
						}//コンボ三段目に変化
					}
					break;

				case MOT_L_ATTACK2_STAND_FAIL:
				case MOT_R_ATTACK2_STAND_FAIL:
					if (_Player->GetComboFlag() == TRUE) {
						if (_Player->GetMotionID() == MOT_L_ATTACK2_STAND_SUC || _Player->GetMotionID() == MOT_R_ATTACK2_STAND_SUC) {
							motionChange += 8;
						}//コンボ二段目に変化
						if (_Player->GetMotionID() == MOT_L_ATTACK2_COMBO1_SUC || _Player->GetMotionID() == MOT_R_ATTACK2_COMBO1_SUC) {
							motionChange += 10;
						}//コンボ三段目に変化
					}
					break;

				case MOT_L_ATTACK2_CROUCH_SUC:
				case MOT_L_ATTACK2_CROUCH_FAIL:
					if (_Player->GetComboFlag() == TRUE) {
						if (_Player->GetMotionID() == MOT_L_ATTACK2_CROUCH_SUC || _Player->GetMotionID() == MOT_R_ATTACK2_CROUCH_SUC) {
							motionChange = MOT_L_ATTACK2_CROUCH_COMBO_FAIL;
						}//コンボ二段目に変化
					}
					break;
				case MOT_R_ATTACK2_CROUCH_SUC:
				case MOT_R_ATTACK2_CROUCH_FAIL:
					if (_Player->GetComboFlag() == TRUE) {
						if (_Player->GetMotionID() == MOT_L_ATTACK2_CROUCH_SUC || _Player->GetMotionID() == MOT_R_ATTACK2_CROUCH_SUC) {
							motionChange = MOT_R_ATTACK2_CROUCH_COMBO_FAIL;
						}//コンボ二段目に変化
					}
					break;



				case MOT_R_ATTACK1_CROUCH:
				case MOT_L_ATTACK1_CROUCH:
					if (_Player->GetComboFlag() == TRUE) {
						if (_Player->GetMotionID() == MOT_L_ATTACK1_CROUCH || _Player->GetMotionID() == MOT_R_ATTACK1_CROUCH) { motionChange += 6; }//コンボ二段目に変化
					}
					break;

				case MOT_L_ATTACK1_STAND:
				case MOT_R_ATTACK1_STAND:
					if (_Player->GetComboFlag() == TRUE) {
						if (_Player->GetMotionID() == MOT_L_ATTACK1_STAND || _Player->GetMotionID() == MOT_R_ATTACK1_STAND) { motionChange += 6; }//コンボ二段目に変化
						if (_Player->GetMotionID() == MOT_L_ATTACK1_COMBO1 || _Player->GetMotionID() == MOT_R_ATTACK1_COMBO1) { motionChange += 8; }//コンボ三段目に変化
					}
					break;

				case MOT_R_STEP_SUC:
				case MOT_L_STEP_SUC:
					break;

				case MOT_L_ATTACK2_JUMP_SUC:
				case MOT_R_ATTACK2_JUMP_SUC:
				case MOT_L_ATTACK2_JUMP_FAIL:
				case MOT_R_ATTACK2_JUMP_FAIL:
					break;

				default:
					motionChange = -2;
					break;

				}
			}
		}
		if (MotionProcessFlag == FALSE || (motionChange == -1 &&
			(_Player->GetMotionID() == MOT_R_RUN || _Player->GetMotionID() == MOT_L_RUN
				|| _Player->GetMotionID() == MOT_R_CROUCH || _Player->GetMotionID() == MOT_L_CROUCH))) {		//モーションの終了を検知
			if (_Owner->GetStandFlag() == TRUE) {		//地上での待機モーション
				if (_Arrow < 0) { _Player->SetMotionID(MOT_L_STAND); }
				else { _Player->SetMotionID(MOT_R_STAND); }
			}
			else {										//空中での待機モーション
				if (_Arrow < 0) { _Player->SetMotionID(MOT_L_JUMP_DOWN); }
				else { _Player->SetMotionID(MOT_R_JUMP_DOWN); }
			}
		}


		if (_Player->GetStandFlag() == FALSE && motionChange == MOT_R_JUMP_UP)
		{
			motionChange = MOT_R_JUMP_DOWN;
		}
		else if (_Player->GetStandFlag() == FALSE && motionChange == MOT_L_JUMP_UP)
		{
			motionChange = MOT_L_JUMP_DOWN;
		}

		if (motionChange > 0) {
			if (_Owner->GetScene()->GetFPSCon()->GetUpdateFlag() == TRUE &&
				_Player->GetMotionID()!=motionChange) {
			

				if (i > 1) {
					_Player->SetMotionID(motionChange , FALSE);
				}
				else {
					_Player->SetMotionID(motionChange, TRUE);
				}
			std::fill(_OldMotionChange.begin(), _OldMotionChange.end(), -2);
			break;

		}
	}
	}
	if (OldMotTrgFlag == FALSE) {
		//_OldMotionChange[0] = -2;
	}
	//_OldMotionChange.emplace_back(_OldMotionChange[0]);
	while (_OldMotionChange.size() > 6) {
	_OldMotionChange.pop_back();
	}
	//_OldMotionChange.pop_front();
	MOTION_FRAME tmp = _Player->GetFrame();
	_Player->SetMove(VGet(tmp.mx, tmp.my, 0));
	//_Player->SetMotTrgFlag(FALSE);

		//_Player->MotionUpdate();
}

sdata::SaveDataClass* MotionComponent::_SaveData()
{
	return _Owner->GetScene()->GetMain()->GetSaveData();	// キー取得用
}
