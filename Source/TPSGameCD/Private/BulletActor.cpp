// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// sphereComp를 루트로
	sphereComp = CreateDefaultSubobject<USphereComponent>( TEXT( "sphereComp" ) );
	SetRootComponent( sphereComp );

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "meshComp" ) );
	meshComp->SetupAttachment( RootComponent );

	moveComp = CreateDefaultSubobject<UProjectileMovementComponent>( TEXT( "moveComp" ) );

	//pc: speed 설정, 바운드 설정
	moveComp->InitialSpeed = 2000.f;
	moveComp->MaxSpeed = 2000.f;
	moveComp->bShouldBounce = true;

	sphereComp->SetCollisionProfileName( TEXT( "BLockAll" ) );
	meshComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );

	//총알 액터의 수명을 5초로 하고 싶다
	SetLifeSpan( 5 );
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();


	moveComp->SetUpdatedComponent( sphereComp );
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

