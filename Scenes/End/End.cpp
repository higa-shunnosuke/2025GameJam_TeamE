#include "End.h"
#include "DxLib.h"
#include "../../Application.h"

// コンストラクタ
End::End():
	time()
{

}

// デストラクタ
End::~End()
{

}

// 初期化処理
void End::Initialize()
{
	// 親クラスの初期化処理を呼び出す
	__super::Initialize();

}

// 更新処理
eSceneType End::Update(const float &delta_second)
{
	time += delta_second;

	//3秒経過したら
	if (time > 3.0f)
	{
		time = 3.0f;
		//ゲームを終了させる
		Application* app = Application::GetInstance();
		app->QuitGame(true);
	}


	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

// 描画処理
void End::Draw() const
{
	// フォントサイズ変更
	SetFontSize(32);

	DrawFormatString(10, 10, 0xffffff, "End");
	DrawFormatString(100, 240, 0xffffff, "Thank you for playing");
	DrawFormatString(620, 450, 0xffffff, "%.0f",3.0f - time);

}

// 終了処理
void End::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

// 現在のシーンタイプ取得処理
const eSceneType End::GetNowSceneType() const
{
	return eSceneType::end;
}
