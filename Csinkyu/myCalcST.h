/*
   - myCalcST.h - (original)
   ver.2025/07/24

   DxLib: オリジナル計算機能の追加.
*/
#pragma once

//角度変換用.
#define _rad(x) (x)*(M_PI/180)
#define _dig(x) (x)*(180/M_PI)

//当たり判定.
BOOL   HitCircle		(const Circle* cir1, const Circle* cir2);
BOOL   HitBox			(const Box*    box1, const Box*    box2,  BOOL isCenter);
BOOL   HitLine			(const Line*   line, const Circle* cir);

//移動限界.
void   FixPosInArea		(DBL_XY* pos, INT_XY size, int left, int up, int right, int down);
BOOL   IsOutInArea		(DBL_XY  pos, INT_XY size, int left, int up, int right, int down, BOOL isCompOut);

//計算.
double CalcDist			(INT_XY pos1,  INT_XY pos2);
double CalcDist			(DBL_XY pos1,  DBL_XY pos2);
DBL_XY CalcMidPos		(DBL_XY pos1,  DBL_XY pos2);
DBL_XY CalcArcPos		(DBL_XY stPos, double ang, double len);
double CalcFacingAng	(DBL_XY stPos, DBL_XY targetPos);
DBL_XY CalcDigToPos		(double dig);
DBL_XY CalcRadToPos		(double rad);

//値の曲線変動(アニメーション用)
double CalcNumEaseIn	(double time);
double CalcNumEaseOut	(double time);
double CalcNumEaseInOut	(double time);
double CalcNumWaveLoop	(double time);

//値の操作.
int    RandNum			(int st, int ed, BOOL isDxRand = FALSE);
double GetDecimal		(double num);