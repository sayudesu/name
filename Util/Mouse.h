#pragma once

#include "Vec2.h"

// マウスの入力状態を取得する
namespace Mouse
{
	// マウスの入力状態取得
	void update();

	// 現在のマウス位置取得
	Vec2 getPos();

	// 押し下げ判定
	bool isPressLeft();
	// トリガー判定
	bool isTriggerLeft();
	// 離した判定
	bool isRelaseLeft();
}
