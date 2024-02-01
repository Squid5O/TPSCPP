// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSmComp.h"
#include "Enemy.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEnemyFSmComp::UEnemyFSmComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSmComp::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<AEnemy>( GetOwner() );  // cast bpcomp owner(enemy) 
		
	// ...
	
}


// Called every frame
void UEnemyFSmComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	switch (state)
	{
	case EEnemyState::IDLE:   TickIdle();    break;
	case EEnemyState::MOVE:   TickMove();	 break;
	case EEnemyState::ATTACk: TickAttack();  break;
	case EEnemyState::DAMAGE: TickDamage();  break;
	case EEnemyState::DIE:    TickDie();     break;
	}
}

//pc:Idle: 주인공을 찾아서 목적지를 기억하고 싶다. 목적지가 있다면 이동 상태로 전의
void UEnemyFSmComp::TickIdle()
{
	//1. 주인공을 찾아서 목적지로 기억하고 싶다.
	//target = GetWorld()->GetFirstPlayerController()->GetPawn(); 얘도 됌
	target = UGameplayStatics::GetPlayerCharacter( GetWorld() , 0 );  // 첫번째 플레이어
	//2. 만약 목적지가 있따면
	if (target)
	{
		//3. 이동상태로 전이하고 싶다. - > state의 값을 move로 바꾸고 싶다. 우효!
		state = EEnemyState::MOVE;
	}

	
}


//pc: Move : 목적지를 향해서 이동하고 싶다. 만약 목적지와의 거리가 3m 이내라면 공격상태로 전이하고 싶다.
void UEnemyFSmComp::TickMove()
{
	// pc; 01 목적지를 향하는 방향을 구하고 싶다.
	FVector dir = target->GetActorLocation() - me->GetActorLocation();
	//1. me가 그 방향으로 이동하게 하고 싶다.
	me->AddMovementInput( dir.GetSafeNormal() ); //dir.Normalize(); 대신 사용
	//2. 목적지와의 거리를 기억하고 싶다.
	float dist = FVector::Dist( target->GetActorLocation() , me->GetActorLocation() );
	//float dist = target->GetDistanceTo(me);  // dist 계산 포함
	if (dist < AttackDistance)
	{
		state = EEnemyState::ATTACk;
	}
	

}


//pc : Attack : 공격을 하고 2초 대기했다가 다시 공격하고 싶다. 만약 공격을 하려고 할때 목적지와의 거리를 3m를 초과한다면 이동상태로 전이하고 싶어
void UEnemyFSmComp::TickAttack()
{
}

void UEnemyFSmComp::TickDamage()
{
}

void UEnemyFSmComp::TickDie()
{
}

