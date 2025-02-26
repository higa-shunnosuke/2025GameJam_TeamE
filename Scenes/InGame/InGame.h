#pragma once

#include "..//SceneBase.h"

enum CutType
{
	Start = 0,
	Win_Player1,
	Win_Player2,
	Foul_Player1,
	Foul_Player2,
	TieGame
};

class InGame : public SceneBase
{
private:
	class SignManager* sign_manager;
	class ButtonMatch* button_match;
	Data player1;
	Data player2;

	std::vector<int> ui_image;

	int cut_scene;				//カットシーン
	CutType type;				//カットシーンタイプ
	float time;					//カットシーン再生時間

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
	/// カットシーン生成処理
	/// </summary>
	void CreateCutScene(CutType type);

};