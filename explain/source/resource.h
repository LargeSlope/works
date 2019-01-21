#pragma once
#include "puzzle.h"
#include <string>

//リソース管理
class Resource {

public:
	//ロード
	static void Load(
		int(*LoadDivGraph)(const TCHAR *, int, int, int, int, int, int *, int),
		int(*LoadGraph)(const TCHAR *, int),
		int(*LoadSoundMem)(const TCHAR *, int, int),
		const char *folder_name);

	//タイルのグラフィック
	static int TileGraph[GRAPH_DIV_NUM_Y][GRAPH_DIV_NUM_X];

	//特殊タイルのグラフィック(縦横一括タイプ)
	static int STile[2];

	//ボード面のグラフィック（0:背景 1:前景）
	static int BoardGraph[2];

	//タイル消去時効果音
	static int VanishSound;

	//タイムアップ表示
	static int Timeup;

	//メニュー画面
	static int StartMenu;

	//ルール説明画面
	static int Rule;

	//リザルト画面
	static int Result;
};