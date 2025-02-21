#include "Pause.h"
#include "DxLib.h"

// コンストラクタ
Pause::Pause()
{

}

// デストラクタ
Pause::~Pause()
{

}

// 初期化処理
void Pause::Initialize()
{
	// 親クラスの初期化処理を呼び出す
	__super::Initialize();

}

// 更新処理
eSceneType Pause::Update(const float &delta_second)
{

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

// 描画処理
void Pause::Draw() const
{

}

// 終了処理
void Pause::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

// 現在のシーンタイプ取得処理
const eSceneType Pause::GetNowSceneType() const
{
	return eSceneType::title;
}