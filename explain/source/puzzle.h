#pragma once
#include "common.h"
#include "puzzle_setting.h"

//ルールサブクラス
class RuleSub {

public:
	//タイル消去パターン
	std::vector<point1<int>> point;
};

//ルールクラス
class Rule {

public:
	std::vector<RuleSub> vanish;

	point1<int> size(int rule_num);
};

//タイルクラス
class Tile {

public:
	//コンストラクタ
	Tile(int value = 0, int type = 0, int offset = 0, int time1 = 0, int time2 = 0);

	//コピーコンストラクタ
	Tile(const Tile&);

	//タイルの色
	int value = 0;

	//タイルのタイプ(0:通常 1:横一列 2:縦一列)
	int type = 0;

	//表示位置のずれ(下方向)
	int offset = 0;

	//時間(0:消去次元　1:落下次元)
	int time[2] = { 0, 0 };

	//消去予約状態
	bool vanish = false;
};

//ボードスーパークラス
class _Board {

	//タイル本体
	Tile tile[BOARD_Y][BOARD_X];

	//一列一括消去(direction 0:縦 1:横)
	void vanish_line(point1<int> point, int direction);

protected:

	//クイックマッチ3フラグ(初期化時使用)
	bool quick = true;

	//クイックマッチ3完了フラグ
	bool qend = false;

	//スコア
	int score = 0;

	//制限時間
	int time = 0;

	//初期化
	void init();

	//マッチアルゴリズム(消去も同時並行)
	void match(point1<int>offset, RuleSub rule);

	//タイル交換
	void exchange(point2<int> index_point);

	//上部埋め直し
	void fill();

	//タイルの表示
	void drawTiles(point1<int> select_point);

	//オフセットの設定
	void setOffset(point1<int> index, int ofs);

	//消去
	void vanishTiles();

	//落下
	void fallTiles();

	//チェック
	int check_vanishing();

	//リセット
	void _reset();
};

//リザルト
class Result {

	//保存用ハイスコア
	int file_hiscore[10] = { 0 };

	//インデックス
	int index = 0;

	//インデックス
	int select = 0;

	//ハイスコアを保存する
	void save_hiscore();

	//シフト
	void shift(int index);

public:
	//スコアをリストに加える
	void push(const int hiscore[10], int score);

	//入力受付
	int input_update();

	//スコアを表示する
	void draw_results();
};

//ボードクラス
class Board :_Board{

	//ルールデータ
	Rule rule;

	//マウスによる交換インデックス
	point2<int> ex_index;

	//大領域マッチング
	void lmatch(int r_num);

	//大領域マッチング
	void Match3();

	//制限時間更新処理
	int update_time();

	//ハイスコアのロード
	void load_hiscore();

	//デタッチスイッチ
	bool detach = false;

	//ハイスコア
	int hiscore[10] = {0};

	//タイムアップのタイミング処理
	int freeze = 0;

	//リザルト画面
	Result result;

public:
	//状態遷移変数(0:維持 1:ゲーム盤面 2:メニュー画面)
	int state = 0;

	//リセット
	void reset();

	//コンストラクタ
	Board();

	//入力変換値更新
	void update_input();

	//基本更新処理
	void update_board();

	//表示処理
	void draw_board();
};
