#include "RandomQuickPressSign.h"
#include "DxLib.h"

RandomQuickPressSign::RandomQuickPressSign()
{

}

RandomQuickPressSign::~RandomQuickPressSign()
{
}

void RandomQuickPressSign::Initialize()
{
	//親クラスの初期化処理
	__super::Initialize();

	//押すボタンをいれる
	sign_button.push_back(ChooseButton());
}

void RandomQuickPressSign::Update(float delta_second)
{
	//親クラスの更新処理
	__super::Update(delta_second);
}

void RandomQuickPressSign::Finalize()
{
	//親クラスの終了処理
	__super::Finalize();

	//配列を空にする
	sign_button.clear();
}

void RandomQuickPressSign::Draw() const
{
	//親クラスの描画処理
	__super::Draw();

	//合図を出す場合
	if (is_sign)
	{
		switch (sign_button[0])
		{
		case XINPUT_BUTTON_A:
			//Aボタンの合図を描画
			DrawFormatString(320, 140, 0xffffff, "A");
			break;

		case XINPUT_BUTTON_B:
			//Bボタンの合図を描画
			DrawFormatString(320, 140, 0xffffff, "B");
			break;

		case XINPUT_BUTTON_X:
			//Xボタンの合図を描画
			DrawFormatString(320, 140, 0xffffff, "X");
			break;

		case XINPUT_BUTTON_Y:
			//Yボタンの合図を描画
			DrawFormatString(320, 140, 0xffffff, "Y");
			break;

		default:
			break;
		}
	}
}

int RandomQuickPressSign::ChooseButton()
{
	switch (GetRandRange(0, 3))
	{
	case 0:
		//Aボタンを押させる
		return XINPUT_BUTTON_A;
		break;

	case 1:
		//Bボタンを押させる
		return XINPUT_BUTTON_B;
		break;

	case 2:
		//Xボタンを押させる
		return XINPUT_BUTTON_X;
		break;

	case 3:
		//Yボタンを押させる
		return XINPUT_BUTTON_Y;
		break;

	default :
		break;
	}

	return NULL;
}
