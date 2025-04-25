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
	// ノーツの構造体
	struct NOTE {
		float x;				// 座標
		int notetype;			// ノーツタイプ
		float easingcnt;		// イージング描画用カウント
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
	// BGM関連
	int _MusicHandle;		// BGMハンドル
	int _Bpm;				// BGMのBPM
	float _MeasureTime;		// 一小節にかかる時間(ミリ秒)
	int _OldTime;
	int _MeasureCnt;
	bool _IsPlay;

	// タイミング関連
	void CreateScore();
	void CreateNotes();
	void UpdateNotes();


	std::vector<int> _LoadScore;						// 譜面(変換前、いらないかも)
	std::vector<std::vector<int>> _Score;	// 譜面(変換後)
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

