#pragma once
#include "puzzle.h"
#include <string>

//���\�[�X�Ǘ�
class Resource {

public:
	//���[�h
	static void Load(
		int(*LoadDivGraph)(const TCHAR *, int, int, int, int, int, int *, int),
		int(*LoadGraph)(const TCHAR *, int),
		int(*LoadSoundMem)(const TCHAR *, int, int),
		const char *folder_name);

	//�^�C���̃O���t�B�b�N
	static int TileGraph[GRAPH_DIV_NUM_Y][GRAPH_DIV_NUM_X];

	//����^�C���̃O���t�B�b�N(�c���ꊇ�^�C�v)
	static int STile[2];

	//�{�[�h�ʂ̃O���t�B�b�N�i0:�w�i 1:�O�i�j
	static int BoardGraph[2];

	//�^�C�����������ʉ�
	static int VanishSound;

	//�^�C���A�b�v�\��
	static int Timeup;

	//���j���[���
	static int StartMenu;

	//���[���������
	static int Rule;

	//���U���g���
	static int Result;
};