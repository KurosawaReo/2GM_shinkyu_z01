/*
   - Global.h -

   共通で使用する型やマクロを入れる所.
*/
#pragma once

//このGlobal.hが定義されているか判別する用.
#define DEF_GLOBAL_H

//stdafxがあるならいらない.
#if true
  #define _USE_MATH_DEFINES  //math定数を使うのに必要.
  #define _CRT_SECURE_NO_WARNINGS
  #include <assert.h>
  #include <math.h>
  #include <stdlib.h>
  #include <time.h>
  #include "DxLib.h"
#endif

//int型の凝縮xy.
struct INT_XY
{
	int x;
	int y;
};
//double型の凝縮xy.
struct DBL_XY
{
	double x;
	double y;
};
//画像データ格納用.
struct IMG
{
	int    handle;	 //ハンドル.
	INT_XY size;	 //画像のサイズ.
};

//円データ.
struct Circle
{
	DBL_XY pos;  //座標.
	float  r;    //半径.
	UINT   clr;  //色.
};
//四角形データ.
struct Box
{
	DBL_XY pos;  //座標.
	DBL_XY size; //サイズ.
	UINT   clr;  //色.
};
//線データ.
struct Line
{
	DBL_XY stPos; //始点座標.
	DBL_XY edPos; //終点座標.
	UINT   clr;   //色.
};
//オブジェクト(四角形)
struct ObjectBox
{
	Box    box{};      //当たり判定と座標.
	DBL_XY offset{};   //画像をずらす量.
	IMG    img{};      //画像.
	BOOL   isActive{}; //有効かどうか.

	//初期化用.
	ObjectBox(){}
	//初期化用(引数あり)
	ObjectBox(DBL_XY _pos, DBL_XY _size, DBL_XY _offset, UINT _clr, BOOL _isActive) :
		box     ({_pos, _size, _clr}), 
		offset  (_offset), 
		isActive(_isActive)
	{}
};
//オブジェクト(円)
struct ObjectCir
{
	Circle cir{};      //当たり判定と座標.
	DBL_XY offset{};   //画像をずらす量.
	IMG    img{};      //画像.
	BOOL   isActive{}; //有効かどうか.

	//初期化用.
	ObjectCir(){}
	//初期化用(引数あり)
	ObjectCir(DBL_XY _pos, float _r, DBL_XY _offset, UINT _clr, BOOL _isActive) :
		cir     ({ _pos, _r, _clr }), 
		offset  (_offset), 
		isActive(_isActive)
	{}
};

//型変換マクロ.
#define _int(n)   (int)(round(n))            //int   型変換マクロ.
#define _intXY(n) {_int(n.x), _int(n.y)}     //INT_XY型変換マクロ.
#define _dblXY(n) {(double)n.x, (double)n.y} //DBL_XY型変換マクロ.

#define _if_check(n) assert(n); if(n)        //if文の前に同条件のassertを挟む.

// - 列挙体 -
enum Scene
{
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_END,
};
//レーザー移動列挙.
enum MoveDir 
{
	MOVE_RIGHT,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_UP
};
// - ゲームデータ -
struct GameData
{
	Scene scene;     //シーンの記録用.
	BOOL  isSlow;    //スローモードかどうか.
	int   font1;     //フォント.
	int   font2;     //フォント.
};

// - 定数 -
#define IS_WINDOW_MODE				(FALSE)			//ウィンドウモードにするか.

#define WINDOW_WID					(1920)			//ウィンドウの横幅.
#define WINDOW_HEI					(1080)			//ウィンドウの縦幅.
#define WINDOW_COLOR_BIT			(32)			//ウィンドウのカラーbit数.

#define FPS							(80)			//フレームレート.

#define SLOW_MODE_TIME				(5)             //スローモード制限時間.
#define SLOW_MODE_SPEED				(0.20f)			//スローモード速度倍率.

#define PLAYER_SIZE					(20)			//プレイヤーサイズ.
#define PLAYER_MOVE_SPEED			(6)				//プレイヤー移動速度.
#define PLAYER_HIT_R				(10)			//プレイヤーの当たり判定円の半径.
#define PLAYER_REF_COOLDOWN			(0)				//反射クールダウン時間.

#define ITEM_SIZE					(20)			//アイテムサイズ.
#define ITEM_SPEED					(3)				//アイテム移動スピード.  
#define ITEM_RESPAWN_TIME			(300)           //アイテム復活時間.

#define OBSTACLE2_SPAN				(80)			//障害物の発射間隔.
#define OBSTACLE2_SPEED				(3.0)			//障害物の速度.
#define	OBSTACLE2_ROT_MAX			(5.0)			//障害物の追尾力(1フレームで回転できる最大度数)
#define OBSTACLE2_LIM_F				(80)			//最大追跡フレーム数.

#define OBSTACLE3_SIZE				(20)			//障害物サイズ.
#define OBSTACLE3_TRACK_POW			(8)				//障害物の追尾力.
#define OBSTACLE3_SPEED				(3)				//障害物の速度.

#define OBSTACLE4_OUTER_MARGIN		(0)				//砲台の周回時の外側余白.
#define OBSTACLE4_SHOT_RESET		(80)			//砲台の発射リセット時間.
#define OBSTACLE4_SHOT_START		(20)			//砲台の発射開始時間.
#define OBSTACLE4_SHOT_SPAN			(10)			//砲台の発射間隔時間.
#define OBSTACLE4_LASER_SPEED		(150)			//レーザーの速度.
#define OBSTACLE4_LASER_LIM			(100)			//レーザーの最大数.
#define OBSTACLE4_LINE_MAX			(2000)			//レーザーで描画する線の最大数.

#define OBSTACLE4_FLASH_MAX         (30)            //最大フラッシュエフェクト数
#define OBSTACLE4_FLASH_SIZE_INIT   (1.0f)          //フラッシュエフェクトの初期サイズ.
#define OBSTACLE4_FLASH_SIZE_SPREAD (2)             //フラッシュエフェクトの拡大量.
#define OBSTACLE4_FLASH_VALID_TM	(50)            //フラッシュエフェクトの持続フレーム.
#define OBSTACLE4_FLASH_ALPHA_TM	(2)             //フラッシュエフェクトの透明化速度.

#define METEO_CNT_MAX				(256)			//隕石の最大出現数.
#define METEO_SPAWN_SPAN			(10)			//隕石の出現時間間隔.
#define METEO_LINE_MAX				(16)			//最大16角形.
#define METEO_SPEED					(5)				//移動速度.
#define METEO_ERASE_OUT_DIS			(50)			//隕石が画面外で消える距離.
#define METEO_GOAL_RAND_RANGE		(500)			//隕石の目標地点の乱数範囲.