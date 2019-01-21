#include "puzzle.h"
#include "resource.h"
#include <string>
#include <fstream>

//�^�C��
Tile::Tile(int value, int type, int offset, int time1, int time2) {
	//�^�C���̐F
	this->value = value;

	//�^�C���̃^�C�v(0:�ʏ� 1:����� 2:�c���)
	this->type = type;

	//�\���ʒu�̂���(������)
	this->offset = offset;

	//����(0:���������@1:��������)
	time[0] = time1;
	time[1] = time2;
}

//�R�s�[�R���X�g���N�^
Tile::Tile(const Tile& tile) {
	//�^�C���̐F
	this->value = tile.value;

	//�^�C���̃^�C�v(0:�ʏ� 1:����� 2:�c���)
	this->type = tile.type;

	//�\���ʒu�̂���(������)
	this->offset = tile.offset;

	//����(0:���������@1:��������)
	time[0] = tile.time[0];
	time[1] = tile.time[1];
}

//���[���f�[�^�T�C�Y
point1<int> Rule::size(int rule_num) {

	int rsize = (int)vanish[rule_num].point.size();
	point1<int> result;

	for (int i = 0; i < rsize; i++) {

		if( result.x < vanish[rule_num].point[i].x )
			result.x = vanish[rule_num].point[i].x;
		if( result.y < vanish[rule_num].point[i].y )
			result.y = vanish[rule_num].point[i].y;
	}
	return result;
}


//������
void _Board::init() {

	//����^�C��
	int type_rand = GetRand(100);

	//�^�C���̏�����
	for (int i = 0; i < BOARD_X * BOARD_Y; i++) {

		//�����_���l�ŏ�����
		tile[i / BOARD_X][i % BOARD_X] = Tile( GetRand(4) );

		// 1/50�̊m���œ���^�C���o��
		type_rand = GetRand(100);
		if (type_rand == 50) tile[i / BOARD_X][i % BOARD_X].type = 1;
		else if (type_rand == 51) tile[i / BOARD_X][i % BOARD_X].type = 2;
		else tile[i / BOARD_X][i % BOARD_X].type = 0;
	}
}

//���ꊇ����(direction 0:�c 1:��)
void _Board::vanish_line(point1<int> point, int direction) {

	if ( direction == 1 ) {

		//���o�[�W����
		for (int i = 0; i < BOARD_X; i++) {

			tile[point.y][i].vanish = true;
		}
	}
	else if( direction == 0 ){

		//�c�o�[�W����
		for (int i = BOARD_Y / 2; i < BOARD_Y; i++) {

			tile[i][point.x].vanish = true;
		}
	}
}

//�}�b�`�A���S���Y��
void _Board::match(point1<int>offset, RuleSub rule) {
	
	//���[���f�[�^�T�C�Y
	int rule_size = (int)rule.point.size();

	//�J�E���^
	int count = 0;

	//���̈�}�b�`���O
	for ( int i = 0; i < rule_size - 1; i++ ) {

		//�C���f�b�N�X
		point1<int> 
			px = rule.point[i    ] + offset,
			nx = rule.point[i + 1] + offset;

		//���[���㎟�̃^�C���ƈ�v����΁C�J�E���g�A�b�v
		if ( ( tile[px.y][px.x].value == tile[nx.y][nx.x].value ) && ( tile[px.y][px.x].time[0] == 0 ) ) count++;

		//�������̃^�C���Ƃ̓}�b�`���O���Ȃ�
		if ( tile[px.y][px.x].time[0] || tile[nx.y][nx.x].time[0] ) count = 0;
	}

	//�J�E���^�����[���T�C�Y�����������ꍇ�C��������
	if ( count < rule_size - 1 ) return;

	//�N�C�b�N�}�b�`3(�����\�ȏꍇ�C�N�C�b�N�}�b�`3�𑱍s����)
	if ( quick ) qend = false;

	//���[���f�[�^��C�S�Ẵ^�C������v�̎��C�����t���O��ON�ɂ���
	for ( int i = 0; i < rule_size; i++ ) {

		//�C���f�b�N�X
		int x = rule.point[i].x + offset.x,
			y = rule.point[i].y + offset.y;

		//�����t���O��ON�ɂ���
		tile[y][x].vanish = true;

		//����^�C���̌���
		vanish_line(point1<int>(x, y), tile[y][x].type - 1);
	}

	//�X�R�A�v�Z
	for (int i = BOARD_X * BOARD_Y / 2; i < BOARD_X * BOARD_Y; i++) {

		//�C���f�b�N�X
		int x = i % BOARD_X,
			y = i / BOARD_X;

		//�������΂���̃^�C���̐����J�E���g���C*10 point ���Z
		if (tile[y][x].vanish && !tile[y][x].time[0]) {

			score += 10;
		}
	}
}

//�^�C������
void _Board::exchange(point2<int> index_point) {

	Tile buff = tile[index_point.s.y][index_point.s.x];
	tile[index_point.s.y][index_point.s.x] = tile[index_point.e.y][index_point.e.x];
	tile[index_point.e.y][index_point.e.x] = buff;
}

//�㕔���ߒ���
void _Board::fill() {

	//�C���f�b�N�X
	int x = 0, y = 0, type_rand = 0;

	//�㕔�ɂ���
	for (int i = 0; i < BOARD_X * BOARD_Y / 2; i++) {

		//�C���f�b�N�X�X�V
		y = i / BOARD_X;
		x = i % BOARD_X;

		//�����ς݃^�C���ȊO�͖�������
		if (!tile[y][x].time[0]) continue;

		//�����_���l�Ŗ��߂�
		tile[y][x].value = GetRand(4);

		// 1/50�̊m���œ���^�C���o��
		type_rand = GetRand(100);
		if ( type_rand == 50 ) tile[y][x].type = 1;
		else if ( type_rand == 51 ) tile[y][x].type = 2;
		else tile[y][x].type = 0;

		//���������̃^�C�}�����Z�b�g
		tile[y][x].time[0] = 0;

		//���������̃^�C�}�����Z�b�g
		tile[y][x].time[1] = 0;

		//�I�t�Z�b�g�̃��Z�b�g
		tile[y][x].offset = 0;
	}
}

//�^�C���̕\��(select_point:�h���b�O���̃C���f�b�N�X)
void _Board::drawTiles(point1<int> select_point) {

	//�C���f�b�N�X
	int x = 0, y = 0;

	//�{�[�h�S�̂ɂ���
	for (int i = 0; i < BOARD_X * BOARD_Y; i++) {

		//�C���f�b�N�X�X�V
		x = i % BOARD_X,
		y = i / BOARD_X;

		//�C���f�b�N�X���h���b�O���̂��̂ƈ�v����Ƃ�����
		if ( ( point1<int>(x, y) == select_point ) && time ) continue;

		//�\��
		if( tile[y][x].time[0] < 24 ) DrawGraph(
			BOARD_OFFSET_X + x * GRAPH_SIZE_X, 
			BOARD_OFFSET_Y + y * GRAPH_SIZE_Y + (tile[y][x].offset),
			Resource::TileGraph[tile[y][x].time[0] / 5][tile[y][x].value], TRUE );

		//����^�C���̕\��(�����ς݃^�C���ɂ͕`�悵�Ȃ�)
		if( tile[y][x].type && ( tile[y][x].time[0] < 10 ) ) DrawGraph(
			BOARD_OFFSET_X + x * GRAPH_SIZE_X,
			BOARD_OFFSET_Y + y * GRAPH_SIZE_Y + (tile[y][x].offset),
			Resource::STile[ tile[y][x].type - 1 ], TRUE );
	}

	//�O�i�̕`��
	DrawGraph(0, 0, Resource::BoardGraph[1], TRUE);

	//�h���b�O���̓}�E�X�|�C���^�̍��W�Ƀ^�C����\��
	if ( isin(select_point, point2<int>(0, BOARD_Y / 2, BOARD_X - 1, BOARD_Y - 1)) &&
		Input::mouse.push && time ) {

		DrawGraph(
			Input::mouse.point.x - (GRAPH_SIZE_X / 2),
			Input::mouse.point.y - (GRAPH_SIZE_Y / 2),
			Resource::TileGraph[tile[select_point.y][select_point.x].time[0]][tile[select_point.y][select_point.x].value], TRUE);

		//����^�C���̏ꍇ
		if ( tile[select_point.y][select_point.x].type ) {

			DrawGraph(
				Input::mouse.point.x - (GRAPH_SIZE_X / 2),
				Input::mouse.point.y - (GRAPH_SIZE_Y / 2),
				Resource::STile[tile[select_point.y][select_point.x].type - 1], TRUE);
		}

	}
}

//�I�t�Z�b�g�̐ݒ�
void _Board::setOffset(point1<int> index, int ofs) {

	tile[index.y][index.x].offset = ofs;
}

//����
void _Board::fallTiles() {

	//�C���f�b�N�X
	int x, y, count = 0;

	//�t�T��
	for (int i = BOARD_X * BOARD_Y - 1; i >= 0; i--) {

		//�C���f�b�N�X�i�c�T���j
		x = i / BOARD_Y,
		y = i % BOARD_Y;

		//��^�C���J�E���g
		if ( tile[y][x].time[0] >= 24 ) count++;

		//�������̃^�C���𔭌����C�J�E���^���Z�b�g
		if ( ( 0 < tile[y][x].time[0] ) && ( tile[y][x].time[0] < 24 ) && ( tile[y][x].time[1] < 12 )) count = 0;

		//�N�C�b�N����
		if ( quick ) {
			
			//�^�C��������
			if( tile[y][x].time[0] == 0 && count ) tile[y][x].time[1] = count * 12;
		}

		//�����Ώۃu���b�N�͗����������J�E���g�A�b�v����
		if ( tile[y][x].time[0] == 0 && count ) tile[y][x].time[1]++;

		//�����������I�t�Z�b�g�ɕϊ�(���`)
		tile[y][x].offset = tile[y][x].time[1] * (GRAPH_SIZE_Y / 12); //1�^�C����12�t���[���ŗ���

		//������̗���
		if (tile[y][x].time[1] >= count * 12) {

			//�������������Z�b�g
			tile[y][x].time[1] = 0;

			//�I�t�Z�b�g�̃��Z�b�g
			tile[y][x].offset = 0;

			//�^�C��������
			exchange(point2<int>(x, y, x, y + count));
		}

		//y�C���f�b�N�X��0�̂Ƃ��C�J�E���^�N���A
		if ( y == 0 ) count = 0;
	}
}

//����
void _Board::vanishTiles() {

	for (int i = BOARD_X * BOARD_Y / 2; i < BOARD_X * BOARD_Y; i++) {

		//�C���f�b�N�X
		int x = i % BOARD_X,
			y = i / BOARD_X;

		//�N�C�b�N����
		if ( quick ) {

			if ( tile[y][x].vanish == true ) {

				tile[y][x].time[0] = 24;
				tile[y][x].vanish = false;
			}
			continue;
		}
		

		//�����t���O��ON������������24�����̎�
		if (tile[y][x].vanish && (tile[y][x].time[0] < 24)) {

			tile[y][x].time[0]++;
		}
		//�����ς݂̏ꍇ
		else if((tile[y][x].vanish) && tile[y][x].time[0] >= 24){

			tile[y][x].vanish = false;
		}
		//�����L�����Z�����i���p�x��O�j
		else if (!(tile[y][x].vanish) && tile[y][x].time[0]) {

			tile[y][x].vanish = true;
			tile[y][x].time[0]++;
		}
	}
}

//�`�F�b�N(0:��Ԉێ� 1:result�ֈڍs)
int _Board::check_vanishing() {

	int result = 1;

	for (int i = 0; i < BOARD_X * BOARD_Y; i++) {

		//�������܂��͏������̂��̂�����ꍇ�C��Ԉێ�
		if ( tile[i / BOARD_X][i % BOARD_X].time[0] ) result = 0;
		if ( tile[i / BOARD_X][i % BOARD_X].time[1] ) result = 0;
	}
	return result;
}

//���Z�b�g
void _Board::_reset() {

	quick = true;
	qend = false;
	score = 0;
	time = 0;
	init();
}

//���Z�b�g
void Board::reset() {

	_reset();
	detach = false;
	freeze = 0;
	state = 0;

	//�N�C�b�N�}�b�`3�Ń^�C��������������Ԃɂ���
	while (!qend) {

		//�N�C�b�N�}�b�`3�̎��s����
		qend = true;

		//�N�C�b�N�}�b�`3�����s ( ����������qend = true )
		update_board();
	}
	//�X�R�A���Z�b�g
	score = 0;

	//�N�C�b�N�}�b�`3����
	quick = false;

	//�n�C�X�R�A�̃��[�h
	load_hiscore();
}

//�n�C�X�R�A�̃��[�h
void Board::load_hiscore() {

	//�t�@�C���n���h��
	int fhandle = FileRead_open("score.txt");

	//�o�b�t�@
	char str[10] = "";

	//��O�i���[�h���s�j
	if ( !fhandle ) return;

	//�ǂݍ���(�t�@�C���̏I�[�C�܂���10�s�ǂݍ��񂾂�I��)
	for (int i = 0; (i < 10) && !FileRead_eof(fhandle); i++) {

		//1�s�ǂݍ���(�i�������͎����ő}�������)
		FileRead_gets(str, 10, fhandle);

		//������𐔒l�ɕϊ�
		hiscore[i] = atoi( str );
	}

	//�t�@�C���N���[�Y
	FileRead_close( fhandle );
}

//�{�[�h�N���X
Board::Board() {

	//�{�[�h�̏�����
	init();

	//���[���f�[�^�̏�����
	rule.vanish = std::vector<RuleSub>( 2 ); //�������[����2����

	//���[������1�F�c�R����������������( X, Y )
	rule.vanish[0].point = { point1<int>( 0, 0 ), point1<int>( 0, 1 ), point1<int>( 0, 2 ) };

	//���[������2�F���R����������������( X, Y )
	rule.vanish[1].point = { point1<int>( 0, 0 ), point1<int>( 1, 0 ), point1<int>( 2, 0 ) };

	//�N�C�b�N�}�b�`3�Ń^�C��������������Ԃɂ���
	while (!qend) {

		//�N�C�b�N�}�b�`3�̎��s����
		qend = true;

		//�N�C�b�N�}�b�`3�����s ( ����������qend = true )
		update_board();
	}
	//�X�R�A���Z�b�g
	score = 0;

	//�N�C�b�N�}�b�`3����
	quick = false;

	//�n�C�X�R�A�̃��[�h
	load_hiscore();
}

//��̈�}�b�`���O�i�I�t�Z�b�g�̐ݒ�j
void Board::lmatch(int r_num) {

	//���[���f�[�^�T�C�Y
	point1<int> size = rule.size(r_num);

	//i,j : offset
	for (int i = BOARD_Y / 2; i < BOARD_Y - size.y; i++) {

		for (int j = 0; j < BOARD_X - size.x; j++) {

			match(point1<int>(j, i), rule.vanish[r_num]);
		}
	}
}

//��̈�}�b�`���O�i���[���I���j
void Board::Match3() {

	for (int r_num = 0; r_num < (int)rule.vanish.size(); r_num++) {

		lmatch(r_num);
	}
}

//�������ԍX�V����
int Board::update_time() {

	//�X�^�[�g����30[s]�ŏ�����
	if ( detach == false ) time = 30 * 60; //60FPS�Œ�ׁ̈D

	//0[s]�ɂȂ����Ƃ��Ƀ^�C�}��~
	if ( time > 0 ) time--;

	//�^�C�}�������C1��Ԃ�
	if ( time <= 0 ) {

		//�t���[�Y�^�C�~���O120�t���[��
		if( ( freeze < 120 ) && ( check_vanishing() ) ) freeze++;

		return 1;
	}

	return 0;
}

//���͕ϊ��l�X�V
void Board::update_input() {

	//�^�C���A�b�v���C�������s��Ȃ�
	if ( time == 0 ) return;

	//�^�C���̈�ɕϊ�
	ex_index.s = (Input::mouse.s_point - point1<int>(BOARD_OFFSET_X, BOARD_OFFSET_Y)) / GRAPH_SIZE_X;
	ex_index.e = (Input::mouse.e_point - point1<int>(BOARD_OFFSET_X, BOARD_OFFSET_Y)) / GRAPH_SIZE_X;

	//�}�C�i�X�C���f�b�N�X������
	if (Input::mouse.s_point.x < BOARD_OFFSET_X) ex_index.s.x--;
	if (Input::mouse.s_point.y < BOARD_OFFSET_Y) ex_index.s.y--;
	if (Input::mouse.e_point.x < BOARD_OFFSET_X) ex_index.e.x--;
	if (Input::mouse.e_point.y < BOARD_OFFSET_Y) ex_index.e.y--;

	//�h���b�O�������C�������{
	else if (Input::mouse.detach[0] &&
		isin(ex_index.s, point2<int>(0, BOARD_Y / 2, BOARD_X - 1, BOARD_Y - 1)) &&
		isin(ex_index.e, point2<int>(0, BOARD_Y / 2, BOARD_X - 1, BOARD_Y - 1)) &&
		(ABS((ex_index.e.x - ex_index.s.x)) == 1 && ABS((ex_index.e.y - ex_index.s.y)) == 0 ||
		 ABS((ex_index.e.x - ex_index.s.x)) == 0 && ABS((ex_index.e.y - ex_index.s.y)) == 1)
		) exchange(ex_index);

	//�f�^�b�`���o
	if (Input::mouse.detach[0]) detach = true;
}

//��{�X�V����
void Board::update_board() {

	//���U���g��ʓ��͌���
	int result_select = 0;

	//���U���g���
	if (freeze == 120) {

		//�n�C�X�R�A�X�V
		result.push(hiscore, score);

		//���U���g��ʓ��͏���
		result_select = result.input_update();

		//CONTINUE�Ȃ�΃Q�[���ĊJ EXIT�Ȃ�΃^�C�g���ɖ߂�
		state = result_select;

		//CONTINUE�Ȃ�΁C���Z�b�g���ă��X�^�[�g
		if(state == 1) reset();

		//EXIT�Ȃ�΁C�����T�C�Y�����ɖ߂�
		if(state == 2) SetFontSize(16);

		return;
	}

	//�^�C�}����
	update_time();

	//�}�b�`���O����
	Match3();

	//�����A�j���[�V����
	vanishTiles();

	//��������
	fallTiles();

	//�^�C������
	fill();
}

//�\������
void Board::draw_board() {

	//�w�i�̕`��
	DrawGraph(0, 0, Resource::BoardGraph[0], TRUE);

	if ( Input::mouse.push[0] && detach ) {

		//�^�C���̃h���b�O��
		drawTiles( ex_index.s );
	}
	else {

		//�^�C���̓h���b�O���łȂ�
		drawTiles( point1<int>(-1, -1) );
	}

	//�^�C�}�̕\��
	DrawFormatString(730, 230, white, "%d", time / 60);

	//�^�C�}�Q�[�W�̕\��
	DrawBox(670, 190, 670 + (int)(125 * ((double)time / (30 * 60))), 210, white, TRUE);
	DrawBox(670, 190, 795, 210, gray17, FALSE);

	//�X�R�A�̕\��
	if (score < hiscore[0]) {

		DrawFormatString(26, 138, white, "%d", score);
	}
	else {

		DrawFormatString(26, 138, sky, "%d", score);
	}

	//�n�C�X�R�A�̕\��
	DrawFormatString(26, 263, white, "%d", hiscore[0]);

	//�^�C���A�b�v���
	if ( !time ) DrawGraph(0, 0, Resource::Timeup, TRUE);

	//���U���g���
	if ( freeze == 120 ) result.draw_results();

	//DrawFormatString(0, 0, black, "%d", quick);
}

//�n�C�X�R�A��ۑ�����
void Result::save_hiscore() {

	//�t�@�C���X�g���[��
	std::ofstream ofs;

	//�������݃��[�h�ŃI�[�v��
	ofs.open("score.txt", std::ios::out);

	//�n�C�X�R�A����������
	for (int i = 0; (i < 10) && (file_hiscore[i] != 0); i++) {

		ofs << file_hiscore[i] << "\n";
	}

	//�t�@�C�����N���[�Y
	ofs.close();
}

//�V�t�g
void Result::shift(int index) {

	for (int i = 10 - 2; i >= index; i--) {

		file_hiscore[i + 1] = file_hiscore[i];
	}
}

//�X�R�A�����X�g�ɉ�����
void Result::push(const int hiscore[10], int score) {

	//file_hiscore[10]

	//�z��R�s�[
	for (int i = 0; i < 10; i++) {

		file_hiscore[i] = hiscore[i];
	}

	//�o�u���\�[�g [0]:�ō��_�� �� [9]:�Œ�_��
	for (int i = 0; i < 10; i++) {

		if (file_hiscore[i] < score) {

			//i�ȍ~���V�t�g���ďꏊ���J����
			shift( i );

			//�C���f�b�N�X
			index = i;

			//�󂢂��ꏊ�ɃX�R�A����
			file_hiscore[i] = score;

			break;
		}
	}

	//�X�R�A��1�ʂ��ŉ��ʂ�
	if ( index == 0 && (file_hiscore[9] > score)) {

		//�ŉ���
		index = 11;
	}

	//�n�C�X�R�A�X�V
	save_hiscore();
}

//���͎�t(0:�ێ� 1:CONTINUE 2:EXIT)
int Result::input_update() {

	int abs_select = 0;

	//�L�[�{�[�h�̉����������Ƃ�
	if (Input::key.value[KEY_INPUT_DOWN] == 1) {

		select++;
	}
	//�L�[�{�[�h�̏���������Ƃ�
	if (Input::key.value[KEY_INPUT_UP] == 1) {

		select--;
	}
	//�L�[�{�[�h�Ō��莞
	if (Input::key.value[KEY_INPUT_RETURN] == 1) {

		abs_select = ABS((select % 2));

		return (abs_select + 1);
	}
	//�}�E�X�őI����
	if (isin(Input::mouse.point, point2<int>(355, 495, 460, 525))) {

		select = 0;

		if (Input::mouse.push[0] == 1) {

			return 1;
		}
	}
	if (isin(Input::mouse.point, point2<int>(355, 535, 460, 565))) {

		select = 1;

		if (Input::mouse.push[0] == 1) {

			return 2;
		}
	}

	return 0;
}

//�X�R�A��\������
void Result::draw_results() {

	//�w�i
	DrawGraph(0, 0, Resource::Result, TRUE);

	//�C���f�b�N�X
	int abs_select = ABS((select % 2));

	//�X�R�A
	for (int i = 0; i < 10; i++) {

		//�n�C�X�R�A
		if ( file_hiscore[i] ) {

			DrawFormatString(360, 275 + 20 * i, white, "%2d %d", i + 1, file_hiscore[i]);
		}
		else {

			DrawFormatString(360, 275 + 20 * i, white, "%2d -", i + 1);
		}

		if ( i == index ) {

			//����X�R�A�������\��
			DrawBox(365, 275 + 20 * i, 455, 295 + 20 * i, white, FALSE);

			//NewRecord
			if( index == 0 ) DrawFormatString( 500, 275, white, "New Record!" );
		}
	}

	//GUI
	DrawBox(355, 495 + abs_select * 40, 460, 525 + abs_select * 40, white, FALSE);
	DrawFormatString(360, 500, white, "CONTINUE");
	DrawFormatString(385, 540, white, "EXIT");
}