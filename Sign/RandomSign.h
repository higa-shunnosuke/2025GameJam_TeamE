#pragma once

#include "SignBase.h"

/// <summary>
/// ランダム合図のクラス
/// </summary>
class RandomSign :public SignBase
{
private:
	std::vector<std::vector<int>> button;			//ボタン

	float alpha_blend_1;							//プレイヤー1のボタンを透過する値
	float alpha_blend_2;							//プレイヤー2のボタンを透過する値

	bool is_alpha_blend_1;							//プレイヤー1のボタンを透過させる？
	bool is_alpha_blend_2;							//プレイヤー2のボタンを透過させる？

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	RandomSign();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~RandomSign();

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize()override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void Update(float delta_second) override;

	/// <summary>
	/// 終了時処理
	/// </summary>
	virtual void Finalize()override;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() const override;

public:
	/// <summary>
	/// 合図の名前を取得
	/// </summary>
	/// <returns>合図の名前</returns>
	virtual std::string GetSignName()const override;

public:
	/// <summary>
	/// ボタンを取得
	/// </summary>
	/// <param name="element">配列番号</param>
	/// <returns>ボタン</returns>
	std::vector<int> GetButton(const int element) { return button[element]; }

};

