#include "Result.h"
#include "DxLib.h"

// �R���X�g���N�^
Result::Result()
{

}

// �f�X�g���N�^
Result::~Result()
{

}

// ����������
void Result::Initialize()
{
	// �e�N���X�̏������������Ăяo��
	__super::Initialize();

}

// �X�V����
eSceneType Result::Update(const float &delta_second)
{

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);
}

// �`�揈��
void Result::Draw() const
{

}

// �I������
void Result::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

// ���݂̃V�[���^�C�v�擾����
const eSceneType Result::GetNowSceneType() const
{
	return eSceneType::title;
}