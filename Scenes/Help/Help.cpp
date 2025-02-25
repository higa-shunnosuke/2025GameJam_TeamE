#include "Help.h"
#include "DxLib.h"



// コンストラクタ
Help::Help():
	cursor(),
	image1(),
	image2()
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
	image1 = rm->GetImages("Resources/images/Rule explanation1.png")[0];
	image2 = rm->GetImages("Resources/images/Rule explanation2.png")[0];
	bg_image = image1;
	cursor = 0;
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
		//タイトル画面へ
		return eSceneType::title;
	}

	//カーソルを右へ動かす
	if (input->GetButtonDown(0, XINPUT_BUTTON_DPAD_RIGHT) == true ||
		input->GetKeyDown(KEY_INPUT_RIGHT))
	{
		if (cursor == 0)
		{
			cursor = 1;
			bg_image = image2;
		}
	}

	//カーソルを左へ動かす
	if (input->GetButtonDown(0, XINPUT_BUTTON_DPAD_LEFT) == true ||
		input->GetKeyDown(KEY_INPUT_LEFT))
	{
		if (cursor == 1)
		{
			cursor = 0;
			bg_image = image1;
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

	// フォントサイズ変更
	SetFontSize(16);

	// フォントサイズ変更
	SetFontSize(32);
	DrawFormatString(10, 10, 0xffffff, "Help");
	DrawFormatString(10, 450, 0xffffff, "True = A,False = B");
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