#pragma once
#include "../Sign/SignBase.h"
#include "../Utilitys/InputManager.h"
#include <DxLib.h>
#include <vector>
#include <cstring>

//���茋��
enum JudgeResult {
	UNJUDGED,   // ������
	CORRECT,    // ����
	INCORRECT   // �s����
};

class ButtonMatch
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ButtonMatch();
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ButtonMatch();

	/// <summary>
	/// ���}�����������ۂɊO������Ăяo���ƁA
	/// sign���獇�}���擾���ăv���C���[2�̏�Ԃ��L�^����
	/// ���}�����������L�^����
	/// </summary>
	/// <param name="sign">SignBase�N���X�̃I�u�W�F�N�g�̃|�C���^</param>
	void Activate(const SignBase* sign);

	/// <summary>
	/// ���}������A���t���[���Ăяo���ē��͂��X�V�����肵�Ă��������B
	/// </summary>
	void ButtonMatchUpdate();

	/// <summary>
	/// �v���C���[1�̔��茋��
	/// </summary>
	/// <returns>UNJUDGED:������
	///  CORRECT:����
	/// INCORRECT:�s����</returns>
	JudgeResult GetPlayer1Result() const;

	/// <summary>
	/// �v���C���[2�̔��茋��
	/// </summary>
	/// <returns>UNJUDGED:������
	///  CORRECT:����
	/// INCORRECT:�s����</returns>
	JudgeResult GetPlayer2Result() const;

	/// <summary>
	/// �v���C���[1�̔������Ԏ擾
	/// </summary>
	/// <returns>�v���C���[1�̔������ԁi�~���b�j</returns>
	unsigned int GetPlayer1ReactionTime() const;

	/// <summary>
	/// �v���C���[2�̔������Ԏ擾
	/// </summary>
	/// <returns>�v���C���[2�̔������ԁi�~���b�j</returns>
	unsigned int GetPlayer2ReactionTime() const;

	/// <summary>
	/// ������Ԃ̃��Z�b�g�i�V�������E���h�J�n���Ɏg���Ă��������j
	/// </summary>
	void ButtonReset();

private:

	bool activated;       // ���}�����ς݂��ǂ���
	bool player1Judged;   // �v���C���[1�͂��łɔ���ς݂�
	bool player2Judged;   // �v���C���[2�͂��łɔ���ς݂�
	JudgeResult player1Result;	//�v���C���[1�̔���󂯓n���p�̕ϐ�
	JudgeResult player2Result;	//�v���C���[2�̔���󂯓n���p�̕ϐ�
	int expectedButton;   // ���}������擾�����A���҂����{�^��

	// �v���C���[2�́A���}�������_�̃{�^�����Ԃ�ێ��iDX_INPUT_PAD2�̃{�^���j
	bool baseline2[D_BUTTON_MAX];

	// ���}���������i�~���b�j��ێ����܂��BDxLib��GetNowCount() �̖߂�l���g�p�B
	unsigned int activationTime;
	// �e�v���C���[�̔������ԁi���}����������͌��o�܂ł̌o�ߎ��ԁA�~���b�j
	unsigned int player1ReactionTime;
	unsigned int player2ReactionTime;

	/// <summary>
	/// 4�̃{�^���iA, B, X, Y�j�̓��͂��ǂ������肵�܂��B
	/// </summary>
	/// <param name="button">����Ώۂ̃{�^���̃R�[�h</param>
	/// <returns>True:4�̃{�^���iA, B, X, Y)�̂����ꂩ False:����ȊO</returns>
	bool IsAllowedButton(int button) const;
};

