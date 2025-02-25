#pragma once

#include "..//SceneBase.h"

//カットシーンタイプ
enum CutSceneType {
	Start,			//ゲーム開始
	Player1_Win,	//１Pの勝利
	Player2_Win,	//２Pの勝利
	TieGame			//引き分け
};

class InGame : public SceneBase
{
private:
	class SignManager* sign_manager;
	class ButtonMatch* button_match;
	Data player1;
	Data player2;
	eSceneType old_type;

public:
	// コンストラクタ
	InGame();
	// デストラクタ
	virtual ~InGame();

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレーム当たりの時間</param>
	/// <returns>次のシーンタイプ情報</returns>
	virtual eSceneType Update(const float& delta_second) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() const override;

	/// <summary>
	/// 終了時処理
	/// </summary>
	virtual void Finalize() override;

	/// <summary>
	/// 現在のシーンタイプ情報を取得する
	/// </summary>
	/// <returns>現在のシーンタイプ</returns>
	virtual const eSceneType GetNowSceneType() const override;

	/// <summary>
	/// 前のシーンタイプを設定する
	/// </summary>
	/// <param name="old_type">前のシーンタイプ</param>
	void SetOldSceneType(eSceneType old_type);

private:
	/// <summary>
	/// ファイルデータ書き込み処理
	/// </summary>
	void WriteData();

	/// <summary>
	/// ファイルデータ読み込み処理
	/// </summary>
	void ReadData();

	/// <summary>
	/// カットシーン再生処理
	/// </summary>
	void PlayCatScene(CutSceneType type);
};