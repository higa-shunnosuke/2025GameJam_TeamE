#pragma once

#include "SignBase.h"

class RandomQuickPressSign :public SignBase
{
public:
	//コンストラクタ
	RandomQuickPressSign();

	//デストラクタ
	~RandomQuickPressSign();

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

private:
	//押させるボタンを決める
	int ChooseButton();

};

