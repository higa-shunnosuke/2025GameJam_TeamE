#include "RandomSign.h"
#include "../Utilitys/InputManager.h"
#include "../Utilitys/ResourceManager.h"
#include "../player/ButtonMatch.h"

//押させるボタンの最大数
#define MAX_RANDOM_BUTTON	4

/// <summary>
/// ランダム合図の画像番号用
/// </summary>
enum RandomSignImage
{
	A = 0,
	B,
	X,
	Y,
	Quick
};

RandomSign::RandomSign()
{

}

RandomSign::~RandomSign()
{

}

void RandomSign::Initialize()
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

	//空にしておく
	sign_button.clear();

	for (int i = 0; i < MAX_RANDOM_BUTTON; i++)
	{
		//押すボタンをいれる
		sign_button.push_back(ChooseButton());
	}

	//空の場合
	if (button.empty())
	{
		button.push_back(sign_button);
		button.push_back(sign_button);
	}
	//すでに値がある場合
	else
	{
		button[0] = sign_button;
		button[1] = sign_button;
	}
}

void RandomSign::Update(float delta_second)
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
			//最初の要素を削除する
			button[0].erase(button[0].begin());
		}

		//プレイヤー2の判定結果が正解の場合
		if (match->GetPlayer2Result() == CORRECT)
		{
			//最初の要素を削除する
			button[1].erase(button[1].begin());
		}
	}
}

void RandomSign::Finalize()
{
	//親クラスの終了処理
	__super::Finalize();
}

void RandomSign::Draw() const
{
	//親クラスの描画処理
	__super::Draw();

	//合図を出す場合
	if (is_sign)
	{
		//説明
		DrawGraph(210, 90, sign_image[RandomSignImage::Quick], TRUE);


		//プレイヤー1のボタンの合図を描画
		for (int i = 0; i < button[0].size(); i++)
		{		
			//合図の座標x
			const int sign_image_x = 80;
			//合図の座標y
			const int sign_image_y = 132;

			switch (button[0][i])
			{
			case XINPUT_BUTTON_A:
				//Aボタンの合図を描画
				DrawGraph(sign_image_x, sign_image_y - (i * 128), sign_image[RandomSignImage::A], TRUE);
				break;

			case XINPUT_BUTTON_B:
				//Bボタンの合図を描画
				DrawGraph(sign_image_x, sign_image_y - (i * 128), sign_image[RandomSignImage::B], TRUE);
				break;

			case XINPUT_BUTTON_X:
				//Xボタンの合図を描画
				DrawGraph(sign_image_x, sign_image_y - (i * 128), sign_image[RandomSignImage::X], TRUE);
				break;

			case XINPUT_BUTTON_Y:
				//Yボタンの合図を描画
				DrawGraph(sign_image_x, sign_image_y - (i * 128), sign_image[RandomSignImage::Y], TRUE);
				break;

			default:
				break;
			}
		}
		//プレイヤー2のボタンの合図を描画
		for (int i = 0; i < button[1].size(); i++)
		{
			//合図の座標x
			const int sign_image_x = 480;
			//合図の座標y
			const int sign_image_y = 132;

			switch (button[1][i])
			{
			case XINPUT_BUTTON_A:
				//Aボタンの合図を描画
				DrawGraph(sign_image_x, sign_image_y - (i * 128), sign_image[RandomSignImage::A], TRUE);
				break;

			case XINPUT_BUTTON_B:
				//Bボタンの合図を描画
				DrawGraph(sign_image_x, sign_image_y - (i * 128), sign_image[RandomSignImage::B], TRUE);
				break;

			case XINPUT_BUTTON_X:
				//Xボタンの合図を描画
				DrawGraph(sign_image_x, sign_image_y - (i * 128), sign_image[RandomSignImage::X], TRUE);
				break;

			case XINPUT_BUTTON_Y:
				//Yボタンの合図を描画
				DrawGraph(sign_image_x, sign_image_y - (i * 128), sign_image[RandomSignImage::Y], TRUE);
				break;

			default:
				break;
			}
		}
	}
}

std::string RandomSign::GetSignName() const
{
	return std::string("RandomSign");
}
