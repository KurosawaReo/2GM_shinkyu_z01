/*
   - myInputST.cpp - (original)
   ver.2025/07/24

   DxLib: オリジナル入力機能の追加.
*/
#if !defined DEF_GLOBAL_H
  #include "Global.h" //stdafx等に入ってなければここで導入.
#endif
#include "myInputST.h"

InputST InputST::self; //実体の宣言.

//キー入力の判定.
BOOL InputST::IsPushKey(KeyID id) {
	return (tmKey[id] > 0);     //押してるならTRUE.
}
int  InputST::IsPushKeyTime(KeyID id) {
	return tmKey[id];           //押している時間.
}
//マウス入力の判定.
BOOL InputST::IsPushMouse(MouseID id) {
	int num = (int)log2(id);    //2進数bitを何桁目かに変換.
	return (tmMouse[num] > 0);  //押してるならTRUE.
}
int  InputST::IsPushMouseTime(MouseID id) {
	int num = (int)log2(id);    //2進数bitを何桁目かに変換.
	return tmMouse[num];        //押している時間.
}
//コントローラ入力の判定.
BOOL InputST::IsPushPadBtn(PadBtnID id) {
	int num = (int)log2(id);    //2進数bitを何桁目かに変換.
	return (tmPadBtn[num] > 0); //押している時間.
}
int  InputST::IsPushPadBtnTime(PadBtnID id) {
	int num = (int)log2(id);    //2進数bitを何桁目かに変換.
	return tmPadBtn[num];       //押している時間.
}

//マウス座標取得.
void InputST::GetMousePos(DBL_XY* pos, BOOL isValidX, BOOL isValidY) {
	
	//xを反映させる.
	if (isValidX) {
		pos->x = (double)mPos.x; //double型にして反映.
	}
	//yを反映させる.
	if (isValidY){
		pos->y = (double)mPos.y; //double型にして反映.
	}
}
//コントローラスティック操作取得.
void InputST::GetPadStickVec(DBL_XY* pos) {
	//範囲-1000〜1000を-1.0〜1.0に変換.
	pos->x = (double)stickVec.x/1000;
	pos->y = (double)stickVec.y/1000;
}

//キーボード:十字キー操作.
void InputST::InputKey4Dir(DBL_XY* pos, float speed) {

	INT_XY pow{}; //移動力.

	//キー入力に応じて移動力を与える.
	if (IsPushKey(KEY_UP)   ||IsPushKey(KEY_W)) {
		pow.y += -1;
	}
	if (IsPushKey(KEY_DOWN) ||IsPushKey(KEY_S)) {
		pow.y += +1;
	}
	if (IsPushKey(KEY_LEFT) ||IsPushKey(KEY_A)) {
		pow.x += -1;
	}
	if (IsPushKey(KEY_RIGHT)||IsPushKey(KEY_D)) {
		pow.x += +1;
	}

	//座標移動.
	pos->x += Move4Dir(pow).x * speed;
	pos->y += Move4Dir(pow).y * speed;
}
//コントローラ:十字キー操作.
void InputST::InputPad4Dir(DBL_XY* pos, float speed) {

	INT_XY pow{};  //移動力.

	//キー入力に応じて移動力を与える.
	if (IsPushPadBtn(PAD_BTN_UP)) {
		pow.y += -1;
	}
	if (IsPushPadBtn(PAD_BTN_DOWN)) {
		pow.y += +1;
	}
	if (IsPushPadBtn(PAD_BTN_LEFT)) {
		pow.x += -1;
	}
	if (IsPushPadBtn(PAD_BTN_RIGHT)) {
		pow.x += +1;
	}

	//座標移動.
	pos->x += Move4Dir(pow).x * speed;
	pos->y += Move4Dir(pow).y * speed;
}
//コントローラ:スティック操作.
void InputST::InputPadStick(DBL_XY* pos, float speed) {
	
	DBL_XY vec;
	GetPadStickVec(&vec); //入力取得.

	//座標移動.
	pos->x += vec.x * speed;
	pos->y += vec.y * speed;
}
//移動4方向処理(斜め計算)
DBL_XY InputST::Move4Dir(INT_XY pow){

	DBL_XY move{}; //求めた移動量.

	//移動力があれば.
	if (pow.x != 0 || pow.y != 0) {
		//角度にする.
		double theta = atan2(pow.y, pow.x);
		//移動量を求める.
		move = { cos(theta), sin(theta) };
		//ほぼ0の値なら0と見なす(計算上誤差があるため)
		if (fabs(move.x) < 0.0001) { move.x = 0; }
		if (fabs(move.y) < 0.0001) { move.y = 0; }
	}

	return move;
}

//ボタンの更新処理.
void InputST::UpdateKey() {
	
	char key[KEY_MAX];
	GetHitKeyStateAll(key); //押しているキー情報を取得.
	
	for (int i = 0; i < KEY_MAX; i++) {
		//押されているなら.
		if (key[i] != 0) {
			tmKey[i]++;   //カウント.
		}
		else {
			tmKey[i] = 0; //0秒にリセット.
		}
	}
}
//マウスの更新処理.
void InputST::UpdateMouse() {

	//マウス座標取得.
	GetMousePoint(&mPos.x, &mPos.y);

	for (int i = 0; i < MOUSE_MAX; i++) {
		//押されているなら.
		if ((GetMouseInput() & (1 << i)) != 0) { //And演算で抽出.
			tmMouse[i]++;   //カウント.
		}
		else {
			tmMouse[i] = 0; //0秒にリセット.
		}
	}
}
//コントローラの更新処理.
void InputST::UpdatePad() {

	//スティック入力取得.
	GetJoypadAnalogInput(&stickVec.x, &stickVec.y, DX_INPUT_PAD1);

	for (int i = 0; i < PAD_BTN_MAX; i++) {
		//押されているなら.
		if (GetJoypadInputState(DX_INPUT_PAD1) & (1 << i)) { //And演算で抽出.
			tmPadBtn[i]++;   //カウント.
		}
		else {
			tmPadBtn[i] = 0; //0秒にリセット.
		}
	}
}