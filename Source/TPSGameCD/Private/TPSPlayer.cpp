// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayer.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h"

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




}

// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
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

