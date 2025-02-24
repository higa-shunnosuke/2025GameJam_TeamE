#pragma once

#include <map>
#include <string>
#include <vector>
#include "Singleton.h"

/// <summary>
/// リソース管理クラス
/// </summary>
class ResourceManager : public Singleton<ResourceManager>
{
private:
	std::map<std::string, std::vector<int>> images_container;	// 画像保存用変数
	std::map<std::string, int> sounds_container;				// 音源保存用変数

public:
	/// <summary>
	/// 画像取得処理
	/// </summary>
	/// <param name="file_name">ファイルパス</param>
	/// <param name="all_num">画像総枚数</param>
	/// <param name="num_x">横の枚数</param>
	/// <param name="num_y">縦の枚数</param>
	/// <param name="size_x">横のサイズ(px)</param>
	/// <param name="size_y">縦のサイズ(px)</param>
	/// <returns>画像データ</returns>
	const std::vector<int>& GetImages(std::string file_name, int all_num = 1, int num_x = 1, int num_y = 1, int size_x = 0, int size_y = 0);
	/// <summary>
	/// 画像取得処理
	/// </summary>
	/// <param name="file_name">ファイルパス</param>
	/// <param name="all_num">画像総枚数</param>
	/// <param name="num_x">横の枚数</param>
	/// <param name="num_y">縦の枚数</param>
	/// <param name="size_x">横のサイズ(px)</param>
	/// <param name="size_y">縦のサイズ(px)</param>
	/// <returns>画像データ</returns>
	const std::vector<int>& GetImages(const char* file_name, int all_num = 1, int num_x = 1, int num_y = 1, int size_x = 0, int size_y = 0);

	/// <summary>
	/// 音源取得処理
	/// </summary>
	/// <param name="file_path">ファイルパス</param>
	/// <returns>音源データreturns>
	int GetSounds(std::string file_path);
	/// <summary>
	/// 音源取得処理
	/// </summary>
	/// <param name="file_path">ファイルパス</param>
	/// <returns>音源データreturns>
	int GetSounds(const char* file_path);

	/// <summary>
	/// 画像削除
	/// </summary>
	void UnLoadImages();

	/// <summary>
	/// 音源削除
	/// </summary>
	void UnLoadSounds();

private:
	/// <summary>
	/// 画像読込み
	/// </summary>
	/// <param name="file_path">ファイルパス</param>
	void CreateImagesResource(std::string file_path);

	/// <summary>
	/// 画像読込み
	/// </summary>
	/// <param name="file_name">ファイルパス</param>
	/// <param name="all_num">画像総枚数</param>
	/// <param name="num_x">横の枚数</param>
	/// <param name="num_y">縦の枚数</param>
	/// <param name="size_x">横のサイズ(px)</param>
	/// <param name="size_y">縦のサイズ(px)</param>
	void CreateImagesResource(std::string file_name, int all_num, int num_x, int num_y, int size_x, int size_y);

	/// <summary>
	/// 音源読込み
	/// </summary>
	/// <param name="file_path">ファイルパス</param>
	void CreateSoundsResource(std::string file_path);
};