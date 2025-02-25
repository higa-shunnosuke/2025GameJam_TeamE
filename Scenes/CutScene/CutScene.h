#include "..//SceneBase.h"
#include <time.h>

class CutScene : public SceneBase
{
private:
	Data player1;
	Data player2;
	eSceneType old_type;	//前のシーンタイプ
	int cut_scene;			//カットシーン
	int t;					//経過時間
	time_t old_t;			//前回の時刻
	time_t now_t;			//現在の時刻
	int old_score1;			//前回のプレイヤー１のポイント
	int old_score2;			//前回のプレイヤー２のポイント

public:
	// コンストラクタ
	CutScene();
	// デストラクタ
	virtual ~CutScene();

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
	/// ファイルデータ読み込み処理
	/// </summary>
	void ReadData();

};