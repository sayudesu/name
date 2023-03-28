#include "Mouse.h"
#include "DxLib.h"

namespace
{
	constexpr int kLogNum = 16;
	// 入力ログ	0が最新の状態
	int mouseLog[kLogNum];
}

namespace Mouse
{
	// マウスの入力状態取得
	void update()
	{
		// ログの更新
		for (int i = kLogNum - 1; i >= 1; i--)
		{
			mouseLog[i] = mouseLog[i-1];
		}
		// 最新の状態
		if (GetMouseInput() & MOUSE_INPUT_LEFT)
		{
			mouseLog[0] = 1;
		}
		else
		{
			mouseLog[0] = 0;
		}
	}

	// 現在のマウス位置取得
	Vec2 getPos()
	{
		Vec2 mousePos{ 0,0 };
		int mouseX = 0;
		int mouseY = 0;
		if (GetMousePoint(&mouseX, &mouseY) == -1)
		{
			// エラー発生
			return mousePos;
		}
		mousePos.x = static_cast<float>(mouseX);
		mousePos.y = static_cast<float>(mouseY);
		return mousePos;
	}

	// 押し下げ判定
	bool isPressLeft()
	{
		return (mouseLog[0]);
	}
	// トリガー判定
	bool isTriggerLeft()
	{
		bool isNow = (mouseLog[0]);	// 現在の状態
		bool isLast = (mouseLog[1]);	// １フレーム前の状態
		return (isNow && !isLast);
	}
	// 離した判定
	bool isRelaseLeft()
	{
		bool isNow = (mouseLog[0]);	// 現在の状態
		bool isLast = (mouseLog[1]);	// １フレーム前の状態
		return (!isNow && isLast);
	}
}