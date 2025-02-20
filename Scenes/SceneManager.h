#pragma once

#include "../Utilitys/Singleton.h"
#include "SceneBase.h"

class SceneManager : public Singleton<SceneManager>
{
private:
	SceneBase* current_scene;	// ���݂̃V�[�����

public:
	// �R���X�g���N�^
	SceneManager();
	// �f�X�g���N�^
	~SceneManager();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void Update(float delta_second);

	/// <summary>
	/// �I��������
	/// </summary>
	void Finalize();

private:
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;

	/// <summary>
	/// �V�[���؂�ւ�����
	/// </summary>
	/// <param name="next_type">���̃V�[���^�C�v</param>
	void ChangeScene(eSceneType next_type);

};

