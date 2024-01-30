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
	moveComp->SetUpdatedComponent( sphereComp );

	//pc: speed 설정, 바운드 설정
	moveComp->InitialSpeed = 2000.f;
	moveComp->MaxSpeed = 2000.f;
	moveComp->bShouldBounce = true;

	sphereComp->SetCollisionProfileName( TEXT( "BLockAll" ) );
	meshComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );

	//pc: 메시의 크기를 25 로 하고 싶다
	meshComp->SetWorldScale3D(FVector(0.25f));
	//pc: 충돌체 반지름을 12.5 하고싶당
	sphereComp->SetSphereRadius(12.5f);

	//총알 액터의 수명을 5초로 하고 싶다
	SetLifeSpan( 5 );
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();

	//pc: 총알 액터의 숨여을 5초로 하고 싶다. - 타이머를 이용해서
	FTimerHandle timeHandle;
	//GetWorld()->GetTimerManager().SetTimer(timeHandle, this, &ABulletActor::AutoDestroy, 1, false);  얘또됨

	GetWorld()->GetTimerManager().SetTimer( timeHandle , 
		FTimerDelegate::CreateLambda( [this]()->void {this->Destroy(); } ) , 1 , false );


	/*
	auto lambdaFun = [this]( int a , int b ) {};

	//람다(ladbda)식, 무명함수(어노니머스 평션)
	//[캡처대상](매개변수)->반환자료형{to do};
	//print(1)
	auto lambdaFun = [this]( int a , int b )->int {
		return a + b;
		};

	int result = lambdaFun( 10 , 20 );*/
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

