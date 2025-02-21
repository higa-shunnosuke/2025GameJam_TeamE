#include "MashButtonSign.h"

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
}

void MashButtonSign::Update(float delta_second)
{
	//親クラスの更新処理
	__super::Update(delta_second);
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

	}
}

std::string MashButtonSign::GetSignName() const
{
	return std::string("MashButton");
}
