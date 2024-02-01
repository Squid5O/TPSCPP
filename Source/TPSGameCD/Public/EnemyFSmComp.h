// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSmComp.generated.h"


UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	IDLE,
	MOVE,
	ATTACk,
	DAMAGE,
	DIE,
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSGAMECD_API UEnemyFSmComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSmComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//1. Idle: 주인공을 찾아서 목적지를 기억하고 싶다. 목적지가 있다면 이동 상태로 전의;
	//2. Move : 목적지를 향해서 이동하고 싶다. 만약 목적지와의 거리가 3m 이내라면 공격상태로 전이하고 싶다.
	//3. Attack : 공격을 하고 2초 대기했다가 다시 공격하고 싶다. 만약 공격을 하려고 할때 목적지와의 거리를 3m를 초과한다면 이동상태로 전이하고 싶어

		
	UPROPERTY( EditAnywhere )
	EEnemyState state;

	UPROPERTY( EditAnywhere )
	float AttackDistance = 200;

	UPROPERTY( EditAnywhere )
	//class AActor* target;
	AActor* target;

	UPROPERTY( EditAnywhere )
	class AEnemy* me;


private:
	void TickIdle();
	void TickMove();
	void TickAttack();
	void TickDamage();
	void TickDie();
};
