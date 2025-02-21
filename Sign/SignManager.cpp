#include "SignManager.h"
#include "SignFactory.h"

SignManager::SignManager() :
	sign(nullptr),
	fake_count(0)
{

}

SignManager::~SignManager()
{

}

void SignManager::Initialize()
{
	if (fake_count >= 0)
	{
		//合図1から5の中からランダムな合図を取得
		sign = SignFactory::GetSign(0);
	}
	else
	{
		//合図1から4の中からランダムな合図を取得
		sign = SignFactory::GetSign(0);
	}
}

void SignManager::Update(float delta_second)
{
	sign->Update(delta_second);
}

void SignManager::Finalize()
{
	//合図の終了処理
	SignFactory::Finalize();
}

void SignManager::Draw() const
{
	sign->Draw();
}
