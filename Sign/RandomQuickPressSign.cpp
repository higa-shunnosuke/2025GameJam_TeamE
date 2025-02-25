#include "RandomQuickPressSign.h"
#include "../Utilitys/ResourceManager.h"

/// <summary>
/// ランダム早押し合図の画像番号用
/// </summary>
enum RandomQuickPressSignImage
{
	A = 0,
	B,
	X,
	Y,
	Quick
};

RandomQuickPressSign::RandomQuickPressSign()
{

}

RandomQuickPressSign::~RandomQuickPressSign()
{
}

void RandomQuickPressSign::Initialize()
{
	//親クラスの初期化処理
	__super::Initialize();

	//合図の画像が入っていない場合
	if (sign_image.empty())
	{
		//リソースマネージャーのインスタンスを取得
		ResourceManager* r_m = ResourceManager::GetInstance();
		//分割読み込みする画像ではないので配列の0番目だけを取得
		sign_image.push_back(r_m->GetImages("Resources/images/Sign/Sign_A.png").at(0));
		sign_image.push_back(r_m->GetImages("Resources/images/Sign/Sign_B.png").at(0));
		sign_image.push_back(r_m->GetImages("Resources/images/Sign/Sign_X.png").at(0));
		sign_image.push_back(r_m->GetImages("Resources/images/Sign/Sign_Y.png").at(0));
		sign_image.push_back(r_m->GetImages("Resources/images/Sign/Quick_Press.png").at(0));
	}

	//押すボタンをいれる
	sign_button.push_back(ChooseButton());
}

void RandomQuickPressSign::Update(float delta_second)
{
	//親クラスの更新処理
	__super::Update(delta_second);
}

void RandomQuickPressSign::Finalize()
{
	//親クラスの終了処理
	__super::Finalize();
}

void RandomQuickPressSign::Draw() const
{
	//親クラスの描画処理
	__super::Draw();

	//合図を出す場合
	if (is_sign)
	{
		//説明
		DrawGraph(210, 90, sign_image[RandomQuickPressSignImage::Quick], TRUE);

		//合図の座標x
		const int sign_image_x = 275;
		//合図の座標y
		const int sign_image_y = 160;

		switch (sign_button[0])
		{
		case XINPUT_BUTTON_A:
			//Aボタンの合図を描画
			DrawGraph(sign_image_x, sign_image_y, sign_image[RandomQuickPressSignImage::A], TRUE);
			break;

		case XINPUT_BUTTON_B:
			//Bボタンの合図を描画
			DrawGraph(sign_image_x, sign_image_y, sign_image[RandomQuickPressSignImage::B], TRUE);
			break;

		case XINPUT_BUTTON_X:
			//Xボタンの合図を描画
			DrawGraph(sign_image_x, sign_image_y, sign_image[RandomQuickPressSignImage::X], TRUE);
			break;

		case XINPUT_BUTTON_Y:
			//Yボタンの合図を描画
			DrawGraph(sign_image_x, sign_image_y, sign_image[RandomQuickPressSignImage::Y], TRUE);
			break;

		default:
			break;
		}
	}
}

std::string RandomQuickPressSign::GetSignName() const
{
	return std::string("RandomQuickPressSign");
}
