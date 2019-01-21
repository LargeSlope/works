#pragma once

//グラフィック読み込み関連
#define GRAPH_DIV_NUM_X	(5)					//X方向に何分割するか
#define GRAPH_DIV_NUM_Y	(5)					//Y方向に何分割するか
#define TILE_KIND_NUM	(GRAPH_DIV_NUM_X)	//タイルが全部で何色あるか
#define TILE_TIME_NUM	(GRAPH_DIV_NUM_Y)	//タイルの消去最大時間
#define GRAPH_SIZE_X	(48)				//X方向のサイズ
#define GRAPH_SIZE_Y	(48)				//Y方向のサイズ

//描画関連
#define ANIM_FRAME		(5)					//グラフ1枚当たりのフレーム数
#define GRAPH_NUM		(GRAPH_DIV_NUM_X * GRAPH_DIV_NUM_Y)		//グラフハンドルの数
#define BOARD_X			(10)				//X方向に並べる数
#define BOARD_Y			(10 + 10)			//Y方向に並べる数

#define BOARD_OFFSET_X ((WINDOW_SIZE_X - (BOARD_X * GRAPH_SIZE_X)) / 2)	//X方向のオフセット
#define BOARD_OFFSET_Y ((WINDOW_SIZE_Y - 3 * (BOARD_Y / 2 * GRAPH_SIZE_Y)) / 2)	//Y方向のオフセット

//サウンド関連
#define SOUND_NUM		(5)					//効果音の総数

//システム関連
#define ADDPOINT		(10)				//タイル1つ当たりの加算ポイント
