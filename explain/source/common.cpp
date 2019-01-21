#include "common.h"
#include "DxLib.h"

int Winit() {

	SetUseDirectDrawDeviceIndex(1);

	if (SetGraphMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 16) != DX_CHANGESCREEN_OK) return 1;

	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK) return 2;

	if (SetBackgroundColor((WINDOW_COLOR & 0x00FF0000) >> 16, (WINDOW_COLOR & 0x0000FF00) >> 8, (WINDOW_COLOR & 0x000000FF))) return 3;

	if (DxLib_Init()) return 4; //DxLib初期化

	if (SetDrawScreen(DX_SCREEN_BACK)) return 5; //BackGround描画

	return 0;
}

int Wupdate(unsigned char update_flag) {

	//(裏画面を表画面に反映, メッセージ処理, 画面クリア)

	return (
		(!(update_flag & 0x01) ? (ScreenFlip() == 0) : 1) &&
		(!(update_flag & 0x02) ? (ProcessMessage() == 0) : 1) &&
		(!(update_flag & 0x04) ? (ClearDrawScreen() == 0) : 1)
		);
}

void End() {

	DxLib_End(); // DXライブラリ終了処理
}

Mouse Input::mouse;
Key Input::key;

void Input::_update_mouse(
	int(*GetMousePoint)(int *, int *),
	int(*GetMouseInput)(),
	int(*GetMouseWheelRotVol)(int)) 
{
	GetMousePoint(&mouse.point.x, &mouse.point.y);
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {

		mouse.push[0]++;
	}
	else {
	
		if (mouse.push[0]) {
		
			mouse.detach[0] = true;
			mouse.e_point = mouse.point;
		}
		else mouse.detach[0] = false;
		mouse.push[0] = 0;
	}

	if (GetMouseInput() & MOUSE_INPUT_RIGHT) {

		mouse.push[1]++;
	}
	else {

		if (mouse.push[1]) {
		
			mouse.detach[1] = true;
			mouse.e_point = mouse.point;
		}
		else mouse.detach[1] = false;
		mouse.push[1] = 0;
	}

	if ((mouse.push[0] == 1) || (mouse.push[1] == 1)) {

		mouse.s_point = mouse.point;
	}

	mouse.wheel = GetMouseWheelRotVol(1);
}

void Input::_update_key(int(*GetHitKeyStateAll)(char *)) {

	char key_input[256] = {0};

	//キーボード状態取得
	GetHitKeyStateAll(key_input);

	//全てのキーについて
	for (int i = 0; i < 256; i++) {

		if (key_input[i]) {
			key.value[i]++;
		}
		else {
			key.value[i] = 0;
		}
	}
}


/*
//マウス入力状態取得
void Input::getMouseState() {

	//マウス座標の取得
	GetMousePoint(&mouse_point.x, &mouse_point.y);

	//入力状態の取得
	mouse_input = GetMouseInput();

	//マウス入力状態 (左クリック限定)
	if (mouse_input & MOUSE_INPUT_LEFT) {

		//マウスボタン押下時間の更新
		mouse_input_time++;
	}
	else if(mouse_input_time){

		//マウスボタン押下時間のリセット
		mouse_input_time = 0;

		//マウスボタンデタッチフラグをONにする
		mouse_detach = 1;
	}
	else {

		//マウスボタンデタッチフラグをOFFにする
		mouse_detach = 0;
	}
}

//キーボード入力状態取得
void Input::getKeyState() {

	//キーボード状態取得
	GetHitKeyStateAll(key_input);

	//全てのキーについて
	for (int i = 0; i < 256; i++) {

		if (key_input[i]) {
			key[i]++;
		}
		else {
			key[i] = 0;
		}
	}
}
*/
