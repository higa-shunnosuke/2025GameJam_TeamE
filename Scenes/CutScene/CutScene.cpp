#include "CutScene.h"
#include "DxLib.h"

#define FILE_NAME "Resources/datas/InGame_Data.csv"

// コンストラクタ
CutScene::CutScene() :
	player1(),
	player2(),
	old_type(),
	cut_scene(),
	now_t(),
	old_t(),
	t(),
	old_score1(),
	old_score2()
{

}

// デストラクタ
CutScene::~CutScene()
{

}

// 初期化処理
void CutScene::Initialize()
{
	// 親クラスの初期化処理を呼び出す
	__super::Initialize();

	//データの初期化
	ReadData();

	// ムービーファイルをロード
	switch (old_type)
	{
	case eSceneType::title:
		cut_scene = LoadGraph("Resources/CatScene/Start.mp4");
		break;
	case eSceneType::in_game:
		
		if (old_score1 < player1.point)
		{
			cut_scene = LoadGraph("Resources/CatScene/1P_WIN.mp4");
			old_score1 = player1.point;
		}
		if (old_score2 < player2.point)
		{
			cut_scene = LoadGraph("Resources/CatScene/2P_WIN.mp4");
			old_score2 = player1.point;
		}
		break;
	case eSceneType::pause:
		cut_scene = LoadGraph("Resources/CatScene/Start.mp4");
		break;
	}

	// ムービーを再生状態にする
	PlayMovieToGraph(cut_scene);

	//前回の時刻の初期化
	time(&old_t);
	t = 0;
}

// 更新処理
eSceneType CutScene::Update(const float& delta_second)
{
	//現在時刻と前回の時刻の更新
	time(&now_t);

	if (old_t < now_t)
	{
		t += 0.8f;
	}

	old_t = now_t;

	//３秒経過したら
	if (t > 2.4f)
	{
		//インゲーム画面へ
		return eSceneType::in_game;
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

// 描画処理
void CutScene::Draw() const
{
	//カットシーン再生
	// ムービー映像を画面いっぱいに描画します
	DrawExtendGraph(0, 0, 640, 480, cut_scene, FALSE);

	// フォントサイズ変更
	SetFontSize(32);

	DrawFormatString(10, 10, 0xffffff, "CutScene");

}

// 終了処理
void CutScene::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();

	// 読み込んだムービーファイルのグラフィックハンドルの削除
	DeleteGraph(cut_scene);
}

// 現在のシーンタイプ取得処理
const eSceneType CutScene::GetNowSceneType() const
{
	return eSceneType::cut;
}

// 前のシーンタイプ設定処理
void CutScene::SetOldSceneType(eSceneType old_type)
{
	this->old_type = old_type;
}

// ファイルデータ読み込み処理
void CutScene::ReadData()
{
	FILE* fp;

	//ファイルを開く
	fopen_s(&fp, FILE_NAME, "r");

	if (fp == NULL)
	{
		throw("%sファイルを開けませんでした。", FILE_NAME);
	}
	else
	{
		//ファイルがなければ生成する
		fscanf_s(fp, "%d,%d", &player1.point, &player1.foul);
		fscanf_s(fp, "%d,%d", &player2.point, &player2.foul);

		//ファイルを閉じる
		fclose(fp);
	}
}