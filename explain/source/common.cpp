#include "common.h"
#include "DxLib.h"

int Winit() {

	SetUseDirectDrawDeviceIndex(1);

	if (SetGraphMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 16) != DX_CHANGESCREEN_OK) return 1;

	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK) return 2;

	if (SetBackgroundColor((WINDOW_COLOR & 0x00FF0000) >> 16, (WINDOW_COLOR & 0x0000FF00) >> 8, (WINDOW_COLOR & 0x000000FF))) return 3;

	if (DxLib_Init()) return 4; //DxLib������

	if (SetDrawScreen(DX_SCREEN_BACK)) return 5; //BackGround�`��

	return 0;
}

int Wupdate(unsigned char update_flag) {

	//(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)

	return (
		(!(update_flag & 0x01) ? (ScreenFlip() == 0) : 1) &&
		(!(update_flag & 0x02) ? (ProcessMessage() == 0) : 1) &&
		(!(update_flag & 0x04) ? (ClearDrawScreen() == 0) : 1)
		);
}

void End() {

	DxLib_End(); // DX���C�u�����I������
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

	//�L�[�{�[�h��Ԏ擾
	GetHitKeyStateAll(key_input);

	//�S�ẴL�[�ɂ���
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
//�}�E�X���͏�Ԏ擾
void Input::getMouseState() {

	//�}�E�X���W�̎擾
	GetMousePoint(&mouse_point.x, &mouse_point.y);

	//���͏�Ԃ̎擾
	mouse_input = GetMouseInput();

	//�}�E�X���͏�� (���N���b�N����)
	if (mouse_input & MOUSE_INPUT_LEFT) {

		//�}�E�X�{�^���������Ԃ̍X�V
		mouse_input_time++;
	}
	else if(mouse_input_time){

		//�}�E�X�{�^���������Ԃ̃��Z�b�g
		mouse_input_time = 0;

		//�}�E�X�{�^���f�^�b�`�t���O��ON�ɂ���
		mouse_detach = 1;
	}
	else {

		//�}�E�X�{�^���f�^�b�`�t���O��OFF�ɂ���
		mouse_detach = 0;
	}
}

//�L�[�{�[�h���͏�Ԏ擾
void Input::getKeyState() {

	//�L�[�{�[�h��Ԏ擾
	GetHitKeyStateAll(key_input);

	//�S�ẴL�[�ɂ���
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
