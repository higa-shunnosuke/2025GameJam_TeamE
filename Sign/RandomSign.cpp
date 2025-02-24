#include "RandomSign.h"
#include "../Utilitys/InputManager.h"
#include "../player/ButtonMatch.h"

#define DEBUG

//押させるボタンの最大数
#define MAX_RANDOM_BUTTON	4

RandomSign::RandomSign()
{

}

RandomSign::~RandomSign()
{

}

void RandomSign::Initialize()
{
	//親クラスの初期化処理
	__super::Initialize();

	//空にしておく
	sign_button.clear();

	for (int i = 0; i < MAX_RANDOM_BUTTON; i++)
	{
		//押すボタンをいれる
		sign_button.push_back(ChooseButton());
	}

	//空の場合
	if (button.empty())
	{
		button.push_back(sign_button);
		button.push_back(sign_button);
	}
	//すでに値がある場合
	else
	{
		button[0] = sign_button;
		button[1] = sign_button;
	}
}

void RandomSign::Update(float delta_second)
{
	//親クラスの更新処理
	__super::Update(delta_second);

	if (is_sign)
	{
		ButtonMatch* match = ButtonMatch::GetInstance();

		if (match->GetPlayer1Result() == CORRECT)
		{
			button[0].erase(button[0].begin());
		}

		if (match->GetPlayer2Result() == CORRECT)
		{
			button[1].erase(button[1].begin());
		}
	}


#ifdef DEBUG
	InputManager* input = InputManager::GetInstance();
	if (input->GetKeyDown(KEY_INPUT_F))
	{
		button[0].erase(button[0].begin());
	}

	if (input->GetKeyDown(KEY_INPUT_J))
	{
		button[1].erase(button[1].begin());
	}

#endif // DEBUG

}

void RandomSign::Finalize()
{
	//親クラスの終了処理
	__super::Finalize();
}

void RandomSign::Draw() const
{
	//親クラスの描画処理
	__super::Draw();

	//合図を出す場合
	if (is_sign)
	{
		//説明
		SetFontSize(16);
		DrawFormatString(320, 120, 0xffffff, "Press in Order！");
		SetFontSize(32);

		//プレイヤー1のボタンの合図を描画
		for (int i = 0; i < button[0].size(); i++)
		{
			switch (button[0][i])
			{
			case XINPUT_BUTTON_A:
				//Aボタンの合図を描画
				DrawFormatString(120, 260 - (i * 40), 0xffffff, "A");
				break;

			case XINPUT_BUTTON_B:
				//Bボタンの合図を描画
				DrawFormatString(120, 260 - (i * 40), 0xffffff, "B");
				break;

			case XINPUT_BUTTON_X:
				//Xボタンの合図を描画
				DrawFormatString(120, 260 - (i * 40), 0xffffff, "X");
				break;

			case XINPUT_BUTTON_Y:
				//Yボタンの合図を描画
				DrawFormatString(120, 260 - (i * 40), 0xffffff, "Y");
				break;

			default:
				break;
			}
		}
		//プレイヤー2のボタンの合図を描画
		for (int i = 0; i < button[1].size(); i++)
		{
			switch (button[1][i])
			{
			case XINPUT_BUTTON_A:
				//Aボタンの合図を描画
				DrawFormatString(420, 260 - (i * 40), 0xffffff, "A");
				break;

			case XINPUT_BUTTON_B:
				//Bボタンの合図を描画
				DrawFormatString(420, 260 - (i * 40), 0xffffff, "B");
				break;

			case XINPUT_BUTTON_X:
				//Xボタンの合図を描画
				DrawFormatString(420, 260 - (i * 40), 0xffffff, "X");
				break;

			case XINPUT_BUTTON_Y:
				//Yボタンの合図を描画
				DrawFormatString(420, 260 - (i * 40), 0xffffff, "Y");
				break;

			default:
				break;
			}
		}
	}
}

std::string RandomSign::GetSignName() const
{
	return std::string("RandomSign");
}
