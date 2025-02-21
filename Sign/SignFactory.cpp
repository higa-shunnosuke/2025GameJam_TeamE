#include "SignFactory.h"

#include <random>

SignFactory* SignFactory::instance = nullptr;

void SignFactory::Initialize()
{
	random_quick_press_sign = new RandomQuickPressSign();
}

void SignFactory::Finalize()
{
	instance->random_quick_press_sign->Finalize();

	delete instance->random_quick_press_sign;
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
	SignBase* ret = nullptr;

	switch (instance->GetRandRange(0, max_rand_val))
	{
		//ランダムな早押し
	case 0:
		instance->random_quick_press_sign->Initialize();
		ret = instance->random_quick_press_sign;
		break;

	default:
		break;
	}

	//合図を返す
	return ret;
}

uint64_t SignFactory::GetRandRange(uint64_t min_val, uint64_t max_val)
{
	//乱数生成器
	static std::mt19937_64 mt64(0);

	//[min_val, max_val] の一様分布整数 (int) の分布生成器
	std::uniform_int_distribution<uint64_t> get_rand_uni_int(min_val, max_val);

	//乱数を生成
	return get_rand_uni_int(mt64);
}
