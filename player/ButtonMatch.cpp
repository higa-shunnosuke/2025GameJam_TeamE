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

    // 合図発動フラグを立て、判定の状態をリセット
    activated = true;
    player1Judged = false;
    player2Judged = false;
    player1Result = UNJUDGED;
    player2Result = UNJUDGED;

    // GetSignButton() から合図のボタンを取得
    std::vector<int> signButtons = sign->GetSignButton();
    if (!signButtons.empty())
    {
        expectedButton = signButtons[0];
    }
    else
    {
        expectedButton = -1;
    }

    // プレイヤー２の現在のボタン状態を基準として記録
    XINPUT_STATE state2 = {};
    GetJoypadXInputState(DX_INPUT_PAD2, &state2);
    for (int i = 0; i < D_BUTTON_MAX; i++)
    {
        baseline2[i] = (state2.Buttons[i] != 0);
    }

    // 合図発動時刻を記録（ミリ秒単位）
    activationTime = GetNowCount();
}

void ButtonMatch::ButtonMatchUpdate()
{
    if (!activated) return;

    // --- プレイヤー１の判定 ---
    if (!player1Judged)
    {
        // 期待するボタンが新たに押された場合
        if (IsAllowedButton(expectedButton) && InputManager::GetInstance()->GetButtonDown(0, expectedButton))
        {
            player1Result = CORRECT;
            player1ReactionTime = GetNowCount() - activationTime;
            player1Judged = true;
        }
        else
        {
            // 期待ボタン以外の対象ボタンが押された場合は不正解
            if ((expectedButton != XINPUT_BUTTON_A && InputManager::GetInstance()->GetButtonDown(0, XINPUT_BUTTON_A)) ||
                (expectedButton != XINPUT_BUTTON_B && InputManager::GetInstance()->GetButtonDown(0, XINPUT_BUTTON_B)) ||
                (expectedButton != XINPUT_BUTTON_X && InputManager::GetInstance()->GetButtonDown(0, XINPUT_BUTTON_X)) ||
                (expectedButton != XINPUT_BUTTON_Y && InputManager::GetInstance()->GetButtonDown(0, XINPUT_BUTTON_Y)))
            {
                player1Result = INCORRECT;
                player1ReactionTime = GetNowCount() - activationTime;
                player1Judged = true;
            }
        }
    }

    // --- プレイヤー２の判定 ---
    // 現在の状態を取得し、合図発動時の基準（baseline2）との差分で新たな入力を検出します
    XINPUT_STATE state2 = {};
    GetJoypadXInputState(DX_INPUT_PAD2, &state2);
    if (!player2Judged)
    {
        int allowedButtons[4] = { XINPUT_BUTTON_A, XINPUT_BUTTON_B, XINPUT_BUTTON_X, XINPUT_BUTTON_Y };
        for (int i = 0; i < 4; i++)
        {
            int btn = allowedButtons[i];
            bool currentPressed = (state2.Buttons[btn] != 0);
            // 基準状態で未押下だったのに、現在新たに押された場合を検出
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
