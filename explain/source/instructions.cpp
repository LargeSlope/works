#include "instructions.h"
#include "common.h"
#include "resource.h"

//�X�V
int instruction::update() {

	//�A�����͖h�~
	if ( cont == 0 ) { 

		cont = 1;
		return 0; 
	}

	//ENTER�����N���b�N�Ői��
	if ( Input::key.value[KEY_INPUT_RETURN] == 1 ) { 

		cont = 0; 
		return 1; 
	}
	if ( Input::mouse.push[0] == 1 ) { 

		cont = 0; 
		return 1; 
	}

	return 0;
}

//�`��
void instruction::draw() {

	//���[���̕`��
	DrawGraph(0, 0, Resource::Rule, TRUE);

	//test
	//DrawFormatString(0, 0, black, "%d", cont);
}