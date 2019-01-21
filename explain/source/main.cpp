#include "DxLib.h"
#include "common.h"
#include "puzzle.h"
#include "resource.h"
#include "gui.h"
#include "instructions.h"


//���C���֐�
int main() {

	//DxLib������
	Init;

	//�{�[�h�N���X
	Board board;

	//�^�C�g�����j���[
	title_menu tmenu;

	//�Q�[������
	instruction game_rule;

	//�Q�[�����x��
	int level = 0;

	//�O���t�B�b�N�ǂݍ��� ("Resource"�t�H���_���J��)
	Resource::Load( LoadDivGraph, LoadGraph, LoadSoundMem, "Resource" );

	//�t�H���g�T�C�Y
	SetFontSize(16);

	//���C�����[�v
	while ( Loop( ALL ) ) {

		//���͒l�X�V
		Input::update_key();
		Input::update_mouse();

		//���x��1
		if ( level == 0 ) {

			//���j���[�̍X�V
			if ( tmenu.update() ) {

				//���j���[��I��
				switch ( tmenu.select_num ) {

				//���x��2(�Q�[�����)�֑J��
				case 0: level = 2; break;

				//���x��1(����)�֑J��
				case 1: level = 1; break;

				//�Q�[���I��
				case 2: level = 3; break;

				//�f�t�H���g
				default: break;
				}

				//�Q�[���J�n���C�t�H���g�T�C�Y��ύX
				if( level == 2 ) SetFontSize(21);
			}

			//���j���[�̕`��
			tmenu.draw();
		}

		//�Q�[������
		if ( level == 1 ) {

			//�Q�[���������
			if( game_rule.update() == 1 ) level = 0;

			//������ʕ\��
			game_rule.draw();
		}

		//�Q�[�����
		if ( level == 2 ) {

			//���͒l�X�V
			board.update_input();

			//��{�X�V
			board.update_board();

			//�\���X�V
			board.draw_board();

			//��ԑJ��(���j���[���)
			if (board.state == 2) {

				//�{�[�h��Ԃ����Z�b�g
				board.reset();

				//���j���[��ʂɑJ��
				level = 0;
			}
		}

		//�Q�[���I��
		if ( level == 3 ) {

			break;
		}
	}

	End();
	return 0;
}