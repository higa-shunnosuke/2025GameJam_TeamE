﻿#include "SceneManager.h"
#include "SceneFactory.h"
#include "DxLib.h"

#include "../Utilitys/InputManager.h"

// コンストラクタ
SceneManager::SceneManager() :
	current_scene(nullptr)
{

}

// デストラク
SceneManager::~SceneManager()
{
	// 解放忘れ防止
	Finalize();
}

// 初期化処理
void SceneManager::Initialize()
{
	// 最初のシーンをタイトル画面にする
	ChangeScene(eSceneType::title);

}

//  更新処理
void SceneManager::Update(float delta_second)
{
	// シーンの更新
	eSceneType next_scene_type = current_scene->Update(delta_second);

	// フォントサイズ変更
	SetFontSize(32);

	// 描画処理
	Draw();

	// 現在のシーンタイプが次のシーンタイプと違っているか？
	if (current_scene->GetNowSceneType() != next_scene_type)
	{
		// シーン切り替え処理
		ChangeScene(next_scene_type);
	}

}

// 終了時処理
void SceneManager::Finalize()
{
	// シーン情報が生成されていれば、削除する
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
}

// 描画処理
void SceneManager::Draw() const
{
	// 画面の初期化
	ClearDrawScreen();

	// シーンの描画処理
	current_scene->Draw();

	// 裏画面の内容を表画面に反映する
	ScreenFlip();
}

// シーン切り替え処理
void SceneManager::ChangeScene(eSceneType next_type)
{
	// 次のシーンを生成する
	SceneBase* next_scene = SceneFactory::CreateScene(next_type);

	// エラーチェック
	if (next_scene == nullptr)
	{
		throw ("シーンが生成できませんでした\n");
	}

	// シーン情報が格納されていたら、削除する
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	// 次のシーンの初期化
	next_scene->Initialize();

	// 現在シーンの上書き
	current_scene = next_scene;
}
