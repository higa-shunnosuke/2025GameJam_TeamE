#include "SignFactory.h"
#include "RandomQuickPressSign.h"
#include "MashButtonSign.h"
#include "QuickPressSign.h"
#include "RandomSign.h"
#include "FeintSign.h"

#include <random>

SignFactory* SignFactory::instance = nullptr;

void SignFactory::Initialize()
{
	random_quick_press_sign = new RandomQuickPressSign();
	mash_button_sign = new MashButtonSign();
	quick_Press_sign = new QuickPressSign();
	random_sign = new RandomSign();
	feint_sign = new FeintSign();
}

void SignFactory::Finalize()
{
	instance->random_quick_press_sign->Finalize();
	instance->mash_button_sign->Finalize();
	instance->quick_Press_sign->Finalize();
	instance->random_sign->Finalize();
	instance->feint_sign->Finalize();

	delete instance->random_quick_press_sign;
	delete instance->mash_button_sign;
	delete instance->quick_Press_sign;
	delete instance->random_sign;
	delete instance->feint_sign;
	delete instance;

	instance = nullptr;
}

SignBase* SignFactory::GetSign(const int max_rand_val)
{
	//インスタンスが生成されていない場合
	if (!instance)
	{
		//インスタンスを生成する
		instance = new SignFactory();
		instance->Initialize();
	}

	//返す値
	SignBase* ret = new SignBase();

	switch (ret->GetRandRange(0, max_rand_val))
	{
		//ランダムな早押し
	case 0:
		delete ret;
		instance->random_quick_press_sign->Initialize();
		ret = instance->random_quick_press_sign;
		break;

		//連打
	case 1:
		delete ret;
		instance->mash_button_sign->Initialize();
		ret = instance->mash_button_sign;
		break;

		//早押し
	case 2:
		delete ret;
		instance->quick_Press_sign->Initialize();
		ret = instance->quick_Press_sign;
		break;

		//ランダム
	case 3:
		delete ret;
		instance->random_sign->Initialize();
		ret = instance->random_sign;
		break;

		//フェイント
	case 4:
		delete ret;
		instance->feint_sign->Initialize();
		ret = instance->feint_sign;
		break;

	default:
		break;
	}

	//合図を返す
	return ret;
}
