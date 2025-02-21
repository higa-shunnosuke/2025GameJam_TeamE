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

int SignFactory::GetRandRange(int min_val, int max_val)
{
	//ハードウェア乱数生成器を使用してシードを生成
	std::random_device rand_device;

	//MersenneTwisterアルゴリズムを使った乱数生成
	std::mt19937 generator(rand_device());

	//min_valとmax_valの範囲で均等分布
	std::uniform_int_distribution<> distribution(min_val, max_val);

	//ランダムな値を生成して返す	
	return distribution(generator);
}
