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
	//プレイヤーの入力インスタンスを取得
	ButtonMatch* match = ButtonMatch::GetInstance();

	//返す値
	SignResult ret = SignResult::None;

	//合図を出していない場合
	if (!sign->GetIsSign())
	{
		//入力のインスタンスを取得
		InputManager* input = InputManager::GetInstance();

		//プレイヤー1がA,B,X,Yのいずれかを押した場合
		if (input->GetButtonDown(0, XINPUT_BUTTON_A) ||
			input->GetButtonDown(0, XINPUT_BUTTON_B) ||
			input->GetButtonDown(0, XINPUT_BUTTON_X) ||
			input->GetButtonDown(0, XINPUT_BUTTON_Y))
		{
			//プレイヤー1にファールを返す
			ret = SignResult::Player1_Faul;
		}

		//プレイヤー2がA,B,X,Yのいずれかを押した場合
		if (input->GetButtonDown(1, XINPUT_BUTTON_A) ||
			input->GetButtonDown(1, XINPUT_BUTTON_B) ||
			input->GetButtonDown(1, XINPUT_BUTTON_X) ||
			input->GetButtonDown(1, XINPUT_BUTTON_Y))
		{
			//プレイヤー2にファールを返す
			ret = SignResult::Player2_Faul;
		}
	}
	//合図を出した場合
	else
	{
		//連打合図とランダム合図ではない場合
		if (sign->GetSignName() != "MashButtonSign" && sign->GetSignName() != "RandomSign")
		{
			//プレイヤー1の判定結果が正解の場合
			if (match->GetPlayer1Result() == CORRECT)
			{
				//プレイヤー1にポイントを返す
				ret = SignResult::Player1_Point;
			}

			//プレイヤー2の判定結果が正解の場合
			if (match->GetPlayer2Result() == CORRECT)
			{
				//プレイヤー2にポイントを返す
				ret = SignResult::Player2_Point;
			}

			//両者正解の場合
			if (match->GetPlayer1Result() == CORRECT &&
				match->GetPlayer2Result() == CORRECT)
			{
				//プレイヤー2のほうが反応速度が速い場合
				if (match->GetPlayer1ReactionTime() > match->GetPlayer2ReactionTime())
				{
					//プレイヤー2にポイントを返す
					ret = SignResult::Player2_Point;
				}
				//プレイヤー1のほうが反応速度が速い場合
				else if (match->GetPlayer1ReactionTime() < match->GetPlayer2ReactionTime())
				{
					//プレイヤー1にポイントを返す
					ret = SignResult::Player1_Point;

				}
				//反応速度が同じ場合
				else if (match->GetPlayer1ReactionTime() == match->GetPlayer2ReactionTime())
				{
					//引き分けを返す
					ret = SignResult::Draw;
				}
			}
		}
		//連打合図とランダム合図の場合
		else
		{
			//連打合図の場合
			if (sign->GetSignName() == "MashButtonSign")
			{
				//MashButtonSign型にキャスト
				MashButtonSign* mbs_sign = dynamic_cast<MashButtonSign*>(sign);

				//プレイヤー1のバーが最大の場合
				if (mbs_sign->IsMaximum(0))
				{
					//プレイヤー1にポイントを返す
					ret = SignResult::Player1_Point;
				}
				//プレイヤー2のバーが最大の場合
				else if (mbs_sign->IsMaximum(1))
				{
					//プレイヤー2のにポイントを返す
					ret = SignResult::Player2_Point;
				}
			}
			//ランダム合図の場合
			else if (sign->GetSignName() == "RandomSign")
			{
				//RandomSign型にキャスト
				RandomSign* rs_sign = dynamic_cast<RandomSign*>(sign);

				//プレイヤー1の押すボタンがない場合
				if (rs_sign->GetButton(0).empty())
				{
					//プレイヤー1にポイントを返す
					ret = SignResult::Player1_Point;
				}
				//プレイヤー2の押すボタンがない場合
				else if (rs_sign->GetButton(1).empty())
				{
					//プレイヤー2にポイントを返す
					ret = SignResult::Player2_Point;
				}
			}
		}
	}

	//値を返す
	return ret;
}
