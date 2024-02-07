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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemyState state;
};
