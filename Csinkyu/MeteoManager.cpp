/*
   - MeteoManager.cpp -
   隕石の出現を管理する.
*/
#include "MeteoManager.h"

void MeteoManager::Init(GameData* _data, Player* _player) {

	p_data   = _data;
	p_player = _player;

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Init(_data);
	}
}

void MeteoManager::Reset() {

	timer = 0;

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Reset();
	}
}

void MeteoManager::Update() {

	//タイマーが残っていれば.
	if (timer > 0) {
		timer -= (float)((p_data->isSlow) ? SLOW_MODE_SPEED : 1);
	}
	//タイマーが0になったら.
	else {
		SpawnMeteo(); //隕石生成.
	}

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Update(); //更新.
	}
	//プレイヤーとの当たり判定.
	if (IsHitMeteos(p_player->GetHit(), FALSE)) {
		p_player->PlayerDeath(); //死亡.
	}
}

void MeteoManager::Draw() {

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		meteo[i].Draw(); //描画.
	}
}

//隕石生成.
void MeteoManager::SpawnMeteo(){

	//空いてる所を探す.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		if (!meteo[i].GetActive()) {

			meteo[i].Spawn();         //出現.
			timer = METEO_SPAWN_SPAN; //タイマー再開.
			break; //出現完了.
		}
	}
}

//隕石のどれか1つでも当たっているか.
BOOL MeteoManager::IsHitMeteos(Circle* pos, BOOL isDestroy) {

	BOOL hit;

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		hit = meteo[i].IsHitMeteo(pos); //1こずつ判定.
		//当たれば.
		if (hit) {
			if (isDestroy) {
				meteo[i].Destroy(); //隕石を破壊.
			}
			return TRUE; //1つでも当たっている.
		}
	}
	return FALSE; //どれも当たっていない.
}

//最寄りの隕石座標を探す.
BOOL MeteoManager::GetMeteoPosNearest(DBL_XY _startPos, DBL_XY* _nearPos) {

	BOOL isExistMeteo = FALSE; //1つでも隕石があるか.
	double shortest = -1; //暫定の最短距離.

	//全隕石ループ.
	for (int i = 0; i < METEO_CNT_MAX; i++) {
		//有効かつ、破壊されてないなら.
		if (meteo[i].GetActive() && meteo[i].GetState() == Meteo_Normal) {

			DBL_XY tmpPos = meteo[i].GetPos();          //1つずつ座標取得.
			double tmpDis = CalcDis(tmpPos, _startPos); //距離を計算.

			//初回限定.
			if (shortest == -1) {
				shortest  = tmpDis; //暫定1位.
				*_nearPos = tmpPos;
			}
			//より近い場所が見つかれば更新.
			else if (tmpDis < shortest){
				shortest  = tmpDis;
				*_nearPos = tmpPos;
			}

			isExistMeteo = TRUE; //隕石がある.
		}
	}

	return isExistMeteo;
}