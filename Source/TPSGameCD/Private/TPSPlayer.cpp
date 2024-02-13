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
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SceneComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Enemy.h"
#include "EnemyFSmComp.h"

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
	gunMeshComp->SetupAttachment( GetMesh() , TEXT("hand_rSocket"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempGunMesh( 
		TEXT( "/Script/Engine.SkeletalMesh'/Game/models/FPWeapon/Mesh/SK_FPGun.SK_FPGun'" ) );
	if (tempGunMesh.Succeeded()) {
		gunMeshComp->SetSkeletalMesh( tempGunMesh.Object );
		gunMeshComp->SetRelativeLocation( FVector( 0 , 300 , 200 ) );
	}

	//pc: snipeMeshComp를 생성하고 싶다.
	//pc: staticMesh를 적용해서 매쉬에 붙이고 싶다.
	sniperMeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "sniperMeshComp" ) );
	sniperMeshComp->SetupAttachment( GetMesh() , TEXT( "hand_rSocket" ) );
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

	crossHairUI = CreateWidget( GetWorld() , crossHairFactory );
	crossHairUI->AddToViewport();

	sniperScorpUI = CreateWidget( GetWorld() , sniperScorpFactory );
	sniperScorpUI->AddToViewport();

	//pc:태어날 때 기본 crossHairUI만 보이게 하고 싶다.


	//총을 교체하면 ZoomOut을 하고싶다.

		//pc:태어날 때 기본 crossHairUI만 보이게 하고 싶다.
	sniperScorpUI->SetVisibility( ESlateVisibility::Hidden );

	OnActionChooseGrenadeGun();
	
}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();

	Zoom();

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

	PlayerInputComponent->BindAction( TEXT( "Zoom" ) , IE_Pressed , this, &ATPSPlayer::OnActionZoomIn);
	PlayerInputComponent->BindAction( TEXT( "Zoom" ) , IE_Released, this , &ATPSPlayer::OnAcitonZoomOut );

	PlayerInputComponent->BindAction( TEXT( "ActionRun" ) , IE_Pressed , this , &ATPSPlayer::OnActionRunPressed );
	PlayerInputComponent->BindAction( TEXT( "ActionRun" ) , IE_Released , this , &ATPSPlayer::OnActionRunReleased );

	PlayerInputComponent->BindAction( TEXT( "ActionCrouch" ) , IE_Pressed , this , &ATPSPlayer::OnActionCrouched );

	PlayerInputComponent->BindAction( TEXT( "DiveRoll" ) , IE_Pressed , this , &ATPSPlayer::OnActionDiveRoll );
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
	//총 소리를 내고 싶다.
	UGameplayStatics::PlaySound2D( GetWorld() , fireSFX );
	//움찔 애니메이션을 넣고 싶다.
	this->PlayAnimMontage( fireMontage );  
	//ACharacter::PlayAnimMontage = 얘 자체가 Chartacter라 안써두됌 ,, this 생략 가능

	// bChooseSniperGun ture false로 나가는거 다르게
	if(bChooseSniperGun==false){
	FTransform t = gunMeshComp->GetSocketTransform(TEXT("FirePosition"));
	GetWorld()->SpawnActor<ABulletActor>(bulletFactory, t);
	}
	else {
		FHitResult outHit;
	//	FVector start = cameraComp->GetComponentLocation();
		FVector start = cameraComp->K2_GetComponentLocation();
		FVector end = start + cameraComp->GetForwardVector()*100000;
		FCollisionQueryParams params;
		params.AddIgnoredActor( this );
		bool bReturnValue = GetWorld()->LineTraceSingleByChannel(
			outHit , start , end , ECollisionChannel::ECC_Visibility , params );
		//만약 부딪힌 것이 있따면.
		if (bReturnValue) {
		//	DrawDebugLine( GetWorld() , outHit.TraceStart , outHit.ImpactPoint , FColor::Red, false, 10);
			//부딪힌 컴포넌트를 가져와서 
			UPrimitiveComponent* hitComp = outHit.GetComponent();
			//만약 컴포넌트가 있다. 그리고 컴포넌트의 물리가 켜져있다면.
			if (hitComp && hitComp->IsSimulatingPhysics()) {
				//그 컴포넌트에게 힘을 가하고 싶다.
				FVector dir = end - start;
				//hitComp->AddForce( -outHit.ImpactNormal * 500000 * hitComp->GetMass() );
				hitComp->AddForce(dir.GetSafeNormal() * 500000 * hitComp->GetMass() );
			}

			//pc: 부짖힌 곳에 expVFX를 생성해서 배치하고 싶다.
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , expVFX , outHit.ImpactPoint );

			//pc: 만약 부딪힌 것이 AEnemy라면
			//적에게 데미지 1점을 주고 싶다.
			AEnemy* enemy = Cast<AEnemy>( outHit.GetActor() );

			  // check( enemy ); // 어썰트. true 아닐 경우 에러 뱉음
				
			if(enemy)
			{ 
				auto fsm = Cast<UEnemyFSmComp>( enemy->GetDefaultSubobjectByName( TEXT( "enemyFSM" ) ) );
				fsm->TakeDamage( 5 );
			//	enemy->OnMyTakeDamage( 1 ); 간단 구현. 위는 객체지향구현
			}
		}
		else
		{
		//	DrawDebugLine( GetWorld() , start , end , FColor::Blue , false , 10 );
		}

	}
}

void ATPSPlayer::OnActionChooseGrenadeGun()
{
	bChooseSniperGun = false;
	//pc : 유탄총을 보이게, 스나이퍼를 안보이게
	gunMeshComp->SetVisibility( true );
	sniperMeshComp->SetVisibility( false );
}

void ATPSPlayer::OnActionChooseSniperGun()
{
	bChooseSniperGun = true;
	//pc: 유탄총을 안보이게 , 스나이퍼를 보이게 
	gunMeshComp->SetVisibility( false );
	sniperMeshComp->SetVisibility( true );
	OnAcitonZoomOut();
}

void ATPSPlayer::Zoom()
{
	//pc: 선형보간을 사용해 현재 FOV를 targetFOV 값에 근접하게 하고싶다.
	cameraComp->FieldOfView = FMath::Lerp<float>( 
	cameraComp->FieldOfView , targetFOV , GetWorld()->GetDeltaSeconds() * 10
	);														//10 곱하면 대략  0.1
	//	cameraComp->FieldOfView , targetFOV , 0.1f 
	
}

void ATPSPlayer::OnActionZoomIn()
{
	// 만약 스나이퍼가 손에 쥔 총이 스나이퍼가 안니라면 함수를 바로 종료하고 싶다.
	if (false == bChooseSniperGun)
	{
		return;
	}
	 //if(!bChooseSniperGun)return;  한줄 가능
	 // 
	//pc:ZoomIn을 하면 crossHairUI를 보이지 않게, sniperUI 보이게 하고 싶다.
	crossHairUI->SetVisibility( ESlateVisibility::Hidden );
	sniperScorpUI->SetVisibility( ESlateVisibility::Visible);
	targetFOV = 30;
}

void ATPSPlayer::OnAcitonZoomOut()
{
	crossHairUI->SetVisibility( ESlateVisibility::Visible );
	sniperScorpUI->SetVisibility( ESlateVisibility::Hidden);
	//pc:ZoomOut을 하면 CroessHairUI을 보이게, sniperUI를 보이지 않게 하고 싶다.
	targetFOV = 90;
}

void ATPSPlayer::OnActionRunPressed()
{
	// 걷기의 최대 speed를 1200으로 하고 싶다.
	GetCharacterMovement()->MaxWalkSpeed = 1200;
}

void ATPSPlayer::OnActionRunReleased()
{
	// 걷기의 최대 speed를 600으로 하고 싶다.
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void ATPSPlayer::OnActionCrouched()
{
	if (isCrouched) 
	{
		//이미 쪼그려 있다면 서고 싶다.
		GetCharacterMovement()->UnCrouch();
		isCrouched = false;
	}
	else
	{
		//서있다면 쪼그리고 싶다.
		GetCharacterMovement()->Crouch();
		isCrouched = true;
	}

}

//int64 milliseconds ; 전역변수

void ATPSPlayer::OnActionDiveRoll()
{
	//액션을 하고 0.8초 동안은 막고싶다.
	double Seconds = FPlatformTime::Seconds();
	int64 curMilSec = static_cast<int64>(Seconds * 1000);


	//정적변수   - 딱 하나만 만듬?
//	static int64 milliseconds;

	//만약 현재시간과 기억하고 있던 시간의 차이가 800m/s 을 초과한다면 몽타주를 재생하고 싶다.

	if(curMilSec - mllisecnds > 800)
	{
		mllisecnds = curMilSec;
		this->PlayAnimMontage( diveMontage );
	}
}

