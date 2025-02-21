#pragma once

#include "SignBase.h"
#include"RandomQuickPressSign.h"

class SignFactory
{
private:
	static SignFactory* instance;			//インスタンス

private:
	class RandomQuickPressSign* random_quick_press_sign;

private:
	//コンストラクタ
	SignFactory() = default;
	SignFactory(const SignFactory&) = delete;
	SignFactory& operator =(const SignFactory) = delete;

	//デストラクタ
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
	uint64_t GetRandRange(uint64_t min_val, uint64_t max_val);
};

