﻿#include <DxLib.h>
#include <cstring> 
#include "ButtonMatch.h"
#include "../Sign/RandomSign.h"
#include "../Utilitys/ResourceManager.h"

ButtonMatch::ButtonMatch()
    : activated(false),
    player1Judged(false),
    player2Judged(false),
    player1Result(UNJUDGED),
    player2Result(UNJUDGED),
    player1ExpectedButton(-1),
    player2ExpectedButton(-1),
    activationTime(0),
    player1ReactionTime(0.f),
    player2ReactionTime(0.f),
    isCorrectPlayer1(false),
    isCorrectPlayer2(false)
{
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
    player1ExpectedButton = -1;
    player2ExpectedButton = -1;
    activationTime = 0;
    player1ReactionTime = 0.f;
    player2ReactionTime = 0.f;
    isCorrectPlayer1 = false;
    isCorrectPlayer2 = false;
}

bool ButtonMatch::IsAllowedButton(int button) const
{
    return (button == XINPUT_BUTTON_A ||
        button == XINPUT_BUTTON_B ||
        button == XINPUT_BUTTON_X ||
        button == XINPUT_BUTTON_Y);
}

void ButtonMatch::Activate(SignBase* sign)
{
    if (!sign) return;

    // 合図発動フラグを立て、判定の状態をリセット
    activated = true;
    player1Judged = false;
    player2Judged = false;
    player1Result = UNJUDGED;
    player2Result = UNJUDGED;

    // GetSignButton() から合図のボタンを取得
    std::vector<int> Player1SignButtons = sign->GetSignButton();
    //合図がランダム合図の場合
    if (sign->GetSignName() == "RandomSign")
    {
        //ランダム合図の型にキャストする
        RandomSign* r_s = dynamic_cast<RandomSign*>(sign);
        //最初のボタンを取得
        Player1SignButtons = r_s->GetButton(0);
    }
    //早押し合図の場合
    else if (sign->GetSignName() == "QuickPressSign")
    {
        //空の場合
        if (Player1SignButtons.empty())
        {
            //0を追加
            Player1SignButtons.push_back(0);
        }
        //すでに値がある場合
        else
        {
            //0を代入
            Player1SignButtons[0] = 0;
        }
    }
    if (!Player1SignButtons.empty())
    {
        player1ExpectedButton = Player1SignButtons[0];
    }
    else
    {
        player1ExpectedButton = -1;
    }

    // GetSignButton() から合図のボタンを取得
    std::vector<int> Player2SignButtons = sign->GetSignButton();
    //合図がランダム合図の場合
    if (sign->GetSignName() == "RandomSign")
    {
        //ランダム合図の型にキャストする
        RandomSign* r_s = dynamic_cast<RandomSign*>(sign);
        //最初のボタンを取得
        Player2SignButtons = r_s->GetButton(1);
    }
    //早押し合図の場合
    else if (sign->GetSignName() == "QuickPressSign")
    {
        //空の場合
        if (Player2SignButtons.empty())
        {
            //0を追加
            Player2SignButtons.push_back(0);
        }
        //すでに値がある場合
        else
        {
            //0を代入
            Player2SignButtons[0] = 0;
        }
    }
    if (!Player2SignButtons.empty())
    {
        player2ExpectedButton = Player2SignButtons[0];
    }
    else
    {
        player2ExpectedButton = -1;
    }

    // 合図発動時刻を記録（ミリ秒単位）
    activationTime = GetNowCount();
}

void ButtonMatch::ButtonMatchUpdate(const float& delta_second)
{
    if (!activated) return;

    //プレイヤー1の判定が成功でないなら時間を加算する
    if (!isCorrectPlayer1)player1ReactionTime += delta_second;
    //プレイヤー2の判定が成功でないなら時間を加算する
    if (!isCorrectPlayer2)player2ReactionTime += delta_second;

    // --- プレイヤー１の判定 ---
    if (!player1Judged)
    {
        // 期待するボタンが新たに押された場合
        if (IsAllowedButton(player1ExpectedButton) && InputManager::GetInstance()->GetButtonDown(0, player1ExpectedButton))
        {
            player1Result = CORRECT;
            player1Judged = true;
        }
        else
        {
            //早押し合図のときA,B,X,Yが押された場合
            if (player1ExpectedButton == 0 &&
                (InputManager::GetInstance()->GetButtonDown(0, XINPUT_BUTTON_A) ||
                    InputManager::GetInstance()->GetButtonDown(0, XINPUT_BUTTON_B) ||
                    InputManager::GetInstance()->GetButtonDown(0, XINPUT_BUTTON_X) ||
                    InputManager::GetInstance()->GetButtonDown(0, XINPUT_BUTTON_Y)))
            {
                player1Result = CORRECT;
                player1Judged = true;
            }
            else
            {
                // 期待ボタン以外の対象ボタンが押された場合は不正解
                if ((player1ExpectedButton != XINPUT_BUTTON_A && InputManager::GetInstance()->GetButtonDown(0, XINPUT_BUTTON_A)) ||
                    (player1ExpectedButton != XINPUT_BUTTON_B && InputManager::GetInstance()->GetButtonDown(0, XINPUT_BUTTON_B)) ||
                    (player1ExpectedButton != XINPUT_BUTTON_X && InputManager::GetInstance()->GetButtonDown(0, XINPUT_BUTTON_X)) ||
                    (player1ExpectedButton != XINPUT_BUTTON_Y && InputManager::GetInstance()->GetButtonDown(0, XINPUT_BUTTON_Y)))
                {
                    player1Result = INCORRECT;
                    player1Judged = true;
                }
            }
        }
    }

    // --- プレイヤー２の判定 ---
    if (!player2Judged)
    {
        // 期待するボタンが新たに押された場合
        if (IsAllowedButton(player2ExpectedButton) && InputManager::GetInstance()->GetButtonDown(1, player2ExpectedButton))
        {
            player2Result = CORRECT;
            player2Judged = true;
        }
        else
        {
            //早押し合図のときA,B,X,Yが押された場合
            if (player2ExpectedButton == 0 &&
                (InputManager::GetInstance()->GetButtonDown(1, XINPUT_BUTTON_A) ||
                    InputManager::GetInstance()->GetButtonDown(1, XINPUT_BUTTON_B) ||
                    InputManager::GetInstance()->GetButtonDown(1, XINPUT_BUTTON_X) ||
                    InputManager::GetInstance()->GetButtonDown(1, XINPUT_BUTTON_Y)))
            {
                player2Result = CORRECT;
                player2Judged = true;
            }
            else
            {
                // 期待ボタン以外の対象ボタンが押された場合は不正解
                if ((player2ExpectedButton != XINPUT_BUTTON_A && InputManager::GetInstance()->GetButtonDown(1, XINPUT_BUTTON_A)) ||
                    (player2ExpectedButton != XINPUT_BUTTON_B && InputManager::GetInstance()->GetButtonDown(1, XINPUT_BUTTON_B)) ||
                    (player2ExpectedButton != XINPUT_BUTTON_X && InputManager::GetInstance()->GetButtonDown(1, XINPUT_BUTTON_X)) ||
                    (player2ExpectedButton != XINPUT_BUTTON_Y && InputManager::GetInstance()->GetButtonDown(1, XINPUT_BUTTON_Y)))
                {
                    player2Result = INCORRECT;
                    player2Judged = true;
                }
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

float ButtonMatch::GetPlayer1ReactionTime() const
{
    return player1ReactionTime;
}

float ButtonMatch::GetPlayer2ReactionTime() const
{
    return player2ReactionTime;
}
