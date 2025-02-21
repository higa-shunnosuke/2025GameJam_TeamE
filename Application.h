﻿#pragma once

#include "DxLib.h"

#include "Utilitys/Singleton.h"
#include "Utilitys/ProjectConfig.h"
#include "Utilitys/InputManager.h"
#include "Scenes/SceneManager.h"

class Application : public Singleton<Application>
{
private:
	// グローバル変数定義
	LONGLONG old_time;		// 前回計測値
	LONGLONG now_time;		// 現在計測値
	float delta_second;		// １フレームあたりの時間

public:
	bool WakeUp()
	{
		// ウィンドウモードで起動する
		ChangeWindowMode(TRUE);

		// ウィンドウサイズの設定
		SetGraphMode(D_WIN_MAX_X, D_WIN_MAX_Y, D_COLOR_BIT);

		// ウィンドウタイトルの設定
		SetWindowText("GameJam_2025_TeamE");

		// 垂直同期を行わない
		SetWaitVSyncFlag(FALSE);

		// Log.txtファイルの生成制御（Debugモードのみ生成する）
#if _DEBUG
		SetOutApplicationLogValidFlag(TRUE);
#else
		SetOutApplicationLogValidFlag(FALSE);
#endif // _DEBUG

		// Dxライブラリの初期化
		if (DxLib_Init() == D_FAILURE)
		{
			throw std::string("Dxライブラリの初期化に失敗しました！\n");
		}

		// 描画先を表画面に反映する
		SetDrawScreen(DX_SCREEN_BACK);

		// シーンマネージャーを生成する
		SceneManager* manager = SceneManager::GetInstance();

		// 初期化処理
		manager->Initialize();

		// 非アクティブ状態でも動作させる
		SetAlwaysRunFlag(TRUE);

		return true;
	}

	void Run()
	{
		// シーンマネージャーを生成する
		SceneManager* manager = SceneManager::GetInstance();

		// 入力情報を取得する
		InputManager* input = InputManager::GetInstance();

		// メインループ
		while (ProcessMessage() == D_SUCCESS)
		{
			// 入力情報の更新
			input->Update();

			// フレームレートの制御
			UpdateDeltaTime();

			// 実行処理
			manager->Update(delta_second);

			// ゲームを終了するか確認する
			if (input->GetButtonDown(XINPUT_BUTTON_BACK) == true ||
				input->GetKeyDown(KEY_INPUT_ESCAPE) == true)
			{
				break;
			}
		}
	}

	void Shutdown()
	{
		// シーンマネージャーを生成する
		SceneManager* manager = SceneManager::GetInstance();

		// 終了時処理
		manager->Finalize();

		// Dxライブラリの使用を終了する
		DxLib_End();
	}

private:
	void UpdateDeltaTime()
	{
		// 現在時間の取得（μ秒）
		now_time = GetNowHiPerformanceCount();

		// 開始時間から現在時間までに経過した時間を計算する（μ秒）
		// 分解能をμ秒→秒に変換する
		delta_second = (float)(now_time - old_time) * 1.0e-6f;

		// 計測開始時間を更新する
		old_time = now_time;

		// ディスプレイのリフレッシュレートを取得する
		float refresh_rate = (float)GetRefreshRate();

		// １フレーム当たりの時間が1/リフレッシュレート秒を超えたら、整える
		if (delta_second > (1.0f / refresh_rate))
		{
			delta_second = (1.0f / refresh_rate);
		}
	}
};