/*
   - myDrawST.h - (original)
   ver.2025/07/19

   DxLib: オリジナル描画機能の追加.
*/
#pragma once

//フォントタイプID(入力しやすくする用)
enum FONTTYPE_ID
{
	FONT_NORMAL = DX_FONTTYPE_NORMAL,
	FONT_EDGE   = DX_FONTTYPE_EDGE,

	FONT_NONE   = -1, //指定なし.
};
//描画モードID(入力しやすくする用)
enum BLENDMODE_ID
{
	MODE_NONE  = DX_BLENDMODE_NOBLEND, //デフォルト.
	MODE_ALPHA = DX_BLENDMODE_ALPHA,   //αブレンド.
	MODE_ADD   = DX_BLENDMODE_ADD,     //加算ブレンド.
	MODE_SUB   = DX_BLENDMODE_SUB,     //減算ブレンド.
	MODE_MUL   = DX_BLENDMODE_MUL      //乗算ブレンド.
};

//画像描画に使う用.
struct IMG_DRAW
{
	IMG    img;      //画像データ.
	INT_XY pos;      //画面のどこに描画するか.
};
struct IMG_DRAW_RECT
{
	IMG    img;      //画像データ.
	INT_XY pos;      //画面のどこに描画するか.(左上座標基準)
	INT_XY stPxl;    //始点pixel.
	INT_XY size;     //切り取るサイズ.
};
struct IMG_DRAW_EXTEND
{
	IMG    img;		 //画像データ.
	INT_XY pos;		 //基準点.
	INT_XY size;	 //描画するサイズ.
};
struct IMG_DRAW_ROTA
{
	IMG    img;      //画像データ.
	INT_XY pos;      //画面のどこに描画するか.
	double extend;   //サイズ倍率.
	double ang;      //角度.
};
//文字描画に使う用.
struct STR_DRAW
{
	TCHAR  text[256]{};        //テキスト.
	INT_XY pos;                //画面のどこに描画するか.
	UINT   color = 0xFFFFFF;   //文字の色.
};
struct STR_DRAW_ROTA
{
	TCHAR  text[256]{};        //テキスト.
	INT_XY pos;                //画面のどこに描画するか.
	INT_XY extend = {1, 1};    //伸縮倍率.
	INT_XY pivot  = {0, 0};    //回転基準点.
	double ang    = 0;         //回転度.
	UINT   color  = 0xFFFFFF;  //文字の色.
};
struct STR_DRAW_MODI
{
	TCHAR  text[256]{};        //テキスト.
	INT_XY luPos;              //テキストの左上座標.
	INT_XY ruPos;              //テキストの右上座標.
	INT_XY rdPos;              //テキストの右下座標.
	INT_XY ldPos;              //テキストの左下座標.
	UINT   color = 0xFFFFFF;   //文字の色.
};

//図形.
int    DrawCircleST		 (const Circle* data, BOOL isFill = TRUE, int thick = 1);
int    DrawBoxST		 (const Box*    data, BOOL isCenter, BOOL isFill = TRUE);
int    DrawLineST		 (const Line*   data, int  thick = 1);
int    DrawWindowGrid	 (int wid, int hei, int size, UINT clrWid = 0xA0A0FF, UINT clrHei = 0xFFA0A0);

//画像.
int    LoadGraphST		 (IMG* img, const TCHAR fileName[]);
int    LoadDivGraphST	 (vector<IMG>* img, const TCHAR fileName[], INT_XY size, INT_XY cnt);
int    DrawGraphST		 (const IMG_DRAW*        data, BOOL isCenter, BOOL isTrans = TRUE);
int    DrawRectGraphST	 (const IMG_DRAW_RECT*   data, BOOL isTrans = TRUE);
int    DrawExtendGraphST (const IMG_DRAW_EXTEND* data, BOOL isCenter, BOOL isTrans = TRUE);
int    DrawRotaGraphST	 (const IMG_DRAW_ROTA*   data, BOOL isCenter, BOOL isTrans = TRUE);

//テキスト.
int    DrawStringST		 (const STR_DRAW*      data, BOOL isCenter,   int font = -1);
int    DrawRotaStringST	 (const STR_DRAW_ROTA* data, BOOL isVertical, int font = -1);
int    DrawModiStringST	 (const STR_DRAW_MODI* data, BOOL isVertical, int font = -1);
INT_XY GetTextSize		 (const TCHAR str[], int font = -1);

//フォント.
int    CreateFontH		 (int size, int thick, FONTTYPE_ID fontId = FONT_NONE);

//オブジェクト.
int    DrawObjectGrid	 (const ObjectGrid* data, INT_XY gridPos, INT_XY gridSize);
int    DrawObjectBox	 (const ObjectBox*  data, BOOL isDrawHit = FALSE);
int    DrawObjectCir	 (const ObjectCir*  data, BOOL isDrawHit = FALSE);

//描画モード.
int    SetDrawBlendModeST(BLENDMODE_ID id, int power = 255);
int    ResetDrawBlendMode();