﻿#include "Pause.h"
#include "DxLib.h"

#define COLOR_ON 0xff0000	//赤
#define COLOR_OFF 0xffffff	//白

#define FILE_NAME "Resources/datas/InGame_Data.csv"

// コンストラクタ
Pause::Pause() :
	cursor(),
	start_color(),
	restart_color(),
	quit_color(),
	is_restart(false)
{

}

// デストラクタ
Pause::~Pause()
{

}

// 初期化処理
void Pause::Initialize()
{
	// 親クラスの初期化処理を呼び出す
	__super::Initialize();

	ResourceManager* rm = ResourceManager::GetInstance();
	bg_image = rm->GetImages("Resources/images/InGame_BackGround.png")[0];

	//サウンドが入っていない場合
	if (sound.empty())
	{
		//サウンドを追加
		sound.push_back(rm->GetSounds("Resources/sounds/se/Cursor.wav"));
		sound.push_back(rm->GetSounds("Resources/sounds/se/Select.wav"));

		//音量を設定
		ChangeVolumeSoundMem(190, sound.at(0));
	}

	//画像が入っていない場合
	if (image.empty())
	{
		//画像を追加
		image.push_back(rm->GetImages("Resources/images/Pause/Start.png").at(0));
		image.push_back(rm->GetImages("Resources/images/Pause/Re_Start.png").at(0));
		image.push_back(rm->GetImages("Resources/images/Pause/End.png").at(0));
		image.push_back(rm->GetImages("Resources/images/Title/Cursor.png").at(0));
		image.push_back(rm->GetImages("Resources/images/Pause/Pause.png").at(0));
	}

	//ボタンの色を初期化
	start_color = COLOR_OFF;
	restart_color = COLOR_OFF;
	quit_color = COLOR_OFF;
}

// 更新処理
eSceneType Pause::Update(const float &delta_second)
{
	//入力管理クラスのポインタ
	InputManager* input = InputManager::GetInstance();

	if (cursor == 0)
	{
		//ポーズ解除ボタンの色を変更
		start_color = COLOR_ON;
		restart_color = COLOR_OFF;
		quit_color = COLOR_OFF;
	}
	else if (cursor == 1)
	{
		//リスタートボタンの色を変更
		start_color = COLOR_OFF;
		restart_color = COLOR_ON;
		quit_color = COLOR_OFF;
	}
	else
	{
		//ゲーム終了ボタンの色を変更
		start_color = COLOR_OFF;
		restart_color = COLOR_OFF;
		quit_color = COLOR_ON;
	}

	//カーソルを下へ動かす
	if (input->GetButtonDown(0, XINPUT_BUTTON_DPAD_DOWN) == true ||
		input->GetKeyDown(KEY_INPUT_DOWN))
	{
		//カーソル音を再生
		PlaySoundMem(sound.at(0), DX_PLAYTYPE_BACK);

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
		PlaySoundMem(sound.at(0), DX_PLAYTYPE_BACK);

		if (cursor < 1)
		{
			cursor = 2;
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
		PlaySoundMem(sound.at(1), DX_PLAYTYPE_BACK);

		if (cursor == 0)
		{
			//ポーズ解除
			return eSceneType::in_game;
		}
		else if (cursor == 1)
		{
			is_restart = true;

			//インゲームのデータを初期化
			DetaInitialize();

			//リスタート
			return eSceneType::re_start;
		}
		else
		{
			//タイトル画面へ
			return eSceneType::title;
		}
	}
	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

// 描画処理
void Pause::Draw() const
{
	//背景描画
	DrawRotaGraph(320, 240, 1.0, 0.0, bg_image, TRUE);

	//スタート
	DrawGraph(230, 240, image.at(0), TRUE);

	//リスタート
	DrawGraph(235, 290, image.at(1), TRUE);

	//エンド
	DrawGraph(233, 340, image.at(2), TRUE);

	//カーソル
	DrawGraph(170, 240 + (cursor * 50), image.at(3), TRUE);

	//ポーズ
	DrawGraph(220, 100, image.at(4), TRUE);

}

// 終了処理
void Pause::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

// 現在のシーンタイプ取得処理
const eSceneType Pause::GetNowSceneType() const
{
	return eSceneType::pause;
}

//ファイルデータの初期化
void Pause::DetaInitialize()
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
		fprintf_s(fp, "%d,%d\n", 0, 0);
		fprintf_s(fp, "%d,%d\n", 0, 0);

		//ファイルを閉じる
		fclose(fp);
	}
}