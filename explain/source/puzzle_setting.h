#pragma once

//�O���t�B�b�N�ǂݍ��݊֘A
#define GRAPH_DIV_NUM_X	(5)					//X�����ɉ��������邩
#define GRAPH_DIV_NUM_Y	(5)					//Y�����ɉ��������邩
#define TILE_KIND_NUM	(GRAPH_DIV_NUM_X)	//�^�C�����S���ŉ��F���邩
#define TILE_TIME_NUM	(GRAPH_DIV_NUM_Y)	//�^�C���̏����ő厞��
#define GRAPH_SIZE_X	(48)				//X�����̃T�C�Y
#define GRAPH_SIZE_Y	(48)				//Y�����̃T�C�Y

//�`��֘A
#define ANIM_FRAME		(5)					//�O���t1��������̃t���[����
#define GRAPH_NUM		(GRAPH_DIV_NUM_X * GRAPH_DIV_NUM_Y)		//�O���t�n���h���̐�
#define BOARD_X			(10)				//X�����ɕ��ׂ鐔
#define BOARD_Y			(10 + 10)			//Y�����ɕ��ׂ鐔

#define BOARD_OFFSET_X ((WINDOW_SIZE_X - (BOARD_X * GRAPH_SIZE_X)) / 2)	//X�����̃I�t�Z�b�g
#define BOARD_OFFSET_Y ((WINDOW_SIZE_Y - 3 * (BOARD_Y / 2 * GRAPH_SIZE_Y)) / 2)	//Y�����̃I�t�Z�b�g

//�T�E���h�֘A
#define SOUND_NUM		(5)					//���ʉ��̑���

//�V�X�e���֘A
#define ADDPOINT		(10)				//�^�C��1������̉��Z�|�C���g
