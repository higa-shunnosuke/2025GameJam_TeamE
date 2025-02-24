#include "SignManager.h"
#include "SignFactory.h"
#include "MashButtonSign.h"
#include "RandomSign.h"
#include "../player/ButtonMatch.h"
#include "../Utilitys/InputManager.h"

//再度フェイントを発動させるまでのターン
#define FEINTSIGN_COOLTIME	5
//リセットするまでの時間
#define RESET_TIME			3

SignManager::SignManager() :
	sign(nullptr),
	feint_count(0),
	count_time(0.f)
{

}

SignManager::~SignManager()
{

}

void SignManager::Initialize()
{
	//フェイント合図を出してい良い場合
	if (feint_count <= 0)
	{
		//合図1から5の中からランダムな合図を取得
		sign = SignFactory::GetSign(4);

		//フェイント合図のクールタイムを入れる
		if (sign->GetSignName() == "FeintSign")feint_count = FEINTSIGN_COOLTIME;
	}
	else
	{
		//ターン経過
		feint_count--;

		//合図1から4の中からランダムな合図を取得
		sign = SignFactory::GetSign(3);
	}

	count_time = 0.f;
}

void SignManager::Update(float delta_second)
{
	//合図の更新
	sign->Update(delta_second);

	//合図を出している場合
	if (sign->GetIsSign())
	{
		//計測
		if (sign->GetSignName() == "FeintSign")count_time += delta_second;

		//計測時間がリセットするまでの時間を超えた場合
		if (count_time > RESET_TIME)
		{
			//終了処理
			sign->Finalize();

			//初期化
			Initialize();
		}
	}
}

void SignManager::Finalize()
{
	//合図の終了処理
	SignFactory::Finalize();
}

void SignManager::Draw() const
{
	//合図の描画
	sign->Draw();
}

SignBase* SignManager::GetSignInstance() const
{
	return this->sign;
}

SignResult SignManager::GetSignResult()
{
	ButtonMatch* match = ButtonMatch::GetInstance();

	if (!sign->GetIsSign())
	{
		InputManager* input = InputManager::GetInstance();

		if (input->GetButtonDown(0, XINPUT_BUTTON_A) ||
			input->GetButtonDown(0, XINPUT_BUTTON_B) ||
			input->GetButtonDown(0, XINPUT_BUTTON_X) ||
			input->GetButtonDown(0, XINPUT_BUTTON_Y))
		{
			return SignResult::Player1_Faul;
		}
		if (input->GetButtonDown(1, XINPUT_BUTTON_A) ||
			input->GetButtonDown(1, XINPUT_BUTTON_B) ||
			input->GetButtonDown(1, XINPUT_BUTTON_X) ||
			input->GetButtonDown(1, XINPUT_BUTTON_Y))
		{
			return SignResult::Player2_Faul;
		}
	}
	else
	{
		if (sign->GetSignName() != "MashButtonSign" && sign->GetSignName() != "RandomSign")
		{
			if (match->GetPlayer1Result() == CORRECT)
			{
				return SignResult::Player1_Point;
			}
			else if (match->GetPlayer2Result() == CORRECT)
			{
				return SignResult::Player2_Point;
			}

			if (match->GetPlayer1Result() == INCORRECT)
			{
				return SignResult::Player1_Faul;
			}
			else if (match->GetPlayer2Result() == INCORRECT)
			{
				return SignResult::Player2_Faul;
			}
		}
		else
		{
			if (sign->GetSignName() == "MashButtonSign")
			{
				MashButtonSign* mbs_sign = dynamic_cast<MashButtonSign*>(sign);

				if (mbs_sign->IsMaximum(0))
				{
					return SignResult::Player1_Point;
				}
				else if (mbs_sign->IsMaximum(1))
				{
					return SignResult::Player2_Point;
				}
			}
			else if (sign->GetSignName() == "RandomSign")
			{
				RandomSign* rs_sign = dynamic_cast<RandomSign*>(sign);
				if (rs_sign->GetButton(0).empty())
				{
					return SignResult::Player1_Point;
				}
				else if (rs_sign->GetButton(1).empty())
				{
					return SignResult::Player2_Point;
				}
			}
		}
	}

	return SignResult::None;
}
