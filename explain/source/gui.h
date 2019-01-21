#pragma once

//タイトルメニュー
class title_menu {

public:
	//メニュー選択画面 (0:スタート画面 1:操作説明 2:終了)
	int select_num = 0;

	//基本更新処理( 0:継続　1:更新 )
	int update();

	//描画処理
	int draw();
};