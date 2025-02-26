#include "Result.h"
#include "DxLib.h"

#define FILE_NAME "Resources/datas/Reaction_Data.csv"

// コンストラクタ
Result::Result():
	count(),
	player1(),
	player2()
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

	ResourceManager* rm = ResourceManager::GetInstance();
	bg_image = rm->GetImages("Resources/images/InGame_BackGround.png")[0];

	//サウンドが入っていない場合
	if (sound.empty())
	{
		//サウンドを追加
		sound.push_back(rm->GetSounds("Resources/sounds/bgm/Result.wav"));

		//音量を設定
		ChangeVolumeSoundMem(110, sound.at(0));
	}

	//カウンタの初期化
	count = 0;

	//データ読み込み
	ReadData();
}

// 更新処理
eSceneType Result::Update(const float &delta_second)
{
	//サウンドが再生されていない場合サウンドを再生する
	if (!CheckSoundMem(sound.at(0)))PlaySoundMem(sound.at(0), DX_PLAYTYPE_LOOP);

	//入力管理クラスのポインタ
	InputManager* input = InputManager::GetInstance();

	//決定
	if (input->GetButtonDown(0, XINPUT_BUTTON_A) == true ||
		input->GetKeyDown(KEY_INPUT_RETURN))
	{
		//BGMを止める
		StopSoundMem(sound.at(0));

		//タイトル画面へ
		return eSceneType::title;
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

// 描画処理
void Result::Draw() const
{
	//背景描画
	DrawRotaGraph(320, 240, 1.0, 0.0, bg_image, TRUE);

	// フォントサイズ変更
	SetFontSize(32);

	DrawFormatString(10, 10, 0xffffff, "Result");

	for (int i = 0; i < count; i++)
	{
		DrawFormatString(0, 100 + (30 * i), 0xffffff, "Round%d:1p:%.1f", i, player1[i]);

		DrawFormatString(250, 100 + (30 * i), 0xffffff, "2p:%.1f", player2[i]);

	}
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

// ファイルデータ読み込み処理
void Result::ReadData()
{
	FILE* fp;
	char line[16];

	//ファイルを開く
	fopen_s(&fp, FILE_NAME, "r");

	if (fp == NULL)
	{
		throw("Could not open file %s.", FILE_NAME);
	}
	else
	{
		//データを読み込む
		while (fgets(line,16,fp) != NULL)
		{
			sscanf_s(line, "%f,%f", &player1[count], &player2[count]);
			count++;
		}
		
		//ファイルを閉じる
		fclose(fp);
	}
}
