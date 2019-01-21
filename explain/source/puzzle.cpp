#include "puzzle.h"
#include "resource.h"
#include <string>
#include <fstream>

//タイル
Tile::Tile(int value, int type, int offset, int time1, int time2) {
	//タイルの色
	this->value = value;

	//タイルのタイプ(0:通常 1:横一列 2:縦一列)
	this->type = type;

	//表示位置のずれ(下方向)
	this->offset = offset;

	//時間(0:消去次元　1:落下次元)
	time[0] = time1;
	time[1] = time2;
}

//コピーコンストラクタ
Tile::Tile(const Tile& tile) {
	//タイルの色
	this->value = tile.value;

	//タイルのタイプ(0:通常 1:横一列 2:縦一列)
	this->type = tile.type;

	//表示位置のずれ(下方向)
	this->offset = tile.offset;

	//時間(0:消去次元　1:落下次元)
	time[0] = tile.time[0];
	time[1] = tile.time[1];
}

//ルールデータサイズ
point1<int> Rule::size(int rule_num) {

	int rsize = (int)vanish[rule_num].point.size();
	point1<int> result;

	for (int i = 0; i < rsize; i++) {

		if( result.x < vanish[rule_num].point[i].x )
			result.x = vanish[rule_num].point[i].x;
		if( result.y < vanish[rule_num].point[i].y )
			result.y = vanish[rule_num].point[i].y;
	}
	return result;
}


//初期化
void _Board::init() {

	//特殊タイル
	int type_rand = GetRand(100);

	//タイルの初期化
	for (int i = 0; i < BOARD_X * BOARD_Y; i++) {

		//ランダム値で初期化
		tile[i / BOARD_X][i % BOARD_X] = Tile( GetRand(4) );

		// 1/50の確率で特殊タイル出現
		type_rand = GetRand(100);
		if (type_rand == 50) tile[i / BOARD_X][i % BOARD_X].type = 1;
		else if (type_rand == 51) tile[i / BOARD_X][i % BOARD_X].type = 2;
		else tile[i / BOARD_X][i % BOARD_X].type = 0;
	}
}

//一列一括消去(direction 0:縦 1:横)
void _Board::vanish_line(point1<int> point, int direction) {

	if ( direction == 1 ) {

		//横バージョン
		for (int i = 0; i < BOARD_X; i++) {

			tile[point.y][i].vanish = true;
		}
	}
	else if( direction == 0 ){

		//縦バージョン
		for (int i = BOARD_Y / 2; i < BOARD_Y; i++) {

			tile[i][point.x].vanish = true;
		}
	}
}

//マッチアルゴリズム
void _Board::match(point1<int>offset, RuleSub rule) {
	
	//ルールデータサイズ
	int rule_size = (int)rule.point.size();

	//カウンタ
	int count = 0;

	//小領域マッチング
	for ( int i = 0; i < rule_size - 1; i++ ) {

		//インデックス
		point1<int> 
			px = rule.point[i    ] + offset,
			nx = rule.point[i + 1] + offset;

		//ルール上次のタイルと一致すれば，カウントアップ
		if ( ( tile[px.y][px.x].value == tile[nx.y][nx.x].value ) && ( tile[px.y][px.x].time[0] == 0 ) ) count++;

		//消去中のタイルとはマッチングしない
		if ( tile[px.y][px.x].time[0] || tile[nx.y][nx.x].time[0] ) count = 0;
	}

	//カウンタがルールサイズよりも小さい場合，無視する
	if ( count < rule_size - 1 ) return;

	//クイックマッチ3(消去可能な場合，クイックマッチ3を続行する)
	if ( quick ) qend = false;

	//ルールデータ上，全てのタイルが一致の時，消去フラグをONにする
	for ( int i = 0; i < rule_size; i++ ) {

		//インデックス
		int x = rule.point[i].x + offset.x,
			y = rule.point[i].y + offset.y;

		//消去フラグをONにする
		tile[y][x].vanish = true;

		//特殊タイルの効果
		vanish_line(point1<int>(x, y), tile[y][x].type - 1);
	}

	//スコア計算
	for (int i = BOARD_X * BOARD_Y / 2; i < BOARD_X * BOARD_Y; i++) {

		//インデックス
		int x = i % BOARD_X,
			y = i / BOARD_X;

		//消したばかりのタイルの数をカウントし，*10 point 加算
		if (tile[y][x].vanish && !tile[y][x].time[0]) {

			score += 10;
		}
	}
}

//タイル交換
void _Board::exchange(point2<int> index_point) {

	Tile buff = tile[index_point.s.y][index_point.s.x];
	tile[index_point.s.y][index_point.s.x] = tile[index_point.e.y][index_point.e.x];
	tile[index_point.e.y][index_point.e.x] = buff;
}

//上部埋め直し
void _Board::fill() {

	//インデックス
	int x = 0, y = 0, type_rand = 0;

	//上部について
	for (int i = 0; i < BOARD_X * BOARD_Y / 2; i++) {

		//インデックス更新
		y = i / BOARD_X;
		x = i % BOARD_X;

		//消去済みタイル以外は無視する
		if (!tile[y][x].time[0]) continue;

		//ランダム値で埋める
		tile[y][x].value = GetRand(4);

		// 1/50の確率で特殊タイル出現
		type_rand = GetRand(100);
		if ( type_rand == 50 ) tile[y][x].type = 1;
		else if ( type_rand == 51 ) tile[y][x].type = 2;
		else tile[y][x].type = 0;

		//消去次元のタイマをリセット
		tile[y][x].time[0] = 0;

		//落下次元のタイマをリセット
		tile[y][x].time[1] = 0;

		//オフセットのリセット
		tile[y][x].offset = 0;
	}
}

//タイルの表示(select_point:ドラッグ中のインデックス)
void _Board::drawTiles(point1<int> select_point) {

	//インデックス
	int x = 0, y = 0;

	//ボード全体について
	for (int i = 0; i < BOARD_X * BOARD_Y; i++) {

		//インデックス更新
		x = i % BOARD_X,
		y = i / BOARD_X;

		//インデックスがドラッグ中のものと一致するとき無視
		if ( ( point1<int>(x, y) == select_point ) && time ) continue;

		//表示
		if( tile[y][x].time[0] < 24 ) DrawGraph(
			BOARD_OFFSET_X + x * GRAPH_SIZE_X, 
			BOARD_OFFSET_Y + y * GRAPH_SIZE_Y + (tile[y][x].offset),
			Resource::TileGraph[tile[y][x].time[0] / 5][tile[y][x].value], TRUE );

		//特殊タイルの表示(消去済みタイルには描画しない)
		if( tile[y][x].type && ( tile[y][x].time[0] < 10 ) ) DrawGraph(
			BOARD_OFFSET_X + x * GRAPH_SIZE_X,
			BOARD_OFFSET_Y + y * GRAPH_SIZE_Y + (tile[y][x].offset),
			Resource::STile[ tile[y][x].type - 1 ], TRUE );
	}

	//前景の描画
	DrawGraph(0, 0, Resource::BoardGraph[1], TRUE);

	//ドラッグ中はマウスポインタの座標にタイルを表示
	if ( isin(select_point, point2<int>(0, BOARD_Y / 2, BOARD_X - 1, BOARD_Y - 1)) &&
		Input::mouse.push && time ) {

		DrawGraph(
			Input::mouse.point.x - (GRAPH_SIZE_X / 2),
			Input::mouse.point.y - (GRAPH_SIZE_Y / 2),
			Resource::TileGraph[tile[select_point.y][select_point.x].time[0]][tile[select_point.y][select_point.x].value], TRUE);

		//特殊タイルの場合
		if ( tile[select_point.y][select_point.x].type ) {

			DrawGraph(
				Input::mouse.point.x - (GRAPH_SIZE_X / 2),
				Input::mouse.point.y - (GRAPH_SIZE_Y / 2),
				Resource::STile[tile[select_point.y][select_point.x].type - 1], TRUE);
		}

	}
}

//オフセットの設定
void _Board::setOffset(point1<int> index, int ofs) {

	tile[index.y][index.x].offset = ofs;
}

//落下
void _Board::fallTiles() {

	//インデックス
	int x, y, count = 0;

	//逆探索
	for (int i = BOARD_X * BOARD_Y - 1; i >= 0; i--) {

		//インデックス（縦探索）
		x = i / BOARD_Y,
		y = i % BOARD_Y;

		//空タイルカウント
		if ( tile[y][x].time[0] >= 24 ) count++;

		//消去中のタイルを発見時，カウンタリセット
		if ( ( 0 < tile[y][x].time[0] ) && ( tile[y][x].time[0] < 24 ) && ( tile[y][x].time[1] < 12 )) count = 0;

		//クイック落下
		if ( quick ) {
			
			//タイルを交換
			if( tile[y][x].time[0] == 0 && count ) tile[y][x].time[1] = count * 12;
		}

		//落下対象ブロックは落下次元をカウントアップする
		if ( tile[y][x].time[0] == 0 && count ) tile[y][x].time[1]++;

		//落下次元をオフセットに変換(線形)
		tile[y][x].offset = tile[y][x].time[1] * (GRAPH_SIZE_Y / 12); //1タイルを12フレームで落下

		//事実上の落下
		if (tile[y][x].time[1] >= count * 12) {

			//落下次元をリセット
			tile[y][x].time[1] = 0;

			//オフセットのリセット
			tile[y][x].offset = 0;

			//タイルを交換
			exchange(point2<int>(x, y, x, y + count));
		}

		//yインデックスが0のとき，カウンタクリア
		if ( y == 0 ) count = 0;
	}
}

//消去
void _Board::vanishTiles() {

	for (int i = BOARD_X * BOARD_Y / 2; i < BOARD_X * BOARD_Y; i++) {

		//インデックス
		int x = i % BOARD_X,
			y = i / BOARD_X;

		//クイック消去
		if ( quick ) {

			if ( tile[y][x].vanish == true ) {

				tile[y][x].time[0] = 24;
				tile[y][x].vanish = false;
			}
			continue;
		}
		

		//消去フラグがONかつ消去次元が24未満の時
		if (tile[y][x].vanish && (tile[y][x].time[0] < 24)) {

			tile[y][x].time[0]++;
		}
		//消去済みの場合
		else if((tile[y][x].vanish) && tile[y][x].time[0] >= 24){

			tile[y][x].vanish = false;
		}
		//消去キャンセル時（高頻度例外）
		else if (!(tile[y][x].vanish) && tile[y][x].time[0]) {

			tile[y][x].vanish = true;
			tile[y][x].time[0]++;
		}
	}
}

//チェック(0:状態維持 1:resultへ移行)
int _Board::check_vanishing() {

	int result = 1;

	for (int i = 0; i < BOARD_X * BOARD_Y; i++) {

		//落下中または消去中のものがある場合，状態維持
		if ( tile[i / BOARD_X][i % BOARD_X].time[0] ) result = 0;
		if ( tile[i / BOARD_X][i % BOARD_X].time[1] ) result = 0;
	}
	return result;
}

//リセット
void _Board::_reset() {

	quick = true;
	qend = false;
	score = 0;
	time = 0;
	init();
}

//リセット
void Board::reset() {

	_reset();
	detach = false;
	freeze = 0;
	state = 0;

	//クイックマッチ3でタイルを準備完了状態にする
	while (!qend) {

		//クイックマッチ3の実行準備
		qend = true;

		//クイックマッチ3を実行 ( 成功したらqend = true )
		update_board();
	}
	//スコアリセット
	score = 0;

	//クイックマッチ3完了
	quick = false;

	//ハイスコアのロード
	load_hiscore();
}

//ハイスコアのロード
void Board::load_hiscore() {

	//ファイルハンドル
	int fhandle = FileRead_open("score.txt");

	//バッファ
	char str[10] = "";

	//例外（ロード失敗）
	if ( !fhandle ) return;

	//読み込み(ファイルの終端，または10行読み込んだら終了)
	for (int i = 0; (i < 10) && !FileRead_eof(fhandle); i++) {

		//1行読み込み(ナル文字は自動で挿入される)
		FileRead_gets(str, 10, fhandle);

		//文字列を数値に変換
		hiscore[i] = atoi( str );
	}

	//ファイルクローズ
	FileRead_close( fhandle );
}

//ボードクラス
Board::Board() {

	//ボードの初期化
	init();

	//ルールデータの初期化
	rule.vanish = std::vector<RuleSub>( 2 ); //消去ルールは2つ存在

	//ルールその1：縦３つ揃った時消去する( X, Y )
	rule.vanish[0].point = { point1<int>( 0, 0 ), point1<int>( 0, 1 ), point1<int>( 0, 2 ) };

	//ルールその2：横３つ揃った時消去する( X, Y )
	rule.vanish[1].point = { point1<int>( 0, 0 ), point1<int>( 1, 0 ), point1<int>( 2, 0 ) };

	//クイックマッチ3でタイルを準備完了状態にする
	while (!qend) {

		//クイックマッチ3の実行準備
		qend = true;

		//クイックマッチ3を実行 ( 成功したらqend = true )
		update_board();
	}
	//スコアリセット
	score = 0;

	//クイックマッチ3完了
	quick = false;

	//ハイスコアのロード
	load_hiscore();
}

//大領域マッチング（オフセットの設定）
void Board::lmatch(int r_num) {

	//ルールデータサイズ
	point1<int> size = rule.size(r_num);

	//i,j : offset
	for (int i = BOARD_Y / 2; i < BOARD_Y - size.y; i++) {

		for (int j = 0; j < BOARD_X - size.x; j++) {

			match(point1<int>(j, i), rule.vanish[r_num]);
		}
	}
}

//大領域マッチング（ルール選択）
void Board::Match3() {

	for (int r_num = 0; r_num < (int)rule.vanish.size(); r_num++) {

		lmatch(r_num);
	}
}

//制限時間更新処理
int Board::update_time() {

	//スタート時に30[s]で初期化
	if ( detach == false ) time = 30 * 60; //60FPS固定の為．

	//0[s]になったときにタイマ停止
	if ( time > 0 ) time--;

	//タイマ完了時，1を返す
	if ( time <= 0 ) {

		//フリーズタイミング120フレーム
		if( ( freeze < 120 ) && ( check_vanishing() ) ) freeze++;

		return 1;
	}

	return 0;
}

//入力変換値更新
void Board::update_input() {

	//タイムアップ時，処理を行わない
	if ( time == 0 ) return;

	//タイル領域に変換
	ex_index.s = (Input::mouse.s_point - point1<int>(BOARD_OFFSET_X, BOARD_OFFSET_Y)) / GRAPH_SIZE_X;
	ex_index.e = (Input::mouse.e_point - point1<int>(BOARD_OFFSET_X, BOARD_OFFSET_Y)) / GRAPH_SIZE_X;

	//マイナスインデックスを実装
	if (Input::mouse.s_point.x < BOARD_OFFSET_X) ex_index.s.x--;
	if (Input::mouse.s_point.y < BOARD_OFFSET_Y) ex_index.s.y--;
	if (Input::mouse.e_point.x < BOARD_OFFSET_X) ex_index.e.x--;
	if (Input::mouse.e_point.y < BOARD_OFFSET_Y) ex_index.e.y--;

	//ドラッグ完了時，交換実施
	else if (Input::mouse.detach[0] &&
		isin(ex_index.s, point2<int>(0, BOARD_Y / 2, BOARD_X - 1, BOARD_Y - 1)) &&
		isin(ex_index.e, point2<int>(0, BOARD_Y / 2, BOARD_X - 1, BOARD_Y - 1)) &&
		(ABS((ex_index.e.x - ex_index.s.x)) == 1 && ABS((ex_index.e.y - ex_index.s.y)) == 0 ||
		 ABS((ex_index.e.x - ex_index.s.x)) == 0 && ABS((ex_index.e.y - ex_index.s.y)) == 1)
		) exchange(ex_index);

	//デタッチ検出
	if (Input::mouse.detach[0]) detach = true;
}

//基本更新処理
void Board::update_board() {

	//リザルト画面入力結果
	int result_select = 0;

	//リザルト画面
	if (freeze == 120) {

		//ハイスコア更新
		result.push(hiscore, score);

		//リザルト画面入力処理
		result_select = result.input_update();

		//CONTINUEならばゲーム再開 EXITならばタイトルに戻る
		state = result_select;

		//CONTINUEならば，リセットしてリスタート
		if(state == 1) reset();

		//EXITならば，文字サイズを元に戻す
		if(state == 2) SetFontSize(16);

		return;
	}

	//タイマ処理
	update_time();

	//マッチング処理
	Match3();

	//消去アニメーション
	vanishTiles();

	//落下処理
	fallTiles();

	//タイル埋め
	fill();
}

//表示処理
void Board::draw_board() {

	//背景の描画
	DrawGraph(0, 0, Resource::BoardGraph[0], TRUE);

	if ( Input::mouse.push[0] && detach ) {

		//タイルのドラッグ中
		drawTiles( ex_index.s );
	}
	else {

		//タイルはドラッグ中でない
		drawTiles( point1<int>(-1, -1) );
	}

	//タイマの表示
	DrawFormatString(730, 230, white, "%d", time / 60);

	//タイマゲージの表示
	DrawBox(670, 190, 670 + (int)(125 * ((double)time / (30 * 60))), 210, white, TRUE);
	DrawBox(670, 190, 795, 210, gray17, FALSE);

	//スコアの表示
	if (score < hiscore[0]) {

		DrawFormatString(26, 138, white, "%d", score);
	}
	else {

		DrawFormatString(26, 138, sky, "%d", score);
	}

	//ハイスコアの表示
	DrawFormatString(26, 263, white, "%d", hiscore[0]);

	//タイムアップ画面
	if ( !time ) DrawGraph(0, 0, Resource::Timeup, TRUE);

	//リザルト画面
	if ( freeze == 120 ) result.draw_results();

	//DrawFormatString(0, 0, black, "%d", quick);
}

//ハイスコアを保存する
void Result::save_hiscore() {

	//ファイルストリーム
	std::ofstream ofs;

	//書き込みモードでオープン
	ofs.open("score.txt", std::ios::out);

	//ハイスコアを書き込む
	for (int i = 0; (i < 10) && (file_hiscore[i] != 0); i++) {

		ofs << file_hiscore[i] << "\n";
	}

	//ファイルをクローズ
	ofs.close();
}

//シフト
void Result::shift(int index) {

	for (int i = 10 - 2; i >= index; i--) {

		file_hiscore[i + 1] = file_hiscore[i];
	}
}

//スコアをリストに加える
void Result::push(const int hiscore[10], int score) {

	//file_hiscore[10]

	//配列コピー
	for (int i = 0; i < 10; i++) {

		file_hiscore[i] = hiscore[i];
	}

	//バブルソート [0]:最高点数 ⇒ [9]:最低点数
	for (int i = 0; i < 10; i++) {

		if (file_hiscore[i] < score) {

			//i以降をシフトして場所を開ける
			shift( i );

			//インデックス
			index = i;

			//空いた場所にスコアを代入
			file_hiscore[i] = score;

			break;
		}
	}

	//スコアが1位か最下位か
	if ( index == 0 && (file_hiscore[9] > score)) {

		//最下位
		index = 11;
	}

	//ハイスコア更新
	save_hiscore();
}

//入力受付(0:維持 1:CONTINUE 2:EXIT)
int Result::input_update() {

	int abs_select = 0;

	//キーボードの下を押したとき
	if (Input::key.value[KEY_INPUT_DOWN] == 1) {

		select++;
	}
	//キーボードの上を押したとき
	if (Input::key.value[KEY_INPUT_UP] == 1) {

		select--;
	}
	//キーボードで決定時
	if (Input::key.value[KEY_INPUT_RETURN] == 1) {

		abs_select = ABS((select % 2));

		return (abs_select + 1);
	}
	//マウスで選択時
	if (isin(Input::mouse.point, point2<int>(355, 495, 460, 525))) {

		select = 0;

		if (Input::mouse.push[0] == 1) {

			return 1;
		}
	}
	if (isin(Input::mouse.point, point2<int>(355, 535, 460, 565))) {

		select = 1;

		if (Input::mouse.push[0] == 1) {

			return 2;
		}
	}

	return 0;
}

//スコアを表示する
void Result::draw_results() {

	//背景
	DrawGraph(0, 0, Resource::Result, TRUE);

	//インデックス
	int abs_select = ABS((select % 2));

	//スコア
	for (int i = 0; i < 10; i++) {

		//ハイスコア
		if ( file_hiscore[i] ) {

			DrawFormatString(360, 275 + 20 * i, white, "%2d %d", i + 1, file_hiscore[i]);
		}
		else {

			DrawFormatString(360, 275 + 20 * i, white, "%2d -", i + 1);
		}

		if ( i == index ) {

			//今回スコアを強調表示
			DrawBox(365, 275 + 20 * i, 455, 295 + 20 * i, white, FALSE);

			//NewRecord
			if( index == 0 ) DrawFormatString( 500, 275, white, "New Record!" );
		}
	}

	//GUI
	DrawBox(355, 495 + abs_select * 40, 460, 525 + abs_select * 40, white, FALSE);
	DrawFormatString(360, 500, white, "CONTINUE");
	DrawFormatString(385, 540, white, "EXIT");
}