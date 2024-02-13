// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyFSmComp.h"
#include "EnmeyAnime.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAMECD_API UEnmeyAnime : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation( float DeltaSeconds )
		override;

	UPROPERTY()
	class UEnemyFSmComp* enemyFSM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemyState state;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bAttack;

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_DamageEnd();

	UFUNCTION()
	void AnimNotify_DieEnd();
};
