#include "QuickPressSign.h"

QuickPressSign::QuickPressSign()
{

}

QuickPressSign::~QuickPressSign()
{

}

void QuickPressSign::Initialize()
{
	//親クラスの初期化処理
	__super::Initialize();
}

void QuickPressSign::Update(float delta_second)
{
	//親クラスの更新処理
	__super::Update(delta_second);
}

void QuickPressSign::Finalize()
{
	//親クラスの終了処理
	__super::Finalize();
}

void QuickPressSign::Draw() const
{
	//親クラスの描画処理
	__super::Draw();

	//合図を出す場合
	if (is_sign)
	{
		//説明
		SetFontSize(16);
		DrawFormatString(320, 120, 0xffffff, "QuickPress！");
		SetFontSize(32);

		//合図を描画
		DrawFormatString(320, 140, 0xffffff, "!");

	}
}

std::string QuickPressSign::GetSignName() const
{
	return std::string("QuickPressSign");
}
