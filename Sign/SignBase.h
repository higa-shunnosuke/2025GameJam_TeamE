#pragma once

#include <random>
#include <vector>

//最大待ち時間
#define MAX_RANDOM_TIME 15

/// <summary>
/// 合図のベースクラス
/// </summary>
class SignBase
{
protected:
	std::vector<int>sign_image;		//合図の画像
	std::vector<int>sign_button;	//押すボタン

	int waiting_time;				//待ち時間

	float count_time;				//計測時間

	bool is_sign;					//合図を出す？

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SignBase() :
		waiting_time(0),
		count_time(0.f),
		is_sign(false)
	{

	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SignBase()
	{

	}

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize()
	{
		waiting_time = GetRandRange(1, MAX_RANDOM_TIME);
	}

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void Update(float delta_second)
	{
		//計測
		count_time += delta_second;

		//計測時間が待ち時間を超えた場合
		if (count_time > waiting_time)
		{
			//合図を出す
			is_sign = true;
		}

	}

	/// <summary>
	/// 終了時処理
	/// </summary>
	virtual void Finalize()
	{

	}

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() const
	{

	}

protected:
	/// <summary>
	/// 指定した範囲のランダムな数字を取得
	/// </summary>
	/// <param name="min_val">最小値</param>
	/// <param name="max_val">最大値</param>
	/// <returns>ランダムな値</returns>
	int GetRandRange(int min_val, int max_val) 
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

public:
	//押すボタンを取得
	std::vector<int>GetSignButton()const { return sign_button; }

	//待ち時間を取得
	int GetWaitingTime()const { return waiting_time; }

};