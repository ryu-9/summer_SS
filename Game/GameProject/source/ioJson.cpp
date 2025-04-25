#include <string>
#include <fstream>
#include <unordered_map>
#include "nlohmann/json.hpp"
#include "ioJson.h"
#include "ioJsonText.h"
#include "HitBox.h"

namespace iojson {
	// セーブデータロード関数
	bool InputSaveDataJson(const std::string path, class sdata::SaveDataClass* sd) {
		std::ifstream file(path + "savedata.json");
		nlohmann::json json;
		file >> json;
		
		auto keys = json.at("key");
		auto i = 0;
		for (auto& ky : keys) {
			sd->_KeyData.emplace_back();
			sd->_KeyData[i].resize(ky.size());

			ky.at("at1").get_to(sd->_KeyData[i][0]);
			ky.at("at2").get_to(sd->_KeyData[i][1]);
			ky.at("grab").get_to(sd->_KeyData[i][2]);
			ky.at("step").get_to(sd->_KeyData[i][3]);
			ky.at("jump").get_to(sd->_KeyData[i][4]);
			ky.at("crouch").get_to(sd->_KeyData[i][5]);
			i++;
		}
		return true; 
	}

	// セーブデータのセーブ関数
	bool OutputSaveDataJson(const std::string path,class sdata::SaveDataClass* sd) { 
		std::ifstream file(path + "savedata.json");
		nlohmann::json json;
		file >> json;

		auto key = json.at("key");

		for (auto i = 0; i < 2; i++) {
			json["key"][i]["at1"] = sd->_KeyData[i][0];
			json["key"][i]["at2"] = sd->_KeyData[i][1];
			json["key"][i]["grab"] = sd->_KeyData[i][2];
			json["key"][i]["step"] = sd->_KeyData[i][3];
			json["key"][i]["jump"] = sd->_KeyData[i][4];
			json["key"][i]["crouch"] = sd->_KeyData[i][5];
		
		}
		std::ofstream outputfile(path + "savedata.json");
		outputfile << std::setw(4) << json ;
		outputfile.close();

		return true; 
	}

	// 譜面ロード関数
	bool InputScoreJson(const std::string path, int& bpm, std::vector<int>& score)
	{
		std::ifstream file(path + "_score.json");
		nlohmann::json json;
		file >> json;

		json.at("bpm").get_to(bpm);
		if (json.find("score") != json.end()) {
			auto scores = json.at("score");
			for (auto& sc : scores) {
				// 元データに追加
				score.emplace_back(sc);
			}
		}
			return true;
	}

	bool InputMotionAttri(std::map<int, uint_fast8_t>& data)
	{
		std::ifstream file("res/mot.json");
		nlohmann::json json;
		file >> json;
			

		auto mots = json.at("mot");
		for (auto i = 0; i < mots.size(); i++) {
			// 元データに追加
			data[i] = mots[i];
		}
		
		return true;
	}

	// モーションフレームデータをロード
	bool InputMotionFrameJson(const std::string path, std::vector<std::vector<MOTION_FRAME>>& data){

		// ファイルロード
		std::ifstream file(path + "framedata.json");
		nlohmann::json json;
		file >> json;
		file.close();
		int mtnum = 0;
		int framenum = 0;
		auto motions = json.at("motion");
		// モーション数分ループ
		for (auto& mot : motions) {
			data.emplace_back();
			auto frames = mot.at("frame");
			auto revf = mtnum % 2;
			// フレーム数分ループ
			if (revf == 0) {
				for (auto& frm : frames) {
					MOTION_FRAME mf;

					frm.at("type").get_to(mf.type);
					frm.at("mx").get_to(mf.mx);
					frm.at("my").get_to(mf.my);
					frm.at("w").get_to(mf.w);
					frm.at("h").get_to(mf.h);
					frm.at("cg").get_to(mf.cg);
					mf.rev = revf;
					if (frm.find("attackbox") != frm.end()) {
						auto atboxs = frm.at("attackbox");
						for (auto& box : atboxs) {		// ATACKBOXのロード
							ATACK_BOX atb;
							box.at("atx").get_to(atb.pos.x);
							box.at("aty").get_to(atb.pos.y);
							atb.pos.z = 0;
							box.at("atw").get_to(atb.r.x);
							box.at("ath").get_to(atb.r.y);
							box.at("isrect").get_to(atb.r.z);
							box.at("rotate").get_to(atb.rotate);
							box.at("damage1").get_to(atb.damage1);
							box.at("damage2").get_to(atb.damage2);
							box.at("shockx").get_to(atb.shock.x);
							box.at("shocky").get_to(atb.shock.y);
							atb.shock.z = 0;
							mf.at.emplace_back(atb);
						}
					}

					if (frm.find("hitbox") != frm.end()) {				// ヒットボックスのロード
						auto hitboxs = frm.at("hitbox");
						for (auto& box : hitboxs) {
							HIT_BOX hitb;
							box.at("hitx").get_to(hitb.pos.x);
							box.at("hity").get_to(hitb.pos.y);
							hitb.pos.z = 0;
							box.at("hitw").get_to(hitb.r.x);
							box.at("hith").get_to(hitb.r.y);
							box.at("isrect").get_to(hitb.r.z);
							box.at("rotate").get_to(hitb.rotate);
							mf.hit.emplace_back(hitb);
						}
					}
					HIT_BOX* TmpHit = new HIT_BOX[mf.hit.size()];
					ATACK_BOX* TmpAt = new ATACK_BOX[mf.at.size()];
					ConvertBox(TmpHit, mf, TmpAt, mf);
					for (auto i = 0; i < mf.hit.size(); i++) {
						mf.hit[i] = TmpHit[i];
					}
					for (auto i = 0; i < mf.at.size(); i++) {
						mf.at[i] = TmpAt[i];
					}
					delete[] TmpHit;
					delete[] TmpAt;
					// 元データに追加
					data[mtnum].emplace_back(mf);
					framenum++;
				}

				if (mot.find("filename") != mot.end()) {
					std::string fname;
					int fcgnum = 0;
					mot.at("filename").get_to(fname);
					mot.at("cgnum").get_to(fcgnum);
					fname = path + fname;
					
					int* tmp = new int[fcgnum];
					int* mask = new int[fcgnum];
					std::string tmpname = fname + ".png";
					LoadDivGraph(tmpname.c_str(), fcgnum, fcgnum, 1, 1000, 1000, tmp, 0);
					tmpname = fname + "_MASK" + ".png";
					LoadDivGraph(tmpname.c_str(), fcgnum, fcgnum, 1, 1000, 1000, mask, 0);
					bool* flag = new bool[fcgnum];
					for (int i = 0; i < fcgnum; i++) {
						flag[i] = FALSE;
					}
					for (int i = 0; i < framenum; i++) {
						if (data[mtnum][i].cg < fcgnum) {
							flag[data[mtnum][i].cg] = TRUE;
							data[mtnum][i].mask = mask[data[mtnum][i].cg];
							data[mtnum][i].cg = tmp[data[mtnum][i].cg];
						}
						else {
							flag[fcgnum - 1] = TRUE;
							data[mtnum][i].cg = tmp[fcgnum - 1];
							data[mtnum][i].mask = mask[fcgnum - 1];
						}
					}
					for (int i = 0; i < fcgnum; i++) {
						if (flag[i] == FALSE) {
							DeleteGraph(tmp[i]);
							DeleteGraph(mask[i]);
						}
					}

					delete[] tmp;
					delete[] mask;
					delete[] flag;
				}
			}
			else {
				for (auto i = 0; i < data[mtnum-1].size(); i++) {
					data[mtnum].emplace_back(data[mtnum - 1][i]);
					data[mtnum][i].mx *= -1;
					data[mtnum][i].rev = revf;
					for (auto j = 0; j < data[mtnum][i].at.size(); j++) {
						data[mtnum][i].at[j].pos.x *= -1;
						data[mtnum][i].at[j].rotate *= -1;
						}
					for (auto j = 0; j < data[mtnum][i].hit.size(); j++) {
						data[mtnum][i].hit[j].pos.x *= -1;
						data[mtnum][i].hit[j].rotate *= -1;
					}
				}
				
			}
			mtnum++;
			framenum = 0;
		}
		return true;
	}
}