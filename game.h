#pragma once

namespace Game
{
	// ウインドウモード設定
	constexpr bool kWindowMode = true;
	// マウスカーソル表示
	constexpr bool kMouseMode = true;
	// ウインドウ名
	const char* const kTitleText = "ゲーム名";
	// ウインドウサイズ
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;
	// カラーモード
	constexpr int kColorDepth = 32;		// 32 or 16
};