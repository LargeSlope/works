#include "gui.h"
#include "resource.h"
#include "common.h"

//メニュー描画範囲
#define MENU_0 point2<int>(333, 450, 483, 480)
#define MENU_1 point2<int>(333, 480, 483, 510)
#define MENU_2 point2<int>(333, 510, 483, 540)
#define MNAREA point2<int>(333, 450, 483, 540)

//基本更新処理( 0:継続　1:更新 )
int title_menu::update() {

	//決定フラグ
	int decide = 0;

	//下を押したとき，メニューを進める
	if ( Input::key.value[KEY_INPUT_DOWN] == 1 ) {

		select_num++;
	}

	//上を押したとき，メニューを後退させる
	if ( Input::key.value[KEY_INPUT_UP] == 1 ) {

		select_num--;
	}

	//ENTERを押したとき，メニューを決定する
	if ( Input::key.value[KEY_INPUT_RETURN] == 1 ) {

		decide = 1;
	}

	//3択処理
	select_num %= 3;

	//マイナスインデックス
	if ( select_num < 0 ) {

		select_num = 3 + select_num;
	}

	//戻り値
	if ( decide == 1 ) {

		return 1;
	}

	//マウス処理
	if ( isin(Input::mouse.point, MENU_0) ) {

		select_num = 0;
	}
	if ( isin(Input::mouse.point, MENU_1) ) {

		select_num = 1;
	}
	if ( isin(Input::mouse.point, MENU_2) ) {

		select_num = 2;
	}

	//未クリック時，状態保持
	if ( Input::mouse.push[0] != 1 ) return 0;

	//枠内クリックならば，更新
	else if( isin( Input::mouse.point, MNAREA ) ) return 1;

	//枠外クリック時，状態保持
	else return 0;
}

//描画処理
int title_menu::draw() {

	//背景画像
	DrawGraph(0, 0, Resource::StartMenu, TRUE);

	//セレクトカーソル
	DrawBox(MENU_0.s.x, MENU_0.s.y + select_num * 30, MENU_0.e.x, MENU_0.e.y + select_num * 30, gray17, TRUE);

	//メニュー
	DrawFormatString(MENU_0.s.x + 10, MENU_0.s.y + 7, gray7, "START");
	DrawFormatString(MENU_1.s.x + 10, MENU_1.s.y + 7, gray7, "EXPLAIN");
	DrawFormatString(MENU_2.s.x + 10, MENU_2.s.y + 7, gray7, "EXIT");

	return 0;
}