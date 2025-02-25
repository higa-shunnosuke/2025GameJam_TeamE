#include "Help.h"
#include "DxLib.h"

//テキスト
#define STRING_1 "ゲーム内容\n合図が出たら相手より先にボタンを押してください。"
#define STRING_2 "勝利条件\n３ポイント先取（最高５回戦）\n早撃ちに勝つごとに１ポイント取得\n同時に押した場合はどちらのポイントにもなりません。"
#define STRING_3 "ファール\n条件１：合図が出るより先にボタンを押す\n条件２：間違ったボタンを押す\n２回ファールをすると負けとなります。"

// コンストラクタ
Help::Help()
{

}

// デストラクタ
Help::~Help()
{

}

// 初期化処理
void Help::Initialize()
{
	// 親クラスの初期化処理を呼び出す
	__super::Initialize();

	ResourceManager* rm = ResourceManager::GetInstance();
	bg_image = rm->GetImages("Resources/images/InGame_BackGround.png")[0];
}

// 更新処理
eSceneType Help::Update(const float &delta_second)
{
	//入力管理クラスのポインタ
	InputManager* input = InputManager::GetInstance();

	//戻る
	if (input->GetButtonDown(0, XINPUT_BUTTON_B) == true ||
		input->GetKeyDown(KEY_INPUT_BACK))
	{
		//タイトル画面へ
		return eSceneType::title;
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

// 描画処理
void Help::Draw() const
{
	//背景描画
	DrawRotaGraph(320, 240, 1.0, 0.0, bg_image, TRUE);

	// フォントサイズ変更
	SetFontSize(16);

	DrawFormatString(10, 100, 0xffffff, STRING_1);
	DrawFormatString(10, 160, 0xffffff, STRING_2);
	DrawFormatString(10, 240, 0xffffff, STRING_3);

	// フォントサイズ変更
	SetFontSize(32);
	DrawFormatString(10, 10, 0xffffff, "Help");
	DrawFormatString(10, 450, 0xffffff, "True = A,False = B");
}

// 終了処理
void Help::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

// 現在のシーンタイプ取得処理
const eSceneType Help::GetNowSceneType() const
{
	return eSceneType::help;
}