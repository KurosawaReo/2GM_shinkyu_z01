/*
   - Player.h -
   プレイヤー管理.
*/
#pragma once

class Player
{
private:
	Circle hit{};       //プレイヤーの当たり判定円.
	int    graph{};     //画像データ.
	BOOL   active{};    //有効か.
	
	float  reflectionCooldown{}; //反射のクールダウン時間.

	GameData* p_data{}; //ゲームデータ.

	BOOL   isDebug{};   //デバッグ用.

public:

	//set.
	void    SetActive(BOOL _active) { active = _active; }
	//get. 
	DBL_XY  GetPos()   { return hit.pos; }
	BOOL    GetActive(){ return active; }
	Circle* GetHit()   { return &hit; }

	//その他.
	void Init  (GameData*);
	void Reset (DBL_XY _pos, BOOL _active);
	void Update();
	void Draw  ();

	void PlayerMove();  //プレイヤー移動.
	void PlayerDeath(); //プレイヤー死亡.

	BOOL  IsReflectionMode() const;			//反射モードかどうかを返す.
	float GetReflectionCooldown() const;	//クールダウン時間を持つ.
	void  UseReflection();					//反射を使用.
};