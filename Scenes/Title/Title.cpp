#include "Title.h"
#include "DxLib.h"

// �R���X�g���N�^
Title::Title()
{

}

// �f�X�g���N�^
Title::~Title()
{

}

// ����������
void Title::Initialize()
{
	// �e�N���X�̏������������Ăяo��
	__super::Initialize();

}

// �X�V����
eSceneType Title::Update(const float &delta_second)
{

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);
}

// �`�揈��
void Title::Draw() const
{

}

// �I������
void Title::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

// ���݂̃V�[���^�C�v�擾����
const eSceneType Title::GetNowSceneType() const
{
	return eSceneType::title;
}