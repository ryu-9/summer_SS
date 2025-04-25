#include "AIControlClass.h"
#include "AIProcessComponent.h"
#include "SceneBase.h"
#include "Main.h"


AIControlClass::AIControlClass(SceneBase* scene)
	:ActorClass(scene)
{
//		

}

void AIControlClass::UpdateActor() {
	if (_AIProcessInput != nullptr) {
		_AIProcessInput->GetSituation();
	}

	if (gPad._m[0]._trg & PAD_INPUT_Z) {
		if (_AIProcessInput == nullptr) {
			_AIProcessInput = new AIProcessComponent(this);
			_AIProcessInput->Init();
		}
		else {
			delete _AIProcessInput;
			_AIProcessInput = nullptr;
		}
	}
}

void AIControlClass::Init()
{
	if (_AIProcessInput != nullptr) {
		_AIProcessInput->Init();
	}
	
}

void AIControlClass::SetAI() {
	if (_AIProcessInput == nullptr) {
		_AIProcessInput = new AIProcessComponent(this);
	}

}
