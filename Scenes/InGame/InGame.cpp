#include "InGame.h"
#include "DxLib.h"
#include "../../Sign/SignManager.h"

#define FILE_NAME "Resources/datas/InGame_Data.csv"

// コンストラクタ
InGame::InGame() :
	sign_manager(nullptr),
	player1(),
	player2()
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

	sign_manager = new SignManager();
	sign_manager->Initialize();

	//データの初期化
	ReadData();
}

// 更新処理
eSceneType InGame::Update(const float &delta_second)
{
	//入力管理クラスのポインタ
	InputManager* input = InputManager::GetInstance();

	sign_manager->Update(delta_second);

	//スタートボタンが押されたら
	if (input->GetButtonDown(XINPUT_BUTTON_START) == true ||
		input->GetKeyDown(KEY_INPUT_TAB))
	{
		//ポーズ画面へ
		return eSceneType::pause;
	}

	//決定
	if (input->GetButtonDown(XINPUT_BUTTON_A) == true ||
		input->GetKeyDown(KEY_INPUT_RETURN))
	{
		player1.point++;
	}

	//どちらかのポイントが３ポイントになったら
	if (player1.point >= 3 || player2.point >= 3)
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