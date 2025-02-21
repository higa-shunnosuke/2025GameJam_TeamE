#include "Result.h"
#include "DxLib.h"

// コンストラクタ
Result::Result()
{

}

// デストラクタ
Result::~Result()
{

}

// 初期化処理
void Result::Initialize()
{
	// 親クラスの初期化処理を呼び出す
	__super::Initialize();

}

// 更新処理
eSceneType Result::Update(const float &delta_second)
{
	//入力管理クラスのポインタ
	InputManager* input = InputManager::GetInstance();

	//決定
	if (input->GetButtonDown(XINPUT_BUTTON_A) == true)
	{
		//タイトル画面へ
		return eSceneType::title;
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

// 描画処理
void Result::Draw() const
{
	// フォントサイズ変更
	SetFontSize(32);

	DrawFormatString(10, 10, 0xffffff, "Result");
}

// 終了処理
void Result::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

// 現在のシーンタイプ取得処理
const eSceneType Result::GetNowSceneType() const
{
	return eSceneType::result;
}