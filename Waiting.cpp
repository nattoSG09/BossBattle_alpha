#include "Waiting.h"
#include "Engine/Input.h"

#include "Player.h"

void Waiting::Start(Player* _pPlayer)
{
}

void Waiting::Update(Player* _pPlayer)
{
	// 移動状態に変更する
	if (_pPlayer->IsStateChange(S_MOVE))_pPlayer->ChangeState(S_MOVE);

}
