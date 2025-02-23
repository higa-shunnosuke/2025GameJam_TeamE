#include "FeintSign.h"

FeintSign::FeintSign()
{

}

FeintSign::~FeintSign()
{

}

void FeintSign::Initialize()
{
	//親クラスの初期化処理
	__super::Initialize();
}

void FeintSign::Update(float delta_second)
{
	//親クラスの更新処理
	__super::Update(delta_second);
}

void FeintSign::Finalize()
{
	//親クラスの終了処理
	__super::Finalize();
}

void FeintSign::Draw() const
{
	//親クラスの描画処理
	__super::Draw();

	//合図を出す場合
	if (is_sign)
	{
		//説明
		SetFontSize(16);
		DrawFormatString(320, 120, 0xffffff, "Feint!");
		SetFontSize(32);

		//合図を描画
		DrawFormatString(320, 140, 0xffffff, "?");

	}
}

std::string FeintSign::GetSignName() const
{
	return std::string("FeintSign");
}
