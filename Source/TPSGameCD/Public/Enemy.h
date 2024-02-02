// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class TPSGAMECD_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//mesh 설정
	
	//pc: EnemyFSMComp를 컴포넌트로 갖고 싶다. 

	UPROPERTY(EditAnywhere)
	class UEnemyFSmComp* enemyFSM;

public:
	void OnMyTakeDamage( int damage );

	UPROPERTY(EditAnywhere)
	int32 HP = 10;
};
