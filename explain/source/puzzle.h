#pragma once
#include "common.h"
#include "puzzle_setting.h"

//���[���T�u�N���X
class RuleSub {

public:
	//�^�C�������p�^�[��
	std::vector<point1<int>> point;
};

//���[���N���X
class Rule {

public:
	std::vector<RuleSub> vanish;

	point1<int> size(int rule_num);
};

//�^�C���N���X
class Tile {

public:
	//�R���X�g���N�^
	Tile(int value = 0, int type = 0, int offset = 0, int time1 = 0, int time2 = 0);

	//�R�s�[�R���X�g���N�^
	Tile(const Tile&);

	//�^�C���̐F
	int value = 0;

	//�^�C���̃^�C�v(0:�ʏ� 1:����� 2:�c���)
	int type = 0;

	//�\���ʒu�̂���(������)
	int offset = 0;

	//����(0:���������@1:��������)
	int time[2] = { 0, 0 };

	//�����\����
	bool vanish = false;
};

//�{�[�h�X�[�p�[�N���X
class _Board {

	//�^�C���{��
	Tile tile[BOARD_Y][BOARD_X];

	//���ꊇ����(direction 0:�c 1:��)
	void vanish_line(point1<int> point, int direction);

protected:

	//�N�C�b�N�}�b�`3�t���O(���������g�p)
	bool quick = true;

	//�N�C�b�N�}�b�`3�����t���O
	bool qend = false;

	//�X�R�A
	int score = 0;

	//��������
	int time = 0;

	//������
	void init();

	//�}�b�`�A���S���Y��(�������������s)
	void match(point1<int>offset, RuleSub rule);

	//�^�C������
	void exchange(point2<int> index_point);

	//�㕔���ߒ���
	void fill();

	//�^�C���̕\��
	void drawTiles(point1<int> select_point);

	//�I�t�Z�b�g�̐ݒ�
	void setOffset(point1<int> index, int ofs);

	//����
	void vanishTiles();

	//����
	void fallTiles();

	//�`�F�b�N
	int check_vanishing();

	//���Z�b�g
	void _reset();
};

//���U���g
class Result {

	//�ۑ��p�n�C�X�R�A
	int file_hiscore[10] = { 0 };

	//�C���f�b�N�X
	int index = 0;

	//�C���f�b�N�X
	int select = 0;

	//�n�C�X�R�A��ۑ�����
	void save_hiscore();

	//�V�t�g
	void shift(int index);

public:
	//�X�R�A�����X�g�ɉ�����
	void push(const int hiscore[10], int score);

	//���͎�t
	int input_update();

	//�X�R�A��\������
	void draw_results();
};

//�{�[�h�N���X
class Board :_Board{

	//���[���f�[�^
	Rule rule;

	//�}�E�X�ɂ������C���f�b�N�X
	point2<int> ex_index;

	//��̈�}�b�`���O
	void lmatch(int r_num);

	//��̈�}�b�`���O
	void Match3();

	//�������ԍX�V����
	int update_time();

	//�n�C�X�R�A�̃��[�h
	void load_hiscore();

	//�f�^�b�`�X�C�b�`
	bool detach = false;

	//�n�C�X�R�A
	int hiscore[10] = {0};

	//�^�C���A�b�v�̃^�C�~���O����
	int freeze = 0;

	//���U���g���
	Result result;

public:
	//��ԑJ�ڕϐ�(0:�ێ� 1:�Q�[���Ֆ� 2:���j���[���)
	int state = 0;

	//���Z�b�g
	void reset();

	//�R���X�g���N�^
	Board();

	//���͕ϊ��l�X�V
	void update_input();

	//��{�X�V����
	void update_board();

	//�\������
	void draw_board();
};
