#include "InGame.h"
#include "DxLib.h"
#include "../../Sign/SignManager.h"
#include "../../player/ButtonMatch.h"

#define FILE_NAME "Resources/datas/InGame_Data.csv"
#define RANKING_NAME "Resources/datas/Reaction_Data.csv"

// コンストラクタ
InGame::InGame() :
sign_manager(nullptr),
button_match(nullptr),
player1(),
player2(),
cut_scene(),
time(),
type(),
round_count(),
is_cut(nullptr)
{

}

// デストラクタ
InGame::~InGame()
{

}

// 初期化処理
void InGame::Initialize()
{
	// 親クラスの初期化処理を呼び出す
	__super::Initialize();

	//リソースマネージャーのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	bg_image = rm->GetImages("Resources/images/InGame_BackGround.png")[0];

	//サウンドが入っていない場合
	if (sound.empty())
	{
		sound.push_back(rm->GetSounds("Resources/sounds/bgm/InGame.wav"));
	}

	//合図生成クラスの初期化
	sign_manager = new SignManager();
	sign_manager->Initialize();

	//ボタン判定クラスの初期化
	button_match = ButtonMatch::GetInstance();
	button_match->ButtonReset();

	//データの初期化
	ReadData();

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

	//スタートのカットシーンを作成
	CreateCutScene(CutType::Start);

	//ラウンド回数を初期化
	round_count = 0;
}

// 更新処理
eSceneType InGame::Update(const float &delta_second)
{
	//サウンドが再生されていない場合サウンドを再生する
	if (!CheckSoundMem(sound.at(0)))PlaySoundMem(sound.at(0), DX_PLAYTYPE_LOOP);

	if (cut_scene != 0)
	{
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
			//どちらかのファールが2ポイントになったら
			else if (player1.foul >= 2 || player2.foul >= 2)
			{
				//BGMを止める
				StopSoundMem(sound.at(0));

				//リザルト画面へ
				return eSceneType::result;
			}
			else
			{
				//再生時間を初期化
				time = 0;
				//カットシーンを削除
				cut_scene = 0;
				// 読み込んだムービーファイルのグラフィックハンドルの削除
				DeleteGraph(cut_scene);

				//初期化する
				button_match->ButtonReset();
				sign_manager->Initialize();

				//リソースマネージャーのインスタンスを取得
				ResourceManager* rm = ResourceManager::GetInstance();
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

				is_cut = false;
				sign_manager->GetSignInstance()->SetIsStart(true);
			}
		}
	}
	else
	{
		//入力管理クラスのポインタ
		InputManager* input = InputManager::GetInstance();

		//スタートボタンが押されたら
		if (input->GetButtonDown(0, XINPUT_BUTTON_START) == true ||
			input->GetKeyDown(KEY_INPUT_TAB))
		{
			//ポーズ画面へ
			return eSceneType::pause;
		}
	}

		player1.reaction_rate[round_count] = floor(button_match->GetPlayer1ReactionTime() * 10) / 10;
		player2.reaction_rate[round_count] = floor(button_match->GetPlayer2ReactionTime() * 10) / 10;
	//合図生成クラスの更新
	sign_manager->Update(delta_second);

	//合図がでた場合
	if (sign_manager->GetSignInstance()->GetIsSign())button_match->Activate(sign_manager->GetSignInstance());

	//ボタン判定クラスの更新
	button_match->ButtonMatchUpdate(delta_second);

	player1.reaction_rate = floor(button_match->GetPlayer1ReactionTime() * 10) / 10;
	player2.reaction_rate = floor(button_match->GetPlayer2ReactionTime() * 10) / 10;

	//合図の結果を確認する
	switch (sign_manager->GetSignResult(is_cut))
	{
		//プレイヤー1にポイントの場合
	case SignResult::Player1_Point:
		if (!is_cut)
		{
			player1.point++;
			CreateCutScene(CutType::Win_Player1);
			is_cut = true;
		}
		break;
		//プレイヤー1にファウルの場合
	case SignResult::Player1_Foul:
		if (!is_cut)
		{
			player1.foul++;
			CreateCutScene(CutType::Foul_Player1);
			is_cut = true;
		}
		break;
		//プレイヤー2にポイントの場合
	case SignResult::Player2_Point:
		if (!is_cut)
		{
			player2.point++;
			CreateCutScene(CutType::Win_Player2);
			is_cut = true;
		}
		break;
		//プレイヤー2にファウルの場合
	case SignResult::Player2_Foul:
		if (!is_cut)
		{
			player2.foul++;
			CreateCutScene(CutType::Foul_Player2);
			is_cut = true;
		}
		break;
		//引き分けの場合
	case SignResult::Draw:
		if (!is_cut)
		{
			CreateCutScene(CutType::TieGame);
		default:
			break;
		}

		//ファイル書き込み
		WriteData();

		if (sign_manager->GetSignResult() != SignResult::None)
		{
			sign_manager->Initialize();
			button_match->ButtonReset();
		}

		//どちらかのファールが2ポイントになったら
		if (player1.foul >= 2 || player2.foul >= 2)
		{
			//BGMを止める
			StopSoundMem(sound.at(0));

			//リザルト画面へ
			return eSceneType::result;
			is_cut = true;
		}
		break;
	default:
		break;
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

// 描画処理
void InGame::Draw() const
{
	//背景描画
	DrawRotaGraph(320, 240, 1.0, 0.0, bg_image, TRUE);

	//合図の描画
	sign_manager->Draw();

	if (cut_scene != 0)
	{
		// ムービー映像を画面いっぱいに描画します
		DrawExtendGraph(0, 0, 640, 480, cut_scene, FALSE);
	}

	// フォントサイズ変更
	SetFontSize(32);

	//ポイント数の描画
	DrawGraph(272, 0, ui_image.at(0), TRUE);
	DrawRotaGraph(225, 15, 1, 0, player1.point_image, TRUE, TRUE);
	DrawRotaGraph(425, 15, 1, 0, player2.point_image, TRUE);

	//ファウル数の描画
	DrawGraph(275, 40, ui_image.at(1), TRUE);
	DrawRotaGraph(237, 50, 1, 0, player1.foul_image, TRUE, TRUE);
	DrawRotaGraph(413, 50, 1, 0, player2.foul_image, TRUE);

	//反応速度の描画
	DrawFormatString(0, 0, 0xffffff, "1P:%f", player1.reaction_rate);
	DrawFormatString(0, 30, 0xffffff, "2P:%f", player2.reaction_rate);
}

// カットシーン生成処理
void InGame::CreateCutScene(CutType type)
{
	// ムービーファイルをロード
	switch (type)
	{
	case Start:
		cut_scene = LoadGraph("Resources/CatScene/Start.mp4");
		break;
	case Win_Player1:
		cut_scene = LoadGraph("Resources/CatScene/1P_WIN.mp4");
		break;
	case Win_Player2:
		cut_scene = LoadGraph("Resources/CatScene/2P_WIN.mp4");
		break;
	case Foul_Player1:
		cut_scene = LoadGraph("Resources/CatScene/1P_FOUL.mp4");
		break;
	case Foul_Player2:
		cut_scene = LoadGraph("Resources/CatScene/2P_FOUL.mp4");
		break;
	case TieGame:
		cut_scene = LoadGraph("Resources/CatScene/DRAW.mp4");
		break;
	}
	// ムービーを再生状態にする
	PlayMovieToGraph(cut_scene);
}

// 終了処理
void InGame::Finalize()
{
	//ランキングデータ書き込み
	WriteRanking();

	// 親クラスの終了時処理を呼び出す
	__super::Finalize();

	sign_manager->Finalize();
}

// 現在のシーンタイプ取得処理
const eSceneType InGame::GetNowSceneType() const
{
	return eSceneType::in_game;
}

// ファイルデータ書き込み処理
void InGame::WriteData()
{
	FILE* fp;

	//ファイルを開く
	fopen_s(&fp, FILE_NAME, "w");

	if (fp == NULL)
	{
		throw("Could not open file %s.", FILE_NAME);
	}
	else
	{
		//データを書き込む
		fprintf_s(fp, "%d,%d\n",  player1.point, player1.foul);
		fprintf_s(fp, "%d,%d\n",  player2.point, player2.foul);

		//ファイルを閉じる
		fclose(fp);
	}
}

// ファイルデータ読み込み処理
void InGame::ReadData()
{
	FILE* fp;

	//ファイルを開く
	fopen_s(&fp, FILE_NAME, "r");

	if (fp == NULL)
	{
		throw("Could not open file %s.", FILE_NAME);
	}
	else
	{
		//データを読み込む
		fscanf_s(fp, "%d,%d",  &player1.point, &player1.foul);
		fscanf_s(fp, "%d,%d",  &player2.point, &player2.foul);

		//ファイルを閉じる
		fclose(fp);
	}
}

// ランキングデータ書き込み処理
void InGame::WriteRanking()
{
	FILE* fp;

	//ファイルを開く
	fopen_s(&fp, FILE_NAME, "w");

	if (fp == NULL)
	{
		throw("Could not open file %s.", FILE_NAME);
	}
	else
	{
		//データを書き込む
		for (int i = 0; i < 5; i++)
		{
			fprintf_s(fp, "%f,%f\n", player1.reaction_rate[i], player2.reaction_rate[i]);
		}

		//ファイルを閉じる
		fclose(fp);
	}
}