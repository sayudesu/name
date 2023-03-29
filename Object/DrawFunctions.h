#pragma once
#include <tchar.h>

// 自分用ライブラリ用名前空間
namespace my {
	/// <summary>
	/// 画像をロードする
	/// </summary>
	/// <param name="path">パス文字列</param>
	/// <returns>画像のハンドル</returns>
	int MyLoadGraph(const TCHAR* path);
	//画像データのメモリ解放
	int MyDeleteGraph( int handle);
	//座標での位置、画像の左上右下、拡大率、角度、グラフィックハンドル、画像の透過、画像反転
	int MyDrawRectRotaGraph(int x, int y,
							int left, int top,
							int width, int height,
							float scale, float angle,
							int handle, bool transFlg, bool transFlg2);

	//左上右下、グラフィックハンドル、画像の透過
	int MyDrawExtendGraph(int left, int top, 
						  int right, int bottom,
						  int handle, bool flag);
}
