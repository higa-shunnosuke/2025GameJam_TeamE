#include "Title.h"

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

	//サウンドが入っていない場合
	if (sound.empty())
	{
		//サウンドを追加
		sound.push_back(rm->GetSounds("Resources/sounds/bgm/Title.wav"));
		sound.push_back(rm->GetSounds("Resources/sounds/se/Cursor.wav"));
		sound.push_back(rm->GetSounds("Resources/sounds/se/Select.wav"));
		sound.push_back(rm->GetSounds("Resources/sounds/se/Cancel.wav"));

		//音量を設定
		ChangeVolumeSoundMem(110, sound.at(0));
		ChangeVolumeSoundMem(190, sound.at(1));
	}

	//画像が入っていない場合
	if (image.empty())
	{
		//画像を追加
		image.push_back(rm->GetImages("Resources/images/Title/TitleName.png").at(0));
		image.push_back(rm->GetImages("Resources/images/Title/Start.png").at(0));
		image.push_back(rm->GetImages("Resources/images/Title/Help.png").at(0));
		image.push_back(rm->GetImages("Resources/images/Title/End.png").at(0));
		image.push_back(rm->GetImages("Resources/images/Title/Cursor.png").at(0));
	}

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
	//サウンドが再生されていない場合サウンドを再生する
	if (!CheckSoundMem(sound.at(0)))PlaySoundMem(sound.at(0), DX_PLAYTYPE_LOOP);

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
		//カーソル音を再生
		PlaySoundMem(sound.at(1), DX_PLAYTYPE_BACK);

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
		//カーソル音を再生
		PlaySoundMem(sound.at(1), DX_PLAYTYPE_BACK);

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
		//決定音を再生
		PlaySoundMem(sound.at(2), DX_PLAYTYPE_BACK);

		if (cursor == 0)
		{
			//BGMを止める
			StopSoundMem(sound.at(0));

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

	//タイトル名
	DrawGraph(100, 100, image.at(0), TRUE);

	//スタート
	DrawGraph(230, 240, image.at(1), TRUE);

	//ヘルプ
	DrawGraph(250, 290, image.at(2), TRUE);

	//エンド
	DrawGraph(250, 350, image.at(3), TRUE);

	//カーソル
	DrawGraph(170, 240 + (cursor * 55), image.at(4), TRUE);
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
		throw("Could not open file %s.", FILE_NAME);
	}
	else
	{
		//ファイルがなければ生成する
		fprintf_s(fp, "%d,%d,%d,%d,%f\n", 0, 0, 0, 0, 0.0f);
		fprintf_s(fp, "%d,%d,%d,%d,%f\n", 0, 0, 0, 0, 0.0f);

		//ファイルを閉じる
		fclose(fp);
	}
}