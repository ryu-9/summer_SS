#include "appframe.h"

class ApplicationGlobal {
public:
	ApplicationGlobal();
	virtual ~ApplicationGlobal();

	bool Init();

public:

	
};

// 他のソースでgGlobalを使えるように
extern ApplicationGlobal		gGlobal;

