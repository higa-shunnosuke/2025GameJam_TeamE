#include <DxLib.h>
#include <cstring> 
#include "ButtonMatch.h"


ButtonMatch::ButtonMatch()
    : activated(false),
    player1Judged(false),
    player2Judged(false),
    player1Result(UNJUDGED),
    player2Result(UNJUDGED),
    expectedButton(-1),
    activationTime(0),
    player1ReactionTime(0),
    player2ReactionTime(0)
{
    memset(baseline2, 0, sizeof(baseline2));
}

ButtonMatch::~ButtonMatch()
{
}


void ButtonMatch::ButtonReset()
{
    activated = false;
    player1Judged = false;
    player2Judged = false;
    player1Result = UNJUDGED;
    player2Result = UNJUDGED;
    expectedButton = -1;
    activationTime = 0;
    player1ReactionTime = 0;
    player2ReactionTime = 0;
    memset(baseline2, 0, sizeof(baseline2));
}

bool ButtonMatch::IsAllowedButton(int button) const
{
    return (button == XINPUT_BUTTON_A ||
        button == XINPUT_BUTTON_B ||
        button == XINPUT_BUTTON_X ||
        button == XINPUT_BUTTON_Y);
}

void ButtonMatch::Activate(const SignBase* sign)
{
    if (!sign) return;

    // ���}�����t���O�𗧂āA����̏�Ԃ����Z�b�g
    activated = true;
    player1Judged = false;
    player2Judged = false;
    player1Result = UNJUDGED;
    player2Result = UNJUDGED;

    // GetSignButton() ���獇�}�̃{�^�����擾
    std::vector<int> signButtons = sign->GetSignButton();
    if (!signButtons.empty())
    {
        expectedButton = signButtons[0];
    }
    else
    {
        expectedButton = -1;
    }

    // �v���C���[�Q�̌��݂̃{�^����Ԃ���Ƃ��ċL�^
    XINPUT_STATE state2 = {};
    GetJoypadXInputState(DX_INPUT_PAD2, &state2);
    for (int i = 0; i < D_BUTTON_MAX; i++)
    {
        baseline2[i] = (state2.Buttons[i] != 0);
    }

    // ���}�����������L�^�i�~���b�P�ʁj
    activationTime = GetNowCount();
}

void ButtonMatch::ButtonMatchUpdate()
{
    if (!activated) return;

    // --- �v���C���[�P�̔��� ---
    if (!player1Judged)
    {
        // ���҂���{�^�����V���ɉ����ꂽ�ꍇ
        if (IsAllowedButton(expectedButton) && InputManager::GetInstance()->GetButtonDown(expectedButton))
        {
            player1Result = CORRECT;
            player1ReactionTime = GetNowCount() - activationTime;
            player1Judged = true;
        }
        else
        {
            // ���҃{�^���ȊO�̑Ώۃ{�^���������ꂽ�ꍇ�͕s����
            if ((expectedButton != XINPUT_BUTTON_A && InputManager::GetInstance()->GetButtonDown(XINPUT_BUTTON_A)) ||
                (expectedButton != XINPUT_BUTTON_B && InputManager::GetInstance()->GetButtonDown(XINPUT_BUTTON_B)) ||
                (expectedButton != XINPUT_BUTTON_X && InputManager::GetInstance()->GetButtonDown(XINPUT_BUTTON_X)) ||
                (expectedButton != XINPUT_BUTTON_Y && InputManager::GetInstance()->GetButtonDown(XINPUT_BUTTON_Y)))
            {
                player1Result = INCORRECT;
                player1ReactionTime = GetNowCount() - activationTime;
                player1Judged = true;
            }
        }
    }

    // --- �v���C���[�Q�̔��� ---
    // ���݂̏�Ԃ��擾���A���}�������̊�ibaseline2�j�Ƃ̍����ŐV���ȓ��͂����o���܂�
    XINPUT_STATE state2 = {};
    GetJoypadXInputState(DX_INPUT_PAD2, &state2);
    if (!player2Judged)
    {
        int allowedButtons[4] = { XINPUT_BUTTON_A, XINPUT_BUTTON_B, XINPUT_BUTTON_X, XINPUT_BUTTON_Y };
        for (int i = 0; i < 4; i++)
        {
            int btn = allowedButtons[i];
            bool currentPressed = (state2.Buttons[btn] != 0);
            // ���ԂŖ������������̂ɁA���ݐV���ɉ����ꂽ�ꍇ�����o
            if (currentPressed && !baseline2[btn])
            {
                if (btn == expectedButton)
                {
                    player2Result = CORRECT;
                }
                else
                {
                    player2Result = INCORRECT;
                }
                player2Judged = true;
                break;
            }
        }
    }
}

JudgeResult ButtonMatch::GetPlayer1Result() const
{
    return player1Result;
}

JudgeResult ButtonMatch::GetPlayer2Result() const
{
    return player2Result;
}

unsigned int ButtonMatch::GetPlayer1ReactionTime() const
{
    return player1ReactionTime;
}

unsigned int ButtonMatch::GetPlayer2ReactionTime() const
{
    return player2ReactionTime;
}
