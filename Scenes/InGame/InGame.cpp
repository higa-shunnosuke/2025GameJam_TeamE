#include "InGame.h"
#include "DxLib.h"

// �R���X�g���N�^
InGame::InGame()
{

}

// �f�X�g���N�^
InGame::~InGame()
{

}

// ����������
void InGame::Initialize()
{
	// �e�N���X�̏������������Ăяo��
	__super::Initialize();

}

// �X�V����
eSceneType InGame::Update(const float &delta_second)
{

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);
}

// �`�揈��
void InGame::Draw() const
{

}

// �I������
void InGame::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

// ���݂̃V�[���^�C�v�擾����
const eSceneType InGame::GetNowSceneType() const
{
	return eSceneType::title;
}