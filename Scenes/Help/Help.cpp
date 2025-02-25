#include "Help.h"
#include "DxLib.h"



// コンストラクタ
Help::Help() :
	cursor(),
	image1(),
	image2(),
	image3(),
	image4(),
	image5(),
	image6()
{

}

// デストラクタ
Help::~Help()
{

}

// 初期化処理
void Help::Initialize()
{
	// 親クラスの初期化処理を呼び出す
	__super::Initialize();

	ResourceManager* rm = ResourceManager::GetInstance();
	image1 = rm->GetImages("Resources/images/Help/Rule explanation1.png")[0];
	image2 = rm->GetImages("Resources/images/Help/Rule explanation2.png")[0];
	image3 = rm->GetImages("Resources/images/Help/Rule explanation3.png")[0];
	image4 = rm->GetImages("Resources/images/Help/Rule_Back.png")[0];
	image5 = rm->GetImages("Resources/images/Help/Cursor_Right.png")[0];
	image6 = rm->GetImages("Resources/images/Help/Cursor_Left.png")[0];
	bg_image = image1;

	cursor = 0;	
	
	//サウンドが入っていない場合
	if (sound.empty())
	{
		//サウンドを追加
		sound.push_back(rm->GetSounds("Resources/sounds/se/Cancel.wav"));
		sound.push_back(rm->GetSounds("Resources/sounds/se/Cursor.wav"));

		//音量を設定
		ChangeVolumeSoundMem(200, sound.at(0));
	}

}

// 更新処理
eSceneType Help::Update(const float &delta_second)
{
	//入力管理クラスのポインタ
	InputManager* input = InputManager::GetInstance();

	//戻る
	if (input->GetButtonDown(0, XINPUT_BUTTON_B) == true ||
		input->GetKeyDown(KEY_INPUT_BACK))
	{
		//戻る音を再生
		PlaySoundMem(sound.at(0), DX_PLAYTYPE_BACK);

		//タイトル画面へ
		return eSceneType::title;
	}

	//カーソルを右へ動かす
	if (input->GetButtonDown(0, XINPUT_BUTTON_DPAD_RIGHT) == true ||
		input->GetKeyDown(KEY_INPUT_RIGHT))
	{
		if (cursor == 0)
		{
			//カーソル音を再生
			PlaySoundMem(sound.at(1), DX_PLAYTYPE_BACK);

			cursor = 1;
			bg_image = image2;
		}
		else if (cursor == 1)
		{
			//カーソル音を再生
			PlaySoundMem(sound.at(1), DX_PLAYTYPE_BACK);

			cursor = 2;
			bg_image = image3;
		}
	}

	//カーソルを左へ動かす
	if (input->GetButtonDown(0, XINPUT_BUTTON_DPAD_LEFT) == true ||
		input->GetKeyDown(KEY_INPUT_LEFT))
	{
		if (cursor == 1)
		{
			//カーソル音を再生
			PlaySoundMem(sound.at(1), DX_PLAYTYPE_BACK);

			cursor = 0;
			bg_image = image1;
		}
		else if (cursor == 2)
		{
			//カーソル音を再生
			PlaySoundMem(sound.at(1), DX_PLAYTYPE_BACK);

			cursor = 1;
			bg_image = image2;
		}
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

// 描画処理
void Help::Draw() const
{
	//背景描画
	DrawRotaGraph(320, 240, 1.0, 0.0, bg_image, TRUE);

	//Bで戻るを描画
	DrawGraph(550, 450, image4, TRUE);

	switch (cursor)
	{
	case 0:
		//→を描画
		DrawGraph(598, -10, image5, TRUE);
		break;

	case 1:
		//→を描画
		DrawGraph(598, -10, image5, TRUE);
		//←を描画
		DrawGraph(0, -10, image6, TRUE);
		break;

	case 2:
		//←を描画
		DrawGraph(0, -10, image6, TRUE);
		break;

	default:
		break;
	}
}

// 終了処理
void Help::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

// 現在のシーンタイプ取得処理
const eSceneType Help::GetNowSceneType() const
{
	return eSceneType::help;
}