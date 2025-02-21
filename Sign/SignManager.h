#pragma once

/// <summary>
/// 合図の管理クラス
/// </summary>
class SignManager
{
private:
	class SignBase* sign;		//合図

	int fake_count;				//再度フェイクをだすためのカウント

public:
	//コンストラクタ
	SignManager();

	//デストラクタ
	~SignManager();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Update(float delta_second);

	/// <summary>
	/// 終了時処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const;
};

