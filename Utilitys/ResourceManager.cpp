#include "ResourceManager.h"
#include "DxLib.h"

//画像取得
const std::vector<int>& ResourceManager::GetImages(std::string file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	// コンテナの中身があれば
	if (images_container.count(file_name) == NULL)
	{
		// 画像の枚数指定が無ければ
		if (all_num == 1)
		{
			// 画像データを読み込む
			CreateImagesResource(file_name);
		}
		else
		{
			// 複数枚の画像データを読み込む
			CreateImagesResource(file_name, all_num, num_x, num_y, size_x, size_y);
		}
	}

	// 画像データを返す
	return images_container[file_name];
}
const std::vector<int>& ResourceManager::GetImages(const char* file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	return GetImages(std::string(file_name), all_num, num_x, num_y, size_x, size_y);
}

//音源読込み
int ResourceManager::GetSounds(std::string file_path)
{
	// コンテナの中身があれば
	if (sounds_container.count(file_path) == NULL)
	{
		// 音源データを読み込む
		CreateSoundsResource(file_path);
	}

	// 音源データを返す
	return sounds_container[file_path];
}
int ResourceManager::GetSounds(const char* file_path)
{
	return GetSounds(std::string(file_path));
}

//画像データ削除
void ResourceManager::UnLoadImages()
{
	// コンテナの中が空なら
	if (images_container.size() == NULL)
	{
		return;
	}

	for (std::pair<std::string, std::vector<int>> value : images_container)
	{
		DeleteSharingGraph(value.second[0]);
		value.second.clear();
	}

	// コンテナの中身を削除する
	images_container.clear();
}

//音源データ削除
void ResourceManager::UnLoadSounds()
{
	// コンテナの中が空なら
	if (sounds_container.size() == NULL)
	{
		return;
	}

	for (std::pair<std::string, int> value : sounds_container)
	{
		DeleteSoundMem(value.second);
	}

	// コンテナの中身を削除する
	sounds_container.clear();
}

//画像読込み
void ResourceManager::CreateImagesResource(std::string file_path)
{
	// ファイルパス
	int handle = LoadGraph(file_path.c_str());

	// ファイル読込み
	if (handle == -1)
	{
		throw (file_path + "ファイルが読み込めませんでした\n");
	}

	// コンテナに格納
	images_container[file_path].push_back(handle);
}
void ResourceManager::CreateImagesResource(std::string file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	// ファイルパス
	int* handle = new int[all_num];

	int result = LoadDivGraph(file_name.c_str(), all_num, num_x, num_y, size_x, size_y, handle);

	// ファイル読込み
	if (result == -1)
	{
		throw (file_name + "ファイルが読み込めませんでした\n");
	}

	// コンテナに格納
	for (int i = 0; i < all_num; i++)
	{
		images_container[file_name].push_back(handle[i]);
	}

	// ファイルパスを削除
	delete[] handle;
}

void ResourceManager::CreateSoundsResource(std::string file_path)
{
	// ファイルパス
	int handle = LoadSoundMem(file_path.c_str());

	// ファイル読込み
	if (handle == -1)
	{
		throw (file_path + "ファイルが読み込めませんでした\n");
	}

	// コンテナに格納
	sounds_container[file_path] = handle;
}
