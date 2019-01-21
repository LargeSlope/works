#include "DxLib.h"
#include "common.h"
#include "puzzle.h"
#include "resource.h"
#include "gui.h"
#include "instructions.h"


//メイン関数
int main() {

	//DxLib初期化
	Init;

	//ボードクラス
	Board board;

	//タイトルメニュー
	title_menu tmenu;

	//ゲーム説明
	instruction game_rule;

	//ゲームレベル
	int level = 0;

	//グラフィック読み込み ("Resource"フォルダを開く)
	Resource::Load( LoadDivGraph, LoadGraph, LoadSoundMem, "Resource" );

	//フォントサイズ
	SetFontSize(16);

	//メインループ
	while ( Loop( ALL ) ) {

		//入力値更新
		Input::update_key();
		Input::update_mouse();

		//レベル1
		if ( level == 0 ) {

			//メニューの更新
			if ( tmenu.update() ) {

				//メニューを選択
				switch ( tmenu.select_num ) {

				//レベル2(ゲーム画面)へ遷移
				case 0: level = 2; break;

				//レベル1(説明)へ遷移
				case 1: level = 1; break;

				//ゲーム終了
				case 2: level = 3; break;

				//デフォルト
				default: break;
				}

				//ゲーム開始時，フォントサイズを変更
				if( level == 2 ) SetFontSize(21);
			}

			//メニューの描画
			tmenu.draw();
		}

		//ゲーム説明
		if ( level == 1 ) {

			//ゲーム説明画面
			if( game_rule.update() == 1 ) level = 0;

			//説明画面表示
			game_rule.draw();
		}

		//ゲーム画面
		if ( level == 2 ) {

			//入力値更新
			board.update_input();

			//基本更新
			board.update_board();

			//表示更新
			board.draw_board();

			//状態遷移(メニュー画面)
			if (board.state == 2) {

				//ボード状態をリセット
				board.reset();

				//メニュー画面に遷移
				level = 0;
			}
		}

		//ゲーム終了
		if ( level == 3 ) {

			break;
		}
	}

	End();
	return 0;
}