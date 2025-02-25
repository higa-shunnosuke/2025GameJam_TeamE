﻿#include "InGame.h"
#include "DxLib.h"
#include "../../Sign/SignManager.h"
#include "../../player/ButtonMatch.h"

#define FILE_NAME "Resources/datas/InGame_Data.csv"

// コンストラクタ
InGame::InGame() :
sign_manager(nullptr),
button_match(nullptr),
player1(),
player2(),
old_type()
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

	ResourceManager* rm = ResourceManager::GetInstance();
	bg_image = rm->GetImages("Resources/images/InGame_BackGround.png")[0];

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
}

// 更新処理
eSceneType InGame::Update(const float &delta_second)
{
	//入力管理クラスのポインタ
	InputManager* input = InputManager::GetInstance();

	//合図生成クラスの更新
	sign_manager->Update(delta_second);

	if (sign_manager->GetSignInstance()->GetIsSign())button_match->Activate(sign_manager->GetSignInstance());

	//ボタン判定クラスの更新
	button_match->ButtonMatchUpdate();

	//スタートボタンが押されたら
	if (input->GetButtonDown(0, XINPUT_BUTTON_START) == true ||
		input->GetKeyDown(KEY_INPUT_TAB))
	{
		//ポーズ画面へ
		return eSceneType::pause;
	}

	switch (sign_manager->GetSignResult())
	{
		player1.reaction_rate = button_match->GetPlayer1ReactionTime();
		player2.reaction_rate = button_match->GetPlayer1ReactionTime();

	case SignResult::Player1_Point:
		player1.point++;
		sign_manager->Initialize();
		button_match->ButtonReset();
		return eSceneType::cut;
		break;
	case SignResult::Player1_Foul:
		player1.foul++;
		sign_manager->Initialize();
		button_match->ButtonReset();
		break;
	case SignResult::Player2_Point:
		player2.point++;
		sign_manager->Initialize();
		button_match->ButtonReset();
		return eSceneType::cut;
		break;
	case SignResult::Player2_Foul:
		player2.foul++;
		sign_manager->Initialize();
		button_match->ButtonReset();
		break;
	default:
		break;
	}

	//どちらかのポイントが３ポイントになったら
	if (player1.point >= 3 || player2.point >= 3)
	{
		//リザルト画面へ
		return eSceneType::result;
	}

	//どちらかのファールが３ポイントになったら
	if (player1.foul >= 3 || player2.foul >= 2)
	{
		//リザルト画面へ
		return eSceneType::result;
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

// 描画処理
void InGame::Draw() const
{
	//背景描画
	DrawRotaGraph(320, 240, 1.0, 0.0, bg_image, TRUE);

	// フォントサイズ変更
	SetFontSize(32);

	//ポイント数の描画
	DrawRotaGraph(225, 15, 1, 0, player1.point_image, TRUE);
	DrawRotaGraph(425, 15, 1, 0, player2.point_image, TRUE, TRUE);

	//ファウル数の描画
	DrawRotaGraph(237, 50, 1, 0, player1.foul_image, TRUE);
	DrawRotaGraph(413, 50, 1, 0, player2.foul_image, TRUE, TRUE);

	//合図の描画
	sign_manager->Draw();
}

// 終了処理
void InGame::Finalize()
{
	//ファイル書き込み
	WriteData();

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
		throw("%sファイルを開けませんでした。", FILE_NAME);
	}
	else
	{
		//ファイルがなければ生成する
		fprintf_s(fp, "%d,%d\n", player1.point, player1.foul);
		fprintf_s(fp, "%d,%d\n", player2.point, player2.foul);

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