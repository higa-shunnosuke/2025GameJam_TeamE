#include "InGame.h"
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
		player1.faul++;
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
		player2.faul++;
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
	if (player1.faul >= 3 || player2.faul >= 2)
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

	DrawFormatString(10, 10, 0xffffff, "InGame");
	DrawFormatString(10, 40, 0xffffff, "point:%d",player1.point);
	DrawFormatString(10, 70, 0xffffff, "faul:%d",player1.faul);
	DrawFormatString(500, 40, 0xffffff, "point:%d",player2.point);
	DrawFormatString(500, 70, 0xffffff, "faul:%d",player2.faul);

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
		fprintf_s(fp, "%d,%d\n", player1.point, player1.faul);
		fprintf_s(fp, "%d,%d\n", player2.point, player2.faul);

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
		fscanf_s(fp, "%d,%d", &player1.point, &player1.faul);
		fscanf_s(fp, "%d,%d", &player2.point, &player2.faul);

		//ファイルを閉じる
		fclose(fp);
	}
}