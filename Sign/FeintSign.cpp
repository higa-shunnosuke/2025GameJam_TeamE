#include "FeintSign.h"
#include "../Utilitys/ResourceManager.h"

enum FeintSignImage
{
	Feint = 0,
	Quick
};

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

	//合図の画像が入っていない場合
	if (sign_image.empty())
	{
		//リソースマネージャーのインスタンスを取得
		ResourceManager* r_m = ResourceManager::GetInstance();
		//分割読み込みする画像ではないので配列の0番目だけを取得
		sign_image.push_back(r_m->GetImages("Resources/images/Sign/Sign_Feint.png").at(0));
		sign_image.push_back(r_m->GetImages("Resources/images/sign/Quick_Press.png").at(0));
	}
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
		DrawGraph(210, 90, sign_image[FeintSignImage::Quick], TRUE);

		//合図の座標x
		const int sign_image_x = 275;
		//合図の座標y
		const int sign_image_y = 160;

		//合図を描画
		DrawGraph(sign_image_x, sign_image_y, sign_image[FeintSignImage::Feint], TRUE);
	}
}

std::string FeintSign::GetSignName() const
{
	return std::string("FeintSign");
}
