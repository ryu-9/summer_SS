#include "BuildScene.h"
#include <fstream>
#include "nlohmann/json.hpp"
#include "ioJsonText.h"
#include "UIChipClass.h"

namespace iojson {
	void BuildScene(std::string name, SceneBase* sc, std::vector<UIChipClass*>& uis, std::vector<UIChipClass*>& buttons) {
		auto path = ("res/UI/" + name + "/");
		std::ifstream file(path + "ui.json");
		nlohmann::json json;
		file >> json;

		auto bts = json.at("Buttons");
		for (auto btn : bts) {
			auto p = btn.at("pos");
			auto pos = VGet(p[0], p[1], p[2]);
			auto s = btn.at("scale");
			auto scale = VGet(s[0], s[1], s[2]);
			auto al = btn.at("alignment");
			auto dror = btn.at("draworder");
			std::string fname;
			btn.at("filename").get_to(fname);
			int type = 0;
			btn.at("type").get_to(type);
			switch (type)
			{
			case 00:
				uis.emplace_back(new UIChipClass(sc, pos, scale, al, (path + fname), dror));
				break;
			case 01:
				uis.back()->AddImage((fname));
				break;
			case 10:
				buttons.emplace_back(new UIChipClass(sc, pos, scale, al, (path + fname), dror));
				break;
			case 11:
				buttons.back()->AddImage((fname));
				break;
			default:
				break;
			}
			
		}
	}
}