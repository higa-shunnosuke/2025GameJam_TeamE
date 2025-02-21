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
	__super::Initialize();

	sign_button.push_back(ChooseButton());
}

void RandomQuickPressSign::Update(float delta_second)
{
	__super::Update(delta_second);
}

void RandomQuickPressSign::Finalize()
{
	__super::Finalize();
}

void RandomQuickPressSign::Draw() const
{
	__super::Draw();

	if (is_sign)
	{
		switch (sign_button[0])
		{
		case XINPUT_BUTTON_A:
			//Aボタンの合図を描画
			DrawFormatString(0, 0, 0xffffff, "A");
			break;

		case XINPUT_BUTTON_B:
			//Bボタンの合図を描画
			DrawFormatString(0, 0, 0xffffff, "B");
			break;

		case XINPUT_BUTTON_X:
			//Xボタンの合図を描画
			DrawFormatString(0, 0, 0xffffff, "X");
			break;

		case XINPUT_BUTTON_Y:
			//Yボタンの合図を描画
			DrawFormatString(0, 0, 0xffffff, "Y");
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
