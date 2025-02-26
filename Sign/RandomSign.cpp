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

RandomSign::RandomSign() :
	alpha_blend_1(255.f),
	alpha_blend_2(255.f),
	is_alpha_blend_1(false),
	is_alpha_blend_2(false)
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

	alpha_blend_1 = 255.f;
	alpha_blend_2 = 255.f;

	is_alpha_blend_1 = false;
	is_alpha_blend_2 = false;
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
		if (!is_alpha_blend_1 && match->GetPlayer1Result() == CORRECT)
		{
			//ボタンの数が1より大きい場合
			if (button[0].size() > 1)
			{
				//透過させる
				is_alpha_blend_1 = true;
			}
			//ボタンの数が1より小さい場合
			else
			{
				//最初の要素を削除する
				button[0].erase(button[0].begin());
			}
		}
		
		//プレイヤー2の判定結果が正解の場合
		if (!is_alpha_blend_2 && match->GetPlayer2Result() == CORRECT)
		{
			//ボタンの数が1より大きい場合
			if (button[1].size() > 1)
			{
				//透過させる
				is_alpha_blend_2 = true;
			}
			//ボタンの数が1より小さい場合
			else
			{
				//最初の要素を削除する
				button[1].erase(button[1].begin());
			}
		}

		//プレイヤー1のボタンを透過させる場合
		if (is_alpha_blend_1)
		{
			//1フレーム当たりにかかった時間に800をかけた値で減算する
			//800は要調整
			alpha_blend_1 -= 800.f * delta_second;

			//透過されて見えなくなった場合
			if (alpha_blend_1 < 0.f)
			{
				//初期化する
				alpha_blend_1 = 255.f;
				is_alpha_blend_1 = false;

				//最初の要素を削除する
				button[0].erase(button[0].begin());
			}
		}
		
		//プレイヤー2のボタンを透過させる場合
		if (is_alpha_blend_2)
		{
			//1フレーム当たりにかかった時間に800をかけた値で減算する
			//800は要調整
			alpha_blend_2 -= 800.f * delta_second;

			//透過されて見えなくなった場合
			if (alpha_blend_2 < 0.f)
			{
				//初期化する
				alpha_blend_2 = 255.f;
				is_alpha_blend_2 = false;

				//最初の要素を削除する
				button[1].erase(button[1].begin());
			}
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
			const int sign_image_x = 60;
			//合図の座標y
			const int sign_image_y = 22;

			switch (button[0][i])
			{
			case XINPUT_BUTTON_A:
				//ここから透過する
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_blend_1	);
				//Aボタンの合図を描画
				DrawGraph(sign_image_x, sign_image_y - (i * 128), sign_image[RandomSignImage::A], TRUE);
				//ここから透過しない
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;

			case XINPUT_BUTTON_B:
				//ここから透過する
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_blend_1);
				//Bボタンの合図を描画
				DrawGraph(sign_image_x, sign_image_y - (i * 128), sign_image[RandomSignImage::B], TRUE);
				//ここから透過しない
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;

			case XINPUT_BUTTON_X:
				//ここから透過する
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_blend_1);
				//Xボタンの合図を描画
				DrawGraph(sign_image_x, sign_image_y - (i * 128), sign_image[RandomSignImage::X], TRUE);
				//ここから透過しない
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;

			case XINPUT_BUTTON_Y:
				//ここから透過する
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_blend_1);
				//Yボタンの合図を描画
				DrawGraph(sign_image_x, sign_image_y - (i * 128), sign_image[RandomSignImage::Y], TRUE);
				//ここから透過しない
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;

			default:
				break;
			}
		}
		//プレイヤー2のボタンの合図を描画
		for (int i = 0; i < button[1].size(); i++)
		{
			//合図の座標x
			const int sign_image_x = 500;
			//合図の座標y
			const int sign_image_y = 22;

			switch (button[1][i])
			{
			case XINPUT_BUTTON_A:
				//ここから透過する
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_blend_2);
				//Aボタンの合図を描画
				DrawGraph(sign_image_x, sign_image_y - (i * 128), sign_image[RandomSignImage::A], TRUE);
				//ここから透過しない
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;

			case XINPUT_BUTTON_B:
				//ここから透過する
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_blend_2);
				//Bボタンの合図を描画
				DrawGraph(sign_image_x, sign_image_y - (i * 128), sign_image[RandomSignImage::B], TRUE);
				//ここから透過しない
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;

			case XINPUT_BUTTON_X:
				//ここから透過する
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_blend_2);
				//Xボタンの合図を描画
				DrawGraph(sign_image_x, sign_image_y - (i * 128), sign_image[RandomSignImage::X], TRUE);
				//ここから透過しない
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;

			case XINPUT_BUTTON_Y:
				//ここから透過する
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_blend_2);
				//Yボタンの合図を描画
				DrawGraph(sign_image_x, sign_image_y - (i * 128), sign_image[RandomSignImage::Y], TRUE);
				//ここから透過しない
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
