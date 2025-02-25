#include "CutScene.h"
#include "DxLib.h"

#define FILE_NAME "Resources/datas/InGame_Data.csv"

// コンストラクタ
CutScene::CutScene() :
	player1(),
	player2(),
	old_type(),
	cut_scene(),
	time(),
	old_player1(),
	old_player2()
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

	//リソースマネージャーのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();

	//サウンドが入っていない場合
	if (sound.empty())
	{
		//サウンドを追加
		sound.push_back(rm->GetSounds("Resources/sounds/bgm/InGame.wav"));

		//音量を設定
		ChangeVolumeSoundMem(140, sound.at(0));
	}

	//データの初期化
	ReadData();

	// ムービーファイルをロード
	switch (old_type)
	{
	case eSceneType::title:
		cut_scene = LoadGraph("Resources/CatScene/Start.mp4");
		break;
	case eSceneType::in_game:
		//表示するカットシーンを設定する
		if (old_player1.point < player1.point)
		{
			cut_scene = LoadGraph("Resources/CatScene/1P_WIN.mp4");
			old_player1.point = player1.point;
		}
		else if (old_player2.point < player2.point)
		{
			cut_scene = LoadGraph("Resources/CatScene/2P_WIN.mp4");
			old_player2.point = player1.point;
		}
		else if (old_player1.foul < player1.foul)
		{
			cut_scene = LoadGraph("Resources/CatScene/1P_FOUL.mp4");
			old_player1.foul = player1.foul;
		}
		else if (old_player2.foul < player2.foul)
		{
			cut_scene = LoadGraph("Resources/CatScene/2P_FOUL.mp4");
			old_player2.foul = player2.foul;
		}
		break;
	case eSceneType::pause:
		cut_scene = LoadGraph("Resources/CatScene/Start.mp4");
		break;
	}

	// ムービーを再生状態にする
	PlayMovieToGraph(cut_scene);

	//数字に変換するための文字を格納する変数
	std::string str;
	//プレイヤー1のポイント数を文字に変換
	str = std::to_string(player1.point > 2 ? 2 : player1.point);
	player1.point_image = rm->GetImages("Resources/images/UI/Point/Point_" + str + ".png").at(0);
	//プレイヤー2のポイント数を文字に変換
	str = std::to_string(player2.point > 2 ? 2 : player2.point);
	player2.point_image = rm->GetImages("Resources/images/UI/Point/Point_" + str + ".png").at(0);

	//プレイヤー1のファウル数を文字に変換
	str = std::to_string(player1.foul > 1 ? 1 : player1.foul);
	player1.foul_image = rm->GetImages("Resources/images/UI/Foul/Foul_" + str + ".png").at(0);
	//プレイヤー2のファウル数を文字に変換
	str = std::to_string(player2.foul > 1 ? 1 : player2.foul);;
	player2.foul_image = rm->GetImages("Resources/images/UI/Foul/Foul_" + str + ".png").at(0);

	//画像が入っていない場合
	if (ui_image.empty())
	{
		ui_image.push_back(rm->GetImages("Resources/images/UI/Point/Point.png").at(0));
		ui_image.push_back(rm->GetImages("Resources/images/UI/Foul/Foul.png").at(0));
	}

	time = 0;
}

// 更新処理
eSceneType CutScene::Update(const float& delta_second)
{
	//サウンドが再生されていない場合サウンドを再生する
	if (!CheckSoundMem(sound.at(0)))PlaySoundMem(sound.at(0), DX_PLAYTYPE_LOOP);

	time += delta_second;

	//３秒経過したら
	if (time > 3.0f)
	{
		//どちらかのポイントが３ポイントになったら
		if (player1.point >= 3 || player2.point >= 3)
		{
			//BGMを止める
			StopSoundMem(sound.at(0));

			//リザルト画面へ
			return eSceneType::result;
		}
		else
		{
			//インゲーム画面へ
			return eSceneType::in_game;
		}
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

	//ポイント数の描画
	DrawGraph(272, 0, ui_image.at(0), TRUE);
	DrawRotaGraph(225, 15, 1, 0, player1.point_image, TRUE, TRUE);
	DrawRotaGraph(425, 15, 1, 0, player2.point_image, TRUE);

	//ファウル数の描画
	DrawGraph(275, 40, ui_image.at(1), TRUE);
	DrawRotaGraph(237, 50, 1, 0, player1.foul_image, TRUE, TRUE);
	DrawRotaGraph(413, 50, 1, 0, player2.foul_image, TRUE);
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
		fscanf_s(fp, "%d,%d,%d,%d", &old_player1.point, &old_player1.foul, &player1.point, &player1.foul);
		fscanf_s(fp, "%d,%d,%d,%d", &old_player2.point, &old_player2.foul, &player2.point, &player2.foul);

		//ファイルを閉じる
		fclose(fp);
	}
}