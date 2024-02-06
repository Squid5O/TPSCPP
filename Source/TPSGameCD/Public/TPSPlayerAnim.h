// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPSPlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAMECD_API UTPSPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isInAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isCrouchedD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Dirction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ptich;
};
