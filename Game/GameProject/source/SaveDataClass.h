#pragma once
#include <string>
#include <vector>

namespace sdata {

	class SaveDataClass
	{
	public:
		SaveDataClass();
		virtual ~SaveDataClass();

		std::vector<std::vector<int>> _KeyData;

	private:
		std::string _Path;
	};


}