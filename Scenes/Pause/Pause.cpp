#include "Pause.h"
#include "DxLib.h"

// �R���X�g���N�^
Pause::Pause()
{

}

// �f�X�g���N�^
Pause::~Pause()
{

}

// ����������
void Pause::Initialize()
{
	// �e�N���X�̏������������Ăяo��
	__super::Initialize();

}

// �X�V����
eSceneType Pause::Update(const float &delta_second)
{

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);
}

// �`�揈��
void Pause::Draw() const
{

}

// �I������
void Pause::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

// ���݂̃V�[���^�C�v�擾����
const eSceneType Pause::GetNowSceneType() const
{
	return eSceneType::title;
}