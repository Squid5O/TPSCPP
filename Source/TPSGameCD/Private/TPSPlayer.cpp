// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayer.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMesh.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Character.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "BulletActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/UMG/Public/Blueprint/UserWidget.h"

// Sets default values
ATPSPlayer::ATPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	////springArmComp 생성해서 Root에 붙이고 싶다.
	//// location (x=0.000, y= 70.00, z = 90.000)
	////use pawn control Rotation

	//springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springRootArm"));
	//this->SetRootComponent( springArmComp );
	////cameraComp 생성해서 springArmComp에 붙이고 싶다.

	//cameraComp = CreateDefaultSubobject<UCameraComponent>( TEXT( "cameraComp" ) );
	//cameraComp -> SetRootCom


	//PC : springArmComp 를 생성해서 Root에 붙이고 싶다.
	springArmComp = CreateDefaultSubobject<USpringArmComponent>( TEXT( "springArmComp" ) );
	springArmComp->SetupAttachment( RootComponent );
	//loc : x 0 ,y 70 ,z 90
	springArmComp->SetWorldLocation(FVector(0, 70, 90));
	//PC : use Pawn Control Roataion을 true로 하고 싶다.
	springArmComp->bUsePawnControlRotation = true;

	//PC : cameraComp를 생성해서 springArmComp에 붙이고 싶다.
	cameraComp = CreateDefaultSubobject<UCameraComponent>( TEXT( "cameraComp" ) );
	cameraComp->SetupAttachment( springArmComp );

	//PC : mesh를 로드해서 적용하고 싶다.
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));
	//PC : 성공했다면
	if (tempMesh.Succeeded()) {
		//PC : mesh에 적용하고 싶다.
		GetMesh()->SetSkeletalMesh( tempMesh.Object );
		GetMesh()->SetRelativeLocationAndRotation( FVector( 0 , 0 , -90 ) , FRotator( 0 , -90 , 0 ) );
	}

	bUseControllerRotationYaw = true;
	springArmComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false; 

	//pc: gunMesh Comp를 생성해서 로딩도 하고 배치학 싶다. mesh에 attach
	gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "gunMeshComp" ) );
	gunMeshComp->SetupAttachment( GetMesh() );

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempGunMesh( 
		TEXT( "/Script/Engine.SkeletalMesh'/Game/models/FPWeapon/Mesh/SK_FPGun.SK_FPGun'" ) );
	if (tempGunMesh.Succeeded()) {
		gunMeshComp->SetSkeletalMesh( tempGunMesh.Object );
		gunMeshComp->SetRelativeLocation( FVector( 0 , 300 , 200 ) );
	}

	//pc: snipeMeshComp를 생성하고 싶다.
	//pc: staticMesh를 적용해서 매쉬에 붙이고 싶다.
	sniperMeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "sniperMeshComp" ) );
	sniperMeshComp->SetupAttachment( GetMesh() );
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempSuniperMesh( 
		TEXT( "/Script/Engine.StaticMesh'/Game/models/SniperGun/sniper1.sniper1'" ) );
	if (tempSuniperMesh.Succeeded()) {
		sniperMeshComp->SetStaticMesh( tempSuniperMesh.Object);
		sniperMeshComp->SetRelativeLocation( FVector( 0 , 80 , 130 ) );
		sniperMeshComp->SetWorldScale3D( FVector( 0.2f ));

	}

	gunMeshComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	sniperMeshComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay()
{
	Super::BeginPlay();

	//crossHairUI = CreateWidget( GetWorld() , crossHairFactory );
	//crossHairUI->AddToViewport();

	//sniperScorpUI = CreateWidget( GetWorld() , sniperScorpFactory );
	//sniperScorpUI->AddToViewport();

	OnActionChooseGrenadeGun();
	
}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();

}

// Called to bind functionality to input
void ATPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PC : 가로축, 세로축, 점프에 대한 함수를 바인딩 하고 싶다. 
		//(주어 - >기능(필요한값)
	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &ATPSPlayer::OnAxisHorizontal );

	PlayerInputComponent->BindAxis(TEXT("Move Right / Left"), this, &ATPSPlayer::OnAxisVertical );
	
	PlayerInputComponent->BindAxis(TEXT( "Turn Right / Left Mouse" ) , this , &ATPSPlayer::OnAxisTurnYaw );

	PlayerInputComponent->BindAxis(TEXT( "Look Up / Down Mouse" ) , this , &ATPSPlayer::OnAxisLookupPitch );

	PlayerInputComponent->BindAction( TEXT( "Jump" ) , IE_Pressed , this , &ATPSPlayer::onActionJump );

	PlayerInputComponent->BindAction( TEXT( "FIRE" ) , IE_Pressed , this , &ATPSPlayer::onActionFire );

	PlayerInputComponent->BindAction( TEXT( "chooseGrenadeGun" ) , IE_Pressed , this , &ATPSPlayer::OnActionChooseGrenadeGun );

	PlayerInputComponent->BindAction( TEXT( "chooseShinperGun" ) , IE_Pressed , this , &ATPSPlayer::OnActionChooseSniperGun );
}

void ATPSPlayer::Move()
{
	///FTransform trnas( direction );
	FTransform trnas = cameraComp->GetComponentTransform();  // 카메라도 가능
	//FTransform trnas = GetActorTransform();
	AddMovementInput( trnas.TransformVector(direction));
}

void ATPSPlayer::OnAxisVertical( float value )
{
	direction.X = value;
}

void ATPSPlayer::OnAxisHorizontal( float value )
{
	direction.Y = value;
}


void ATPSPlayer::OnAxisTurnYaw( float value )
{
	AddControllerYawInput( value );
}


void ATPSPlayer::OnAxisLookupPitch( float value )
{
	AddControllerPitchInput( value );
}

void ATPSPlayer::onActionJump()
{
	ACharacter::Jump();
}

void ATPSPlayer::onActionFire()
{
	FTransform t = gunMeshComp->GetSocketTransform(TEXT("FirePosition"));
	GetWorld()->SpawnActor<ABulletActor>(bulletFactory, t);
}

void ATPSPlayer::OnActionChooseGrenadeGun()
{
	//pc : 유탄총을 보이게, 스나이퍼를 안보이게
	gunMeshComp->SetVisibility( true );
	sniperMeshComp->SetVisibility( false );
}

void ATPSPlayer::OnActionChooseSniperGun()
{
	//pc: 유탄총을 안보이게 , 스나이퍼를 보이게 
	gunMeshComp->SetVisibility( false );
	sniperMeshComp->SetVisibility( true );
}

