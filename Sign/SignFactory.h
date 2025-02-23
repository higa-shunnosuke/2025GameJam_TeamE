#pragma once

/// <summary>
/// 合図生成クラス
/// </summary>
class SignFactory
{
private:
	static SignFactory* instance;								//合図生成クラスのインスタンス

private:
	class RandomQuickPressSign* random_quick_press_sign;		//ランダム早押し合図のインスタンス
	class MashButtonSign* mash_button_sign;						//連打の合図のインスタンス
	class QuickPressSign* quick_Press_sign;						//早押し合図のインスタンス
	class RandomSign* random_sign;								//ランダム合図のインスタンス
	class FeintSign* feint_sign;								//フェイント合図のインスタンス

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
	static class SignBase* GetSign(const int max_rand_val);
};

