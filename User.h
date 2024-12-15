#pragma once

#include "Creature.h"

/*
* ���� ������ ������ �����ؾ���, �����ִ� ��� �͵��� �ʿ��� class�̴�. 
*/

class User final :  public Creature
{
public:
	// ������ EnterWorld �� ���� ��ġ ������ 
	static constexpr float userSpawn = 100.f; // ���� ������ �ʿ��� 

public:
	//User ���� ����ȭ 
	// Actor Job�� ����Ϸ��� User�� Job�� �������ִ� ���� �´�

	//Component ��ݵ��̸� User�� Component ����� �ʿ��ϴ� 
	void SetComponents();

	//���� ���� ���� 
	bool EnterWorldStart(); 
public:
	//���� ����, ���� ���� 
	void OnEnterWorld();
	void OnLeaveWorld();

	//Warp�� ����

private:
	// Spawn, Despawn..
	// 

	// User::OnTickSaveData
	// User::LeaveWorldStart.
	// User::OnDie
	// �����Ҷ���? �� ? 
	void UpdateUserDBData();

};

