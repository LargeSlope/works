#include "gui.h"
#include "resource.h"
#include "common.h"

//���j���[�`��͈�
#define MENU_0 point2<int>(333, 450, 483, 480)
#define MENU_1 point2<int>(333, 480, 483, 510)
#define MENU_2 point2<int>(333, 510, 483, 540)
#define MNAREA point2<int>(333, 450, 483, 540)

//��{�X�V����( 0:�p���@1:�X�V )
int title_menu::update() {

	//����t���O
	int decide = 0;

	//�����������Ƃ��C���j���[��i�߂�
	if ( Input::key.value[KEY_INPUT_DOWN] == 1 ) {

		select_num++;
	}

	//����������Ƃ��C���j���[����ނ�����
	if ( Input::key.value[KEY_INPUT_UP] == 1 ) {

		select_num--;
	}

	//ENTER���������Ƃ��C���j���[�����肷��
	if ( Input::key.value[KEY_INPUT_RETURN] == 1 ) {

		decide = 1;
	}

	//3������
	select_num %= 3;

	//�}�C�i�X�C���f�b�N�X
	if ( select_num < 0 ) {

		select_num = 3 + select_num;
	}

	//�߂�l
	if ( decide == 1 ) {

		return 1;
	}

	//�}�E�X����
	if ( isin(Input::mouse.point, MENU_0) ) {

		select_num = 0;
	}
	if ( isin(Input::mouse.point, MENU_1) ) {

		select_num = 1;
	}
	if ( isin(Input::mouse.point, MENU_2) ) {

		select_num = 2;
	}

	//���N���b�N���C��ԕێ�
	if ( Input::mouse.push[0] != 1 ) return 0;

	//�g���N���b�N�Ȃ�΁C�X�V
	else if( isin( Input::mouse.point, MNAREA ) ) return 1;

	//�g�O�N���b�N���C��ԕێ�
	else return 0;
}

//�`�揈��
int title_menu::draw() {

	//�w�i�摜
	DrawGraph(0, 0, Resource::StartMenu, TRUE);

	//�Z���N�g�J�[�\��
	DrawBox(MENU_0.s.x, MENU_0.s.y + select_num * 30, MENU_0.e.x, MENU_0.e.y + select_num * 30, gray17, TRUE);

	//���j���[
	DrawFormatString(MENU_0.s.x + 10, MENU_0.s.y + 7, gray7, "START");
	DrawFormatString(MENU_1.s.x + 10, MENU_1.s.y + 7, gray7, "EXPLAIN");
	DrawFormatString(MENU_2.s.x + 10, MENU_2.s.y + 7, gray7, "EXIT");

	return 0;
}