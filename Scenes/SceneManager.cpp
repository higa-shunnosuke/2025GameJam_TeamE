#include "SceneManager.h"
#include "SceneFactory.h"
#include "DxLib.h"

#include "../Utilitys/InputManager.h"

// �R���X�g���N�^
SceneManager::SceneManager() :
	current_scene(nullptr)
{

}

// �f�X�g���N
SceneManager::~SceneManager()
{
	// ����Y��h�~
	Finalize();
}

// ����������
void SceneManager::Initialize()
{
	// �ŏ��̃V�[�����^�C�g����ʂɂ���
	ChangeScene(eSceneType::title);

}

//  �X�V����
void SceneManager::Update(float delta_second)
{
	// �V�[���̍X�V
	eSceneType next_scene_type = current_scene->Update(delta_second);

	// �t�H���g�T�C�Y�ύX
	SetFontSize(32);

	// �`�揈��
	Draw();

	// ���݂̃V�[���^�C�v�����̃V�[���^�C�v�ƈ���Ă��邩�H
	if (current_scene->GetNowSceneType() != next_scene_type)
	{
		// �V�[���؂�ւ�����
		ChangeScene(next_scene_type);
	}
}

// �I��������
void SceneManager::Finalize()
{
	// �V�[����񂪐�������Ă���΁A�폜����
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
}

// �`�揈��
void SceneManager::Draw() const
{
	// ��ʂ̏�����
	ClearDrawScreen();

	// �V�[���̕`�揈��
	current_scene->Draw();

	// ����ʂ̓��e��\��ʂɔ��f����
	ScreenFlip();
}

// �V�[���؂�ւ�����
void SceneManager::ChangeScene(eSceneType next_type)
{
	// ���̃V�[���𐶐�����
	SceneBase* next_scene = SceneFactory::CreateScene(next_type);

	// �G���[�`�F�b�N
	if (next_scene == nullptr)
	{
		throw ("�V�[���������ł��܂���ł���\n");
	}

	// �V�[����񂪊i�[����Ă�����A�폜����
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	// ���̃V�[���̏�����
	next_scene->Initialize();

	// ���݃V�[���̏㏑��
	current_scene = next_scene;
}
