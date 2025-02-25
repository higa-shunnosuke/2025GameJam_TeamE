#include "Title.h"
#include "DxLib.h"

#define COLOR_ON 0xff0000	//赤
#define COLOR_OFF 0xffffff	//白

#define FILE_NAME "Resources/datas/InGame_Data.csv"

// コンストラクタ
Title::Title():
	cursor(),
	start_color(),
	help_color(),
	quit_color()
{

}

// デストラクタ
Title::~Title()
{

}

// 初期化処理
void Title::Initialize()
{
	// 親クラスの初期化処理を呼び出す
	__super::Initialize();

	ResourceManager* rm = ResourceManager::GetInstance();
	bg_image = rm->GetImages("Resources/images/BackGround.png")[0];

	//ボタンの色を初期化
	start_color = COLOR_OFF;
	help_color = COLOR_OFF;
	quit_color = COLOR_OFF;

	//データの初期化
	DetaInitialize();
}

// 更新処理
eSceneType Title::Update(const float &delta_second)
{
	//入力管理クラスのポインタ
	InputManager* input = InputManager::GetInstance();

	if (cursor == 0)
	{
		//スタートボタンの色を変更
		start_color = COLOR_ON;
		help_color = COLOR_OFF;
		quit_color = COLOR_OFF;
	}
	else if (cursor == 1)
	{
		//ヘルプボタンの色を変更
		start_color = COLOR_OFF;
		help_color = COLOR_ON;
		quit_color = COLOR_OFF;
	}
	else
	{
		//ゲーム終了ボタンの色を変更
		start_color = COLOR_OFF;
		help_color = COLOR_OFF;
		quit_color = COLOR_ON;
	}

	//カーソルを下へ動かす
	if (input->GetButtonDown(0,XINPUT_BUTTON_DPAD_DOWN) == true ||
		input->GetKeyDown(KEY_INPUT_DOWN))
	{
		if (cursor > 1)
		{
			cursor = 0;
		}
		else
		{
			cursor++;
		}
	}

	//カーソルを上に動かす
	if (input->GetButtonDown(0, XINPUT_BUTTON_DPAD_UP) == true ||
		input->GetKeyDown(KEY_INPUT_UP))
	{
		if (cursor < 0)
		{
			cursor = 1;
		}
		else
		{
			cursor--;
		}
	}

	//決定
	if (input->GetButtonDown(0, XINPUT_BUTTON_A) == true ||
		input->GetKeyDown(KEY_INPUT_RETURN))
	{
		if (cursor == 0)
		{
			//インゲーム画面へ
			return eSceneType::cut;
		}
		else if (cursor == 1)
		{
			//ヘルプ画面へ
			return eSceneType::help;
		}
		else
		{
			//エンド画面へ
			return eSceneType::end;
		}
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

// 描画処理
void Title::Draw() const
{
	//背景描画
	DrawRotaGraph(320, 240, 1.0, 0.0, bg_image, TRUE);

	// フォントサイズ変更
	SetFontSize(32);

	DrawFormatString(10, 10, 0xffffff, "Title");
	DrawFormatString(10, 40, 0xffffff, "cursor:%d",cursor);
	DrawFormatString(280, 240, start_color, "Start");
	DrawFormatString(280, 270, help_color, "Help");
	DrawFormatString(280, 300, quit_color, "Quit");
	DrawFormatString(10, 450, 0xffffff, "True = A,False = B");

}

// 終了処理
void Title::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

// 現在のシーンタイプ取得処理
const eSceneType Title::GetNowSceneType() const
{
	return eSceneType::title;
}

//ファイルデータの初期化
void Title::DetaInitialize()
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
		fprintf_s(fp, "%d,%d,%d,%d\n", 0, 0, 0, 0);
		fprintf_s(fp, "%d,%d,%d,%d\n", 0, 0, 0, 0);

		//ファイルを閉じる
		fclose(fp);
	}
}