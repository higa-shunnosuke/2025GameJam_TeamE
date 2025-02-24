#pragma once

#include "SignBase.h"

/// <summary>
/// 合図の結果状態
/// </summary>
enum class SignResult
{
	None = 0,			//なし
	Player1_Point,		//プレイヤー1にポイント
	Player1_Faul,		//プレイヤー1にファール
	Player2_Point,		//プレイヤー2にポイント
	Player2_Faul		//プレイヤー2にファール
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

	/// <summary>
	/// 合図の結果を取得
	/// </summary>
	SignResult GetSignResult();
};

