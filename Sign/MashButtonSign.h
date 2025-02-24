#pragma once

#include "SignBase.h"

/// <summary>
/// 連打合図のクラス
/// </summary>
class MashButtonSign :public SignBase
{
private:
	std::vector<int> score_bar;			//連打時に表示するバー

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MashButtonSign();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MashButtonSign();

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
	///	バーが最大かどうか取得する
	/// </summary>
	/// <param name="element">配列番号</param>
	/// <returns>true :最大	false : 最大ではない</returns>
	bool IsMaximum(const int element);

};
