#include "Help.h"
#include "DxLib.h"

// �R���X�g���N�^
Help::Help()
{

}

// �f�X�g���N�^
Help::~Help()
{

}

// ����������
void Help::Initialize()
{
	// �e�N���X�̏������������Ăяo��
	__super::Initialize();

}

// �X�V����
eSceneType Help::Update(const float &delta_second)
{

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);
}

// �`�揈��
void Help::Draw() const
{

}

// �I������
void Help::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

// ���݂̃V�[���^�C�v�擾����
const eSceneType Help::GetNowSceneType() const
{
	return eSceneType::title;
}