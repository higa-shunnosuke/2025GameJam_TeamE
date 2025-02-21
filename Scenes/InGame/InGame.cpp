#include "InGame.h"
#include "DxLib.h"
#include "../../Sign/SignManager.h"

// コンストラクタ
InGame::InGame() :
	sign_manager(nullptr)
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

	sign_manager = new SignManager();
	sign_manager->Initialize();

}

// 更新処理
eSceneType InGame::Update(const float &delta_second)
{
	//入力管理クラスのポインタ
	InputManager* input = InputManager::GetInstance();

	sign_manager->Update(delta_second);

	//スタートボタンが押されたら
	if (input->GetButtonDown(XINPUT_BUTTON_START) == true ||
		input->GetKeyDown(KEY_INPUT_TAB))
	{
		//ポーズ画面へ
		return eSceneType::pause;
	}

	//決定
	if (input->GetButtonDown(XINPUT_BUTTON_A) == true ||
		input->GetKeyDown(KEY_INPUT_RETURN))
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

	sign_manager->Draw();
}

// 終了処理
void InGame::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();

	sign_manager->Finalize();
}

// 現在のシーンタイプ取得処理
const eSceneType InGame::GetNowSceneType() const
{
	return eSceneType::in_game;
}