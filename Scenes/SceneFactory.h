#pragma once

#include "SceneBase.h"
#include "Title/Title.h"
#include "Help/Help.h"
#include "InGame/InGame.h"
#include "Pause/Pause.h"
#include "Result/Result.h"
#include "End/End.h"

class SceneFactory
{
public:

	/// <summary>
	/// シーン生成処理
	/// </summary>
	/// <param name="next_type">次のシーンタイプ</param>
	/// <returns>生成したシーン情報のポインタ</returns>
	static SceneBase* CreateScene(eSceneType next_type)
	{
		// シーンタイプによって、生成するシーンを切り替える
		switch (next_type)
		{
		case eSceneType::title:
			return dynamic_cast<SceneBase*>(new Title());
			break;
		case eSceneType::help:
			return dynamic_cast<SceneBase*>(new Help());
			break;
		case eSceneType::re_start:
		case eSceneType::in_game:
			return dynamic_cast<SceneBase*>(new InGame());
			break;
		case eSceneType::pause:
			return dynamic_cast<SceneBase*>(new Pause());
			break;
		case eSceneType::result:
			return dynamic_cast<SceneBase*>(new Result());
			break;
		case eSceneType::end:
			return dynamic_cast<SceneBase*>(new End());
			break;
		}

		return nullptr;
	}
};