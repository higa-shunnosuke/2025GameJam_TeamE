#include "Result.h"
#include "DxLib.h"

#define FILE_NAME "Resources/datas/InGame_Data.csv"

// コンストラクタ
Result::Result():
	player1(),
	player2()
{

}

// デストラクタ
Result::~Result()
{

}

// 初期化処理
void Result::Initialize()
{
	// 親クラスの初期化処理を呼び出す
	__super::Initialize();

	ResourceManager* rm = ResourceManager::GetInstance();
	bg_image = rm->GetImages("Resources/images/InGame_BackGround.png")[0];

	ReadData();
}

// 更新処理
eSceneType Result::Update(const float &delta_second)
{
	//入力管理クラスのポインタ
	InputManager* input = InputManager::GetInstance();

	//決定
	if (input->GetButtonDown(0, XINPUT_BUTTON_A) == true ||
		input->GetKeyDown(KEY_INPUT_RETURN))
	{
		//タイトル画面へ
		return eSceneType::title;
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

// 描画処理
void Result::Draw() const
{
	//背景描画
	DrawRotaGraph(320, 240, 1.0, 0.0, bg_image, TRUE);

	// フォントサイズ変更
	SetFontSize(32);

	DrawFormatString(10, 10, 0xffffff, "Result");

	//プレイヤー１の勝利条件
	if (player1.point > player2.point || player1.foul < player2.foul)
	{
		DrawFormatString(250, 240, 0xffffff, "Player1 Win");
	}
	//プレイヤー２の勝利条件
	else if (player1.point < player2.point || player1.foul > player2.foul)
	{
		DrawFormatString(250, 240, 0xffffff, "Player2 Win");
	}
}

// 終了処理
void Result::Finalize()
{
	DetaInitialize();

	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

// 現在のシーンタイプ取得処理
const eSceneType Result::GetNowSceneType() const
{
	return eSceneType::result;
}

// ファイルデータ読み込み処理
void Result::ReadData()
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

//ファイルデータの初期化
void Result::DetaInitialize()
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
		fprintf_s(fp, "%d,%d\n", 0, 0);
		fprintf_s(fp, "%d,%d\n", 0, 0);

		//ファイルを閉じる
		fclose(fp);
	}
}