#include "resource.h"
#include <string>

using namespace std;

//タイルのグラフィック
int Resource::TileGraph[GRAPH_DIV_NUM_Y][GRAPH_DIV_NUM_X] = {0};

//特殊タイルのグラフィック
int Resource::STile[2] = {0};

//ボード面のグラフィック（0:背景 1:前景）
int Resource::BoardGraph[2] = {0};

//タイル消去時効果音
int Resource::VanishSound = 0;

//タイムアップ画面
int Resource::Timeup = 0;

//メニュー画面
int Resource::StartMenu;

//ルール説明画面
int Resource::Rule;

//リザルト画面
int Resource::Result;

//BGM(直接再生するので必要なし)
//int Resource::BgmSound = 0;

//ロード
void Resource::Load(
	int(*LoadDivGraph)(const TCHAR *, int, int, int, int, int, int *, int),
	int(*LoadGraph)(const TCHAR *, int),
	int(*LoadSoundMem)(const TCHAR *, int, int), 
	const char *folder_name) 
{
	//ファイル名の合成
	string FileName[10] = {""};
	FileName[0] = (string)folder_name + "/Image/tiles.png";
	FileName[1] = (string)folder_name + "/Image/board.png";
	FileName[2] = (string)folder_name + "/Image/board2.png";
	FileName[3] = (string)folder_name + "/Sound/効果音ラボ/decision22.mp3";
	FileName[4] = (string)folder_name + "/Image/menu.png";
	FileName[5] = (string)folder_name + "/Image/rule.png";
	FileName[6] = (string)folder_name + "/Image/result.png";
	FileName[7] = (string)folder_name + "/Image/arrow1.png";
	FileName[8] = (string)folder_name + "/Image/arrow2.png";
	FileName[9] = (string)folder_name + "/Image/timeup.png";

	//タイルの画像
	LoadDivGraph(
		FileName[0].c_str(), 
		GRAPH_NUM, 
		GRAPH_DIV_NUM_X, 
		GRAPH_DIV_NUM_Y, 
		GRAPH_SIZE_X, 
		GRAPH_SIZE_Y, 
		TileGraph[0], 0);

	//特殊タイルの画像
	STile[0] = LoadGraph( FileName[7].c_str(), 0 );
	STile[1] = LoadGraph( FileName[8].c_str(), 0 );

	//ボードの画像
	BoardGraph[0] = LoadGraph(FileName[1].c_str(), 0);
	BoardGraph[1] = LoadGraph(FileName[2].c_str(), 0);

	//タイムアップ画面
	Timeup = LoadGraph(FileName[9].c_str(), 0);

	//メニュー画面
	StartMenu = LoadGraph(FileName[4].c_str(), 0);

	//ルール説明画面
	Rule = LoadGraph(FileName[5].c_str(), 0);

	//リザルト画面
	Result = LoadGraph(FileName[6].c_str(), 0);

	//効果音
	VanishSound = LoadSoundMem(FileName[3].c_str(), 3, -1);
}
