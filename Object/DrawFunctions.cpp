#include <DxLib.h>
#include <cassert>
#include "DrawFunctions.h"

namespace my
{
	/// <summary>
	/// グラフィクスをロードする
	/// </summary>
	/// <param name="path">画像ファイルのパス</param>
	/// <returns>画像のハンドル</returns>
	int MyLoadGraph(const TCHAR* path) {
		int handle = LoadGraph(path);
		//ハンドルは正しく代入されているか確認
		assert(handle != -1);//初期値を-1に指定する
		return handle;
	}
	//画像データのメモリ解放
	int MyDeleteGraph(int handle)
	{
		//Dxlibの関数の引数に渡す
		return DeleteGraph(handle);
	}
	//座標での位置、画像の左上右下、拡大率、角度、グラフィックハンドル、画像の透過、画像反転
	int MyDrawRectRotaGraph(int x, int y, int left, int top, int width, int height, float scale, float angle, int handle, bool transFlg, bool transFlg2)
	{
		//Dxlibの関数の引数に渡す
		return DrawRectRotaGraph(x,y,
								 left,top,
								 width,height,
								 scale,angle,
								 handle,transFlg, transFlg2);
	}
	//左上右下、グラフィックハンドル、画像の透過
	int MyDrawExtendGraph(int left, int top, int right, int bottom, int handle, bool flag)
	{
		//Dxlibの関数の引数に渡す
		return DrawExtendGraph(left, top,
							   right, bottom,
							   handle, flag);
	}
}// end of namespace my