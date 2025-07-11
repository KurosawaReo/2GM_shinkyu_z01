/*
   - MeteoManager.h -
   隕石の出現を管理する.
*/
#pragma once
#include "Meteo.h"

//隕石管理.
class MeteoManager
{
private:
	Meteo meteo[METEO_CNT_MAX]{}; //隕石データ.
	float timer{};			      //隕石生成用.

	GameData* p_data{};           //ゲームデータ.
	Player*   p_player{};		  //プレイヤーデータ.

public:
	void Init(GameData*, Player*);
	void Reset();
	void Update();
	void Draw();

	void SpawnMeteo(); //隕石生成.

	BOOL IsHitMeteos(Circle* pos, BOOL isDestroy); //隕石のどれか1つでも当たっているか.
	BOOL GetMeteoPosNearest(DBL_XY _startPos, DBL_XY* _nearPos); //最寄りの隕石座標を探す.
};