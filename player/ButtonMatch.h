#pragma once
#include "../Sign/SignBase.h"
#include "../Utilitys/InputManager.h"
#include "../Utilitys/Singleton.h"
#include <DxLib.h>
#include <vector>
#include <cstring>

//判定結果
enum JudgeResult {
	UNJUDGED,   // 未判定
	CORRECT,    // 正解
	INCORRECT   // 不正解
};

class ButtonMatch : public Singleton<ButtonMatch>
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ButtonMatch();
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ButtonMatch();

	/// <summary>
	/// 合図が発動した際に外部から呼び出すと、
	/// signから合図を取得してプレイヤー2の状態を記録する
	/// 合図発動時刻も記録する
	/// </summary>
	/// <param name="sign">SignBaseクラスのオブジェクトのポインタ</param>
	void Activate(SignBase* sign);

	/// <summary>
	/// 合図発動後、毎フレーム呼び出して入力を更新し判定してください。
	/// </summary>
	/// <param name="delta_second">1フレーム当たりの時間</param>
	void ButtonMatchUpdate(const float& delta_second);

	/// <summary>
	/// プレイヤー1の判定結果
	/// </summary>
	/// <returns>UNJUDGED:未判定
	///  CORRECT:正解
	/// INCORRECT:不正解</returns>
	JudgeResult GetPlayer1Result() const;

	/// <summary>
	/// プレイヤー2の判定結果
	/// </summary>
	/// <returns>UNJUDGED:未判定
	///  CORRECT:正解
	/// INCORRECT:不正解</returns>
	JudgeResult GetPlayer2Result() const;

	/// <summary>
	/// プレイヤー1の反応時間取得
	/// </summary>
	/// <returns>プレイヤー1の反応時間</returns>
	float GetPlayer1ReactionTime() const;

	/// <summary>
	/// プレイヤー2の反応時間取得
	/// </summary>
	/// <returns>プレイヤー2の反応時間</returns>
	float GetPlayer2ReactionTime() const;

	/// <summary>
	/// 内部状態のリセット（新しいラウンド開始時に使ってください）
	/// </summary>
	void ButtonReset();

private:

	bool activated;       // 合図発動済みかどうか
	bool player1Judged;   // プレイヤー1はすでに判定済みか
	bool player2Judged;   // プレイヤー2はすでに判定済みか
	JudgeResult player1Result;	//プレイヤー1の判定受け渡し用の変数
	JudgeResult player2Result;	//プレイヤー2の判定受け渡し用の変数
	int player1ExpectedButton;  // 合図側から取得した、期待されるプレイヤー1のボタン
	int player2ExpectedButton;	// 合図側から取得した、期待されるプレイヤー2のボタン

	// 合図発動時刻（ミリ秒）を保持します。DxLibのGetNowCount() の戻り値を使用。
	unsigned int activationTime;
	// 各プレイヤーの反応時間
	float player1ReactionTime;
	float player2ReactionTime;

	bool isCorrectPlayer1;		//プレイヤー1は正解した？
	bool isCorrectPlayer2;		//プレイヤー2は正解した？

	/// <summary>
	/// 4つのボタン（A, B, X, Y）の入力かどうか判定します。
	/// </summary>
	/// <param name="button">判定対象のボタンのコード</param>
	/// <returns>True:4つのボタン（A, B, X, Y)のいずれか False:それ以外</returns>
	bool IsAllowedButton(int button) const;

public:
	bool GetIsCorrectPlayer1()const { return isCorrectPlayer1; }
	bool GetIsCorrectPlayer2()const { return isCorrectPlayer2; }

	/// <summary>
	/// プレイヤー1の正解フラグを設定
	/// </summary>
	/// <param name="flg">設定したいフラグ</param>
	void SetIsCorrectPlayer1(const bool flg)
	{
		isCorrectPlayer1 = flg;
	}

	/// <summary>
	/// プレイヤー2の正解フラグを設定
	/// </summary>
	/// <param name="flg">設定したいフラグ</param>
	void SetIsCorrectPlayer2(const bool flg)
	{
		isCorrectPlayer2 = flg;
	}
};

