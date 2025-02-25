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
		sign_image.push_back(r_m->GetImages("Resources/images/sign/sign_a.png").at(0));
		sign_image.push_back(r_m->GetImages("Resources/images/sign/sign_b.png").at(0));
		sign_image.push_back(r_m->GetImages("Resources/images/sign/sign_x.png").at(0));
		sign_image.push_back(r_m->GetImages("Resources/images/sign/sign_y.png").at(0));
		sign_image.push_back(r_m->GetImages("Resources/images/sign/quick_press.png").at(0));
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
		DrawGraph(210, 100, sign_image[RandomQuickPressSignImage::Quick], TRUE);

		switch (sign_button[0])
		{
		case XINPUT_BUTTON_A:
			//Aボタンの合図を描画
			DrawGraph(255, 140, sign_image[RandomQuickPressSignImage::A], TRUE);
			break;

		case XINPUT_BUTTON_B:
			//Bボタンの合図を描画
			DrawGraph(255, 140, sign_image[RandomQuickPressSignImage::B], TRUE);
			break;

		case XINPUT_BUTTON_X:
			//Xボタンの合図を描画
			DrawGraph(255, 140, sign_image[RandomQuickPressSignImage::X], TRUE);
			break;

		case XINPUT_BUTTON_Y:
			//Yボタンの合図を描画
			DrawGraph(255, 140, sign_image[RandomQuickPressSignImage::Y], TRUE);
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
