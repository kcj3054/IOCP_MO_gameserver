#pragma once

#include "Creature.h"

/*
* 게임 내에서 유저가 소지해야할, 관련있는 모든 것들이 필요한 class이다. 
*/

class User final :  public Creature
{
public:
	// 유저가 EnterWorld 시 스폰 위치 보정값 
	static constexpr float userSpawn = 100.f; // 수는 조절이 필요함 

public:
	//User 단위 직렬화 
	// Actor Job을 사용하려면 User가 Job을 가지고있는 것이 맞다

	//Component 기반들이면 User에 Component 등록이 필요하다 
	void SetComponents();

	//월드 진입 시작 
	bool EnterWorldStart(); 
public:
	//월드 진입, 월드 나감 
	void OnEnterWorld();
	void OnLeaveWorld();

	//Warp도 가능

private:
	// Spawn, Despawn..
	// 

	// User::OnTickSaveData
	// User::LeaveWorldStart.
	// User::OnDie
	// 워프할때도? 왜 ? 
	void UpdateUserDBData();

};

