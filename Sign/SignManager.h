#pragma once

#include "SignBase.h"

enum class SignResult
{
	None = 0,
	Player1_Point,
	Player1_Faul,
	Player2_Point,
	Player2_Faul
};

/// <summary>
/// 合図管理クラス
/// </summary>
class SignManager
{
private:
	SignBase* sign;					//合図のインスタンス

	int feint_count;				//再度フェイクをだすためのカウント

	float count_time;				//計測時間

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SignManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
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

public:
	/// <summary>
	/// 合図のインスタンスを取得
	/// </summary>
	/// <returns>合図のインスタンス</returns>
	SignBase* GetSignInstance()const;

	SignResult GetSignResult();
};

