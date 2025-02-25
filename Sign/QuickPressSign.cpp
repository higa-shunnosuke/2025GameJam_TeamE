#include "QuickPressSign.h"
#include "../Utilitys/ResourceManager.h"

/// <summary>
/// 早押し合図の画像番号用
/// </summary>
enum QuickPressSignImage
{
	Quick = 0,
	QuickPress
};

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

	//合図の画像が入っていない場合
	if (sign_image.empty())
	{
		//リソースマネージャーのインスタンスを取得
		ResourceManager* r_m = ResourceManager::GetInstance();
		//分割読み込みする画像ではないので配列の0番目だけを取得
		sign_image.push_back(r_m->GetImages("Resources/images/sign/Sign_Quick.png").at(0));
		sign_image.push_back(r_m->GetImages("Resources/images/sign/Quick_Press.png").at(0));
	}
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
		DrawGraph(210, 90, sign_image[QuickPressSignImage::QuickPress], TRUE);

		//合図の座標x
		const int sign_image_x = 275;
		//合図の座標y
		const int sign_image_y = 160;

		//合図を描画
		DrawGraph(sign_image_x, sign_image_y, sign_image[QuickPressSignImage::Quick], TRUE);

	}
}

std::string QuickPressSign::GetSignName() const
{
	return std::string("QuickPressSign");
}
