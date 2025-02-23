#include "SignManager.h"
#include "SignFactory.h"

//再度フェイントを発動させるまでのターン
#define FEINTSIGN_COOLTIME	5
//リセットするまでの時間
#define RESET_TIME			3

SignManager::SignManager() :
	sign(nullptr),
	feint_count(0),
	count_time(0.f)
{

}

SignManager::~SignManager()
{

}

void SignManager::Initialize()
{
	//フェイント合図を出してい良い場合
	if (feint_count <= 0)
	{
		//合図1から5の中からランダムな合図を取得
		sign = SignFactory::GetSign(4);

		//フェイント合図のクールタイムを入れる
		if (sign->GetSignName() == "FeintSign")feint_count = FEINTSIGN_COOLTIME;
	}
	else
	{
		//ターン経過
		feint_count--;

		//合図1から4の中からランダムな合図を取得
		sign = SignFactory::GetSign(3);
	}

	count_time = 0.f;
}

void SignManager::Update(float delta_second)
{
	//合図の更新
	sign->Update(delta_second);

	//合図を出している場合
	if (sign->GetIsSign())
	{
		//計測
		//count_time += delta_second;

		//計測時間がリセットするまでの時間を超えた場合
		if (count_time > RESET_TIME)
		{
			//終了処理
			sign->Finalize();

			//初期化
			Initialize();
		}
	}
}

void SignManager::Finalize()
{
	//合図の終了処理
	SignFactory::Finalize();
}

void SignManager::Draw() const
{
	//合図の描画
	sign->Draw();
}

SignBase* SignManager::GetSignInstance() const
{
	return this->sign;
}
