#pragma once

#include <list>
#include <map>
#include "../ModeServer/ActorClass.h"



class ModelServer
{

	struct Model
	{
		std::vector<int> handle;
		std::string filepass;
	};

public:
	ModelServer();
	virtual	~ModelServer();
	static ModelServer* _lpInstance;
	static ModelServer* GetInstance() { return (ModelServer*)_lpInstance; }

	int Add(const TCHAR *filename);		// �o�^
	
	int AddGraph(const TCHAR* filename);		// �o�^

	int AddEffect(const char* filename, float size = 1.0f);		// �o�^
	void DelEffectList(int handle);		// �폜
	bool AddEffectList(int handle, SpriteComponent* sp);		// �ǉ�
	void UpdateEffect();		// �X�V

	int Del(ModeBase* mode);		// �폜�\��


private:
	//std::map<std::string, std::list<int>> _Models;
	std::list<Model> _Models;			// ���f�����X�g
	std::list<Model> _Graph;			// �O���t�B�b�N���X�g
	std::list<Model> _Effect;			// �G�t�F�N�g���X�g
	std::map<int, SpriteComponent*> _EffectHandle;		// �G�t�F�N�g�n���h�����X�g
	int _UpdatedEffectNum;
};

