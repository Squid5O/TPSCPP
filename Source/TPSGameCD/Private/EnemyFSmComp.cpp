// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSmComp.h"
#include "Enemy.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "EnmeyAnime.h"

// Sets default values for this component's properties
UEnemyFSmComp::UEnemyFSmComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSmComp::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<AEnemy>( GetOwner() );  // cast bpcomp owner(enemy) 
		
	enemyAnim = Cast<UEnmeyAnime>(me->GetMesh()->GetAnimInstance());
	
}


// Called every frame
void UEnemyFSmComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	switch (state)
	{
	case EEnemyState::IDLE:   TickIdle();    break;
	case EEnemyState::MOVE:   TickMove();	 break;
	case EEnemyState::ATTACk: TickAttack();  break;
	case EEnemyState::DAMAGE: TickDamage();  break;
	case EEnemyState::DIE:    TickDie();     break;
	}
}

//pc:Idle: 주인공을 찾아서 목적지를 기억하고 싶다. 목적지가 있다면 이동 상태로 전의
void UEnemyFSmComp::TickIdle()
{
	//1. 주인공을 찾아서 목적지로 기억하고 싶다.
	//target = GetWorld()->GetFirstPlayerController()->GetPawn(); 얘도 됌
	target = UGameplayStatics::GetPlayerCharacter( GetWorld() , 0 );  // 첫번째 플레이어
	//2. 만약 목적지가 있따면
	if (target)
	{
		//3. 이동상태로 전이하고 싶다. - > state의 값을 move로 바꾸고 싶다. 우효!
	//	state = EEnemyState::MOVE;
		SetState( EEnemyState::MOVE );
	}

	
}


//pc: Move : 목적지를 향해서 이동하고 싶다. 만약 목적지와의 거리가 3m 이내라면 공격상태로 전이하고 싶다.
void UEnemyFSmComp::TickMove()
{
	// pc; 01 목적지를 향하는 방향을 구하고 싶다.
	FVector dir = target->GetActorLocation() - me->GetActorLocation();
	//1. me가 그 방향으로 이동하게 하고 싶다.
	me->AddMovementInput( dir.GetSafeNormal() ); //dir.Normalize(); 대신 사용
	//2. 목적지와의 거리를 기억하고 싶다.
	float dist = FVector::Dist( target->GetActorLocation() , me->GetActorLocation() );
	//float dist = target->GetDistanceTo(me);  // dist 계산 포함
	if (dist < AttackDistance)
	{
		//state = EEnemyState::ATTACk;
		SetState( EEnemyState::ATTACk );
	//	enemyAnim->bAttack = true;
	}
	else
	{
		enemyAnim->bAttack = true;
	}
	

}


//pc : Attack : 공격을 하고 2초 대기했다가 다시 공격하고 싶다. 만약 공격을 하려고 할때 목적지와의 거리를 3m를 초과한다면 이동상태로 전이하고 싶어
void UEnemyFSmComp::TickAttack()
{
	//1. 시간이 흐르다가   persudo code
	currentTIme += GetWorld()->GetDeltaSeconds();  //초
	//2. 만약 현재시간이 2초(공격대기시간)을 초과하면  
	// 현재시간이 > 공격대시간을 초과하면
	if (currentTIme > attackWaitTime)   // 2초 임
	{
		currentTIme = 0; //3. 현재시간을 초기화 하고 싶다.
		
		//float distance = target->GetDistanceTo( me ); 간단구현 AACTOR
			
		float distance = UKismetMathLibrary::Vector_Distance2D(target->GetActorLocation() , me->GetActorLocation());
			
		//4. 목적지와의 거리를 재고
		if (distance >AttackDistance) //5. 만약 그 거리가 공격가능거리를 초과한다면
		{
			//6. 이동상태로 전이하고 싶다. 
			SetState( EEnemyState::MOVE );
			//state = EEnemyState::MOVE;
		}
		else // 7. 그렇지 않다면
		{
			//8. 공격을 하고 싶다.
			UE_LOG( LogTemp , Warning , TEXT( "Enemy->playerAttack!!" ) );
			GEngine->AddOnScreenDebugMessage( -1 , 3 , FColor::Cyan , TEXT( "Enemy-playerAttack!!!" ));
		}
	}
}

void UEnemyFSmComp::TickDamage()
{
	////시간이 흐르다가
	//currentTIme += GetWorld()->GetDeltaSeconds();
	//// 현재시간이 1초가 되면
	//if(currentTIme > 1)
	//{
	//// 이동상태로 전이하고 싶다. 
	//	SetState( EEnemyState::MOVE );
	//	me->GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics);
	//	//currentTIme = 0;
	//}
}

void UEnemyFSmComp::TickDie()
{
	//만약 죽음 애니메이션이 끝났다면 
	if (false == isDieDone)
		return;

	//아래로 이동
	float deltaTime = GetWorld()->GetDeltaSeconds();
	FVector P0 = me->GetActorLocation();
	FVector velocity = FVector::DownVector * 500;
	me->SetActorLocation( P0 + velocity * deltaTime );
	
	//현재 시간이 지난지 2초가 되면 스스로 파괴하고 싶다.
	currentTIme += deltaTime;
	//2초가 되면 
	if (currentTIme > 2)
	{
		me->Destroy();
	}
}

void UEnemyFSmComp::doDamageEnd()
{
// 이동상태로 전이하고 싶다. 
	SetState( EEnemyState::MOVE );
	me->GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics);
	//currenttime = 0;
}

void UEnemyFSmComp::TakeDamage( int damage )
{
	//체력을 damage 만큼 줄이고싶다.
	
//	me->HP -= damage;  마이너스로 넘어감
	if ((me->HP -= damage) < 0)
	{
		me->HP = 0;
	}
	//만약 체력이 0보다 크다면 Damage 상태로 전이하고 싶다.
	if (me->HP > 0)
	{
		SetState( EEnemyState::DAMAGE );
		//pc: 데이지 애니메이션 몽타주 재생 but 랜덤
		int index = FMath::RandRange( 0 , 1 );
		FString sectionName = FString::Printf( TEXT( "Damage%d" ) , index );

		me->PlayAnimMontage( enemyMontage, 1, FName(*sectionName));
	}else
	//그렇지 않다면 ( 체력이 0 이하 라면)
	{
		SetState( EEnemyState::DIE );
		//죽음 애니메이션 몽타주 재생
		me->PlayAnimMontage( enemyMontage, 1, TEXT("Die"));
		isDieDone = false;
	}
	// die 상태로 전이하고 싶다.


	//me->Destroy(); 코드 확인용 임시
	//state = EEnemyState::DAMAGE;
	//currentTIme = 0;
	me->GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

void UEnemyFSmComp::SetState( EEnemyState next )
{
	state = next;
	currentTIme = 0;
}

