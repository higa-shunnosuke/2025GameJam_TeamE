#include "InGame.h"
#include "DxLib.h"

// コンストラクタ
InGame::InGame()
{

}

// デストラクタ
InGame::~InGame()
{

}

// 初期化処理
void InGame::Initialize()
{
	// 親クラスの初期化処理を呼び出す
	__super::Initialize();

}

// 更新処理
eSceneType InGame::Update(const float &delta_second)
{
	//入力管理クラスのポインタ
	InputManager* input = InputManager::GetInstance();

	//スタートボタンが押されたら
	if (input->GetButtonDown(XINPUT_BUTTON_START) == true)
	{
		//ポーズ画面へ
		return eSceneType::pause;
	}

	//決定
	if (input->GetButtonDown(XINPUT_BUTTON_A) == true)
	{
		//リザルト画面へ
		return eSceneType::result;
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

// 描画処理
void InGame::Draw() const
{
	// フォントサイズ変更
	SetFontSize(32);

	DrawFormatString(10, 10, 0xffffff, "InGame");
}

// 終了処理
void InGame::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

// 現在のシーンタイプ取得処理
const eSceneType InGame::GetNowSceneType() const
{
	return eSceneType::in_game;
}