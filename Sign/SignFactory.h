#pragma once

#include "SignBase.h"
#include "RandomQuickPressSign.h"
#include "MashButtonSign.h"
#include "QuickPressSign.h"
#include "RandomSign.h"

/// <summary>
/// 合図の生成クラス
/// </summary>
class SignFactory
{
private:
	static SignFactory* instance;								//インスタンス

private:
	class RandomQuickPressSign* random_quick_press_sign;		//ランダム早押し合図のインスタンス
	class MashButtonSign* mash_button_sign;						//連打の合図のインスタンス
	class QuickPressSign* quick_Press_sign;						//早押し合図のインスタンス
	class RandomSign* random_sign;								//ランダム合図のインスタンス

private:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SignFactory() = default;
	SignFactory(const SignFactory&) = delete;
	SignFactory& operator =(const SignFactory) = delete;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SignFactory() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

public:
	/// <summary>
	/// 終了時処理
	/// </summary>
	static void Finalize();

public:
	/// <summary>
	/// 合図を取得
	/// </summary>
	/// <param name="max_rand_val">ランダムな値の最大値</param>
	/// <returns>ランダムな合図</returns>
	static SignBase* GetSign(const int max_rand_val);

private:
	/// <summary>
	/// 指定した範囲のランダムな数字を取得
	/// </summary>
	/// <param name="min_val">最小値</param>
	/// <param name="max_val">最大値</param>
	/// <returns>ランダムな値</returns>
	int GetRandRange(int min_val, int max_val);
};

