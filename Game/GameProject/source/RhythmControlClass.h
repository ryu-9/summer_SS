#pragma once
#include "ActorClass.h"
#include "SceneBase.h"
#include "PsylliumSpriteComponent.h"

#define	PSYLLIUM_MAX	(196) //196
#define PSYLLIUM_DIST	(100)
#define CENTER			(960)


class RhythmControlClass : public ActorClass
{
public:
	// �m�[�c�̍\����
	struct NOTE {
		float x;				// ���W
		int notetype;			// �m�[�c�^�C�v
		float easingcnt;		// �C�[�W���O�`��p�J�E���g
	};

	RhythmControlClass();
	RhythmControlClass(SceneBase* scene);
	virtual ~RhythmControlClass();
	void ActorInput() override;
	void UpdateActor() override;
	void Init();
	// Getter
	int GetBGMHandle() const { return _MusicHandle; }
	int GetBpm() const { return _Bpm; }
	float GetMeasureTime() const { return _MeasureTime; }
	std::vector<std::vector<int>> GetScore() const { return _Score; }
	std::vector<std::deque<NOTE>>& GetNotes() { return _Notes; }
	void Play();
	void SucFrontNote(int type, bool flag =TRUE);
	float GetInopTime(int i, int j) { return Inoperable[i][j]; }


protected:
	
private:
	// BGM�֘A
	int _MusicHandle;		// BGM�n���h��
	int _Bpm;				// BGM��BPM
	float _MeasureTime;		// �ꏬ�߂ɂ����鎞��(�~���b)
	int _OldTime;
	int _MeasureCnt;
	bool _IsPlay;

	// �^�C�~���O�֘A
	void CreateScore();
	void CreateNotes();
	void UpdateNotes();


	std::vector<int> _LoadScore;						// ����(�ϊ��O�A����Ȃ�����)
	std::vector<std::vector<int>> _Score;	// ����(�ϊ���)
	std::vector<int> _DonePlayNum;

	int _Start;
	int _End;
	easing _Easing;
	int _Angle;
	int _Arm;
	int _Height;
	std::vector<std::deque<NOTE>> _Notes;
	float Inoperable[2][3];
	class PsylliumSpriteComponent* Psyllium[PSYLLIUM_MAX];
	int _Cg;
	int _CgF;
	int _CgP;
	int _Color[2][3];
	int _Type;
	int _Slope;
	bool _BBFlag;
	int _Center;
	float* _OldNotes;
	int _StageColor;
	int FrameNum;

};

