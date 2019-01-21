#include "instructions.h"
#include "common.h"
#include "resource.h"

//更新
int instruction::update() {

	//連続入力防止
	if ( cont == 0 ) { 

		cont = 1;
		return 0; 
	}

	//ENTERか左クリックで進む
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

//描画
void instruction::draw() {

	//ルールの描画
	DrawGraph(0, 0, Resource::Rule, TRUE);

	//test
	//DrawFormatString(0, 0, black, "%d", cont);
}