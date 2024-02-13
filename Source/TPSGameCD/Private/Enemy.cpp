// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyFSmComp.h"
#include "../../../../../../../Source/Runtime/UMG/Public/Components/WidgetComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//mesh를 설정하고 싶다
	//fsm컴포넌트를 생성하고 싶다
	enemyFSM = CreateDefaultSubobject<UEnemyFSmComp>( TEXT( "enemyFSM" ));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh( TEXT( "/Script/Engine.SkeletalMesh'/Game/models/Enemy/Model/vampire_a_lusth.vampire_a_lusth'" ) );
	if (tempMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh( tempMesh.Object );
		GetMesh()->SetRelativeLocationAndRotation(FVector( 0 , 0 , -90 ) , FRotator( 0 , -90 , 0 ) );

		GetMesh()->SetRelativeScale3D( FVector( 0.8f ));
	}

	////healthUI를 만들어서 루트에 부팅고 싶다.
	//healthUI = CreateDefaultSubobject<UWidgetComponent>( TEXT( 'healthUI' ) );
	//healthUI->SetupAttachment( RootComponent );
	//healthUI->SetRelativeLocation( FVector( 0 , 0 , 100 ) );
	////LOc : 0,0.100
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnMyTakeDamage( int damage )
{
	enemyFSM->TakeDamage( damage );
}

