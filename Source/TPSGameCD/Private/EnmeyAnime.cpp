// Fill out your copyright notice in the Description page of Project Settings.


#include "EnmeyAnime.h"
#include "Enemy.h"
#include "EnemyFSmComp.h"

void UEnmeyAnime::NativeInitializeAnimation()
{
	auto owner = TryGetPawnOwner();
	if (nullptr == owner) {
		return;
	}

	AEnemy* me = Cast<AEnemy>( owner );
	enemyFSM = me->enemyFSM;
}

void UEnmeyAnime::NativeThreadSafeUpdateAnimation( float DeltaSeconds )
{
	if (nullptr == enemyFSM)
		return;

	state = enemyFSM->state;
}

void UEnmeyAnime::AnimNotify_AttackEnd()
{
///	UE_LOG(LogTemp, Warning, TEXT)
	bAttack = false;
}

void UEnmeyAnime::AnimNotify_DamageEnd()
{
	//enemyFSM->SetState( (EEnemyState::MOVE) );
	enemyFSM->doDamageEnd();

}

void UEnmeyAnime::AnimNotify_DieEnd()
{
	enemyFSM->isDieDone = true;
}
