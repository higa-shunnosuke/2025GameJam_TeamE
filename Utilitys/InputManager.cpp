#include "InputManager.h"
#include "DxLib.h"

/// <summary>
/// 更新処理
/// </summary>
void InputManager::Update()
{
	// キー入力値の更新
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));
	GetHitKeyStateAll(now_key);

	// コントローラー入力値の更新
	XINPUT_STATE input[2] = {};

	for (int j = 0; j < 2; j++)
	{
		GetJoypadXInputState(DX_INPUT_PAD1 + j, &input[j]);
		for (int i = 0; i < D_BUTTON_MAX; i++)
		{
			old_button[j][i] = now_button[j][i];
			now_button[j][i] = static_cast<bool>(input[j].Buttons[i]);
		}

		trigger[j][0] = TriggerNormalization(input[j].LeftTrigger);
		trigger[j][1] = TriggerNormalization(input[j].RightTrigger);
		stick[j][0].x = StickNormalization(input[j].ThumbLX);
		stick[j][0].y = StickNormalization(input[j].ThumbLY);
		stick[j][1].x = StickNormalization(input[j].ThumbRX);
		stick[j][1].y = StickNormalization(input[j].ThumbRY);
	}
}

/// <summary>
/// キーボードのキーが押されているか確認する
/// </summary>
/// <param name="key_code">割り当てられたキー</param>
/// <returns>押されていたら、true</returns>
bool InputManager::GetKey(int key_code) const
{
	return CheckKeyCodeRange(key_code) && (now_key[key_code] == TRUE && old_key[key_code] == TRUE);
}

/// <summary>
/// キーボードのキーが押された瞬間か確認する
/// </summary>
/// <param name="key_code">割り当てられたキー</param>
/// <returns>押された瞬間なら、true</returns>
bool InputManager::GetKeyDown(int key_code) const
{
	return CheckKeyCodeRange(key_code) && (now_key[key_code] == TRUE && old_key[key_code] == FALSE);
}

/// <summary>
/// キーボードのキーが離された瞬間か確認する
/// </summary>
/// <param name="key_code">割り当てられたキー</param>
/// <returns>離された瞬間なら、true</returns>
bool InputManager::GetKeyUp(int key_code) const
{
	return CheckKeyCodeRange(key_code) && (now_key[key_code] == FALSE && old_key[key_code] == TRUE);
}

/// <summary>
/// コントローラーのボタンが押されているか確認する
/// </summary>
/// <param name="button">割り当てられたボタン</param>
/// <returns>押されていたら、true</returns>
bool InputManager::GetButton(int i, int button) const
{
	return CheckButtonRange(button) && (now_button[i][button] && old_button[i][button]);
}

/// <summary>
/// コントローラーのボタンが押された瞬間か確認する
/// </summary>
/// <param name="button">割り当てられたボタン</param>
/// <returns>押された瞬間なら、true</returns>
bool InputManager::GetButtonDown(int i, int button) const
{
	return CheckButtonRange(button) && (now_button[i][button] && !old_button[i][button]);
}

/// <summary>
/// コントローラーのボタンが離された瞬間か確認する
/// </summary>
/// <param name="button">割り当てられたボタン</param>
/// <returns>離された瞬間なら、true</returns>
bool InputManager::GetButtonUp(int i, int button) const
{
	return CheckButtonRange(button) && (!now_button[i][button] && old_button[i][button]);
}

/// <summary>
/// 左トリガー入力状態取得
/// </summary>
/// <returns>左トリガー入力状態(0.0f～1.0f)</returns>
float InputManager::GetLeftTrigger(int i) const
{
	return trigger[i][0];
}

/// <summary>
/// 右トリガー入力状態取得
/// </summary>
/// <returns>右トリガー入力状態(0.0f～1.0f)</returns>
float InputManager::GetRightTrigger(int i) const
{
	return trigger[i][1];
}

/// <summary>
/// 左スティック入力状態取得
/// </summary>
/// <returns>左スティック入力状態(-1.0f～1.0f)</returns>
Vector2D InputManager::GetLeftStick(int i) const
{
	return stick[i][0];
}

/// <summary>
/// 右スティック入力状態取得
/// </summary>
/// <returns>右スティック入力状態(-1.0f～1.0f)</returns>
Vector2D InputManager::GetRightStick(int i) const
{
	return stick[i][1];
}

/// <summary>
/// トリガー入力値の正規化
/// </summary>
/// <param name="value">トリガー入力値</param>
/// <returns>入力値を正規化した値</returns>
float InputManager::TriggerNormalization(unsigned char value)
{
	float result = 0.0f;

	result = (float)value / (float)UCHAR_MAX;

	return result;
}

/// <summary>
/// スティック入力値の正規化
/// </summary>
/// <param name="value">スティック入力値</param>
/// <returns>入力値を正規化した値</returns>
float InputManager::StickNormalization(short value)
{
	float result = 0.0f;

	if (value >= 0)
	{
		result = (float)value / (float)SHRT_MAX;
	}
	else
	{
		result = -((float)value / (float)SHRT_MIN);
	}

	return result;
}

/// <summary>
/// 割り当てキーコード範囲内チェック処理
/// </summary>
/// <param name="button">割り当てられたキーコード</param>
/// <returns>範囲内なら、true</returns>
bool InputManager::CheckKeyCodeRange(int key_code) const
{
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}

/// <summary>
/// 割り当てボタン範囲内チェック処理
/// </summary>
/// <param name="buttton">割り当てられたボタン</param>
/// <returns>範囲内なら、true</returns>
bool InputManager::CheckButtonRange(int button) const
{
	return (0 <= button && button < D_BUTTON_MAX);
}
