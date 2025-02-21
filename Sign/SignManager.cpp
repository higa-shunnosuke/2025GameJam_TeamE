#include "SignManager.h"
#include "SignFactory.h"

//再度フェイントを発動させるまでのターン
#define FEINTSIGN_COOLTIME	5

SignManager::SignManager() :
	sign(nullptr),
	feint_count(0)
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
		sign = SignFactory::GetSign(3);

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
}

void SignManager::Update(float delta_second)
{
	//合図の更新
	sign->Update(delta_second);
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
