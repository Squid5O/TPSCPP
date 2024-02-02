// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSPlayer.generated.h"

UCLASS()
class TPSGAMECD_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;

	UPROPERTY( EditAnywhere )
	class USpringArmComponent* springArmComp;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	class UCameraComponent* cameraComp;

	FVector direction;

	void Move();

	void OnAxisVertical( float value );
	void OnAxisHorizontal( float value );

	void OnAxisTurnYaw( float value );
	void OnAxisLookupPitch( float value );

	void onActionJump();

	//pc: 총 매쉬를 추가하고싶당
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	class USkeletalMeshComponent* gunMeshComp;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	class UStaticMeshComponent* sniperMeshComp;

	//pc: 총알 공장을 만들고싶다.

	//pc: 마우스 왼쪽 버튼을 누르면 총알공장에서 총알을 만들어서 
	 //   ㄴFirePosition 소켓에 배치하고 싶당.

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABulletActor> bulletFactory;

	void onActionFire();

	void OnActionChooseGrenadeGun();
	void OnActionChooseSniperGun();

	void Zoom();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> crossHairFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> sniperScorpFactory;

	UPROPERTY(EditAnywhere)
	class UUserWidget* crossHairUI;

	UPROPERTY(EditAnywhere)
	class UUserWidget* sniperScorpUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float targetFOV = 90;
/*
	FORCEINLINE void OnActionZoomIn() { targetFOV = 30; }
	FORCEINLINE void onAcitonZoomOut() { targetFOV = 90; }
	*/
	void OnActionZoomIn();

	void OnAcitonZoomOut();

	/// <summary>
	/// // true: sniper, false = grenade
	/// </summary>
	bool bChooseSniperGun = false; 

	//sniper 총으로 쐈을때 부딪힌 곳에 총알 자국을 남기고 싶다.
	UPROPERTY(EditAnywhere)
	class UParticleSystem* expVFX;
};
