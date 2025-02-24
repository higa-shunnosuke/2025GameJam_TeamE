#include "MashButtonSign.h"
#include "../Utilitys/InputManager.h"
#include "../player/ButtonMatch.h"

MashButtonSign::MashButtonSign()
{

}

MashButtonSign::~MashButtonSign()
{

}

void MashButtonSign::Initialize()
{
	//親クラスの初期化処理
	__super::Initialize();

	//押すボタンをいれる
	sign_button.push_back(XINPUT_BUTTON_A);

	//空の場合
	if (score_bar.empty())
	{
		score_bar.push_back(0);
		score_bar.push_back(0);
	}
	//すでに値がある場合
	else
	{
		score_bar[0] = 0;
		score_bar[1] = 0;
	}
}

void MashButtonSign::Update(float delta_second)
{
	//親クラスの更新処理
	__super::Update(delta_second);

	//合図を出す場合
	if (is_sign)
	{
		//プレイヤーの入力インスタンスを取得
		ButtonMatch* match = ButtonMatch::GetInstance();

		//プレイヤー1の判定結果が正解の場合
		if (match->GetPlayer1Result() == CORRECT)
		{
			//スコアを加算する
			score_bar[0] += 10;
		}

		//プレイヤー2の判定結果が正解の場合
		if (match->GetPlayer2Result() == CORRECT)
		{
			//スコアを加算する
			score_bar[1] += 10;
		}
	}

	//100を超えないようにする
	if (score_bar[0] > 100)score_bar[0] = 100;
	if (score_bar[1] > 100)score_bar[1] = 100;
}

void MashButtonSign::Finalize()
{
	//親クラスの終了処理
	__super::Finalize();
}

void MashButtonSign::Draw() const
{
	//親クラスの描画処理
	__super::Draw();

	//合図を出す場合
	if (is_sign)
	{
		//説明
		SetFontSize(16);
		DrawFormatString(320, 120, 0xffffff, "MashButton！");
		SetFontSize(32);

		//Aボタンの合図を描画
		DrawFormatString(320, 140, 0xffffff, "A");

		//バーの枠
		DrawBox(20, 80, 80, 180, 0xffffff, FALSE);
		DrawBox(560, 80, 620, 180, 0xffffff, FALSE);

		//バー
		DrawBox(20, 180 - score_bar[0], 80, 180, 0xffffff, TRUE);
		DrawBox(560, 180 - score_bar[1], 620, 180, 0xffffff, TRUE);

	}
}

std::string MashButtonSign::GetSignName() const
{
	return std::string("MashButtonSign");
}

bool MashButtonSign::IsMaximum(const int element)
{
	//値が100以上の場合
	if (score_bar[element] >= 100)
	{
		//最大
		return true;
	}
	else
	{
		//最大ではない
		return false;
	}
}
