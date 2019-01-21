#include "resource.h"
#include <string>

using namespace std;

//�^�C���̃O���t�B�b�N
int Resource::TileGraph[GRAPH_DIV_NUM_Y][GRAPH_DIV_NUM_X] = {0};

//����^�C���̃O���t�B�b�N
int Resource::STile[2] = {0};

//�{�[�h�ʂ̃O���t�B�b�N�i0:�w�i 1:�O�i�j
int Resource::BoardGraph[2] = {0};

//�^�C�����������ʉ�
int Resource::VanishSound = 0;

//�^�C���A�b�v���
int Resource::Timeup = 0;

//���j���[���
int Resource::StartMenu;

//���[���������
int Resource::Rule;

//���U���g���
int Resource::Result;

//BGM(���ڍĐ�����̂ŕK�v�Ȃ�)
//int Resource::BgmSound = 0;

//���[�h
void Resource::Load(
	int(*LoadDivGraph)(const TCHAR *, int, int, int, int, int, int *, int),
	int(*LoadGraph)(const TCHAR *, int),
	int(*LoadSoundMem)(const TCHAR *, int, int), 
	const char *folder_name) 
{
	//�t�@�C�����̍���
	string FileName[10] = {""};
	FileName[0] = (string)folder_name + "/Image/tiles.png";
	FileName[1] = (string)folder_name + "/Image/board.png";
	FileName[2] = (string)folder_name + "/Image/board2.png";
	FileName[3] = (string)folder_name + "/Sound/���ʉ����{/decision22.mp3";
	FileName[4] = (string)folder_name + "/Image/menu.png";
	FileName[5] = (string)folder_name + "/Image/rule.png";
	FileName[6] = (string)folder_name + "/Image/result.png";
	FileName[7] = (string)folder_name + "/Image/arrow1.png";
	FileName[8] = (string)folder_name + "/Image/arrow2.png";
	FileName[9] = (string)folder_name + "/Image/timeup.png";

	//�^�C���̉摜
	LoadDivGraph(
		FileName[0].c_str(), 
		GRAPH_NUM, 
		GRAPH_DIV_NUM_X, 
		GRAPH_DIV_NUM_Y, 
		GRAPH_SIZE_X, 
		GRAPH_SIZE_Y, 
		TileGraph[0], 0);

	//����^�C���̉摜
	STile[0] = LoadGraph( FileName[7].c_str(), 0 );
	STile[1] = LoadGraph( FileName[8].c_str(), 0 );

	//�{�[�h�̉摜
	BoardGraph[0] = LoadGraph(FileName[1].c_str(), 0);
	BoardGraph[1] = LoadGraph(FileName[2].c_str(), 0);

	//�^�C���A�b�v���
	Timeup = LoadGraph(FileName[9].c_str(), 0);

	//���j���[���
	StartMenu = LoadGraph(FileName[4].c_str(), 0);

	//���[���������
	Rule = LoadGraph(FileName[5].c_str(), 0);

	//���U���g���
	Result = LoadGraph(FileName[6].c_str(), 0);

	//���ʉ�
	VanishSound = LoadSoundMem(FileName[3].c_str(), 3, -1);
}
