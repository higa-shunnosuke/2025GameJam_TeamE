#include "End.h"
#include "DxLib.h"

// �R���X�g���N�^
End::End()
{

}

// �f�X�g���N�^
End::~End()
{

}

// ����������
void End::Initialize()
{
	// �e�N���X�̏������������Ăяo��
	__super::Initialize();

}

// �X�V����
eSceneType End::Update(const float &delta_second)
{
	
	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);
}

// �`�揈��
void End::Draw() const
{
	
}

// �I������
void End::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

// ���݂̃V�[���^�C�v�擾����
const eSceneType End::GetNowSceneType() const
{
	return eSceneType::title;
}
