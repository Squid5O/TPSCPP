# TPSCPP
 tps
-----------------
TPS 게임 만들기

CD 창동!  crate 

empty 레벨 

플레인 0 0 0  location

scale 50	50  50

all 
ㄴContent
   ㄴ Maps  = > GameMap 저장

레이아웃 윈도우 UE4 클래식 좋음 

Env.Light Mixer 
ㄴcreate Sky Light _ 하늘 생성

New C++ 클래스 만들기
ㄴ game mode base 


빌드CS는 건들지마라
ㄴ헤더는 퍼블릭(공개 선언부/)
ㄴ소스는 프라이빗 (코드 실행부)

삭제하고 제네레이트 _~_~~_~_~_~_~_~_~_

F5 = 실행~

프로젝트 셋팅 맵샛팅 모드 - 기본 맵 수정

x가 앞을 향하도록 해라 _ 맵 만들떄

캐릭터->폰->액터

C++ 만들고 ㅡ블루프린트 만들어라~~_~_~_~_

프로젝트 셋팅  _ 월드 셋팅에서 게임모드베이스 설정해랏
 
스캘래톤 매쉬 = 리그정보를 가질 수 있는 mesh

캐릭터 무브먼트는 계층구조에 포함 되지 않음

BP slayer
 ㄴ casule
      ㄴ arrow 
         ㄴ 스캘래톤 mesh
---------------------------------
charater movents 

SpringArm

socket

캐릭터 무브먼트 = 워킹

add 피쳐 컨텐츠. -> 3rd Person -> 폴더 만들어줌

input- action

x 앞
y 옆
z 위

카메라랑 몸 따로 회전 가능

Orient Rotation to Movement

절대 방향

/////////////////////////////////////////////////////////---------------////////////////////// 1_26 수업

q

ohmygod - 인벤토리

--1.10 액터 컴포넌트를 만든후 캐릭터에 넣으면 캐릭터 에 로직을 짤 필요 없이 액터 컴포넌트에 쓴 블루프린트 로직을 캐릭터에서 그대로 사용 가능.

프로젝트 셋팅- 인풋 하지만 하드코딩 tab

-------------------////////////////////////1.29

x 앞 pitch 
y 옆 roll
z 위 Yaw

앞뒤양옆 움직이면서 카메라 회전에 맞춰 돌아가게 해야함

Begin Object Class=/Script/BlueprintGraph.K2Node_CallFunction Name="K2Node_CallFunction_4" ExportPath="/Script/BlueprintGraph.K2Node_CallFunction'/Game/Blueprints/BP_TPSPlayer.BP_TPSPlayer:EventGraph.K2Node_CallFunction_4'"
   bIsPureFunc=True
   bIsConstFunc=True
   FunctionReference=(MemberParent="/Script/CoreUObject.Class'/Script/Engine.SceneComponent'",MemberName="GetRelativeTransform")
   NodePosX=-704
   NodePosY=528
   NodeGuid=2F052CCB400FD8916A788D9A75811AB6
   CustomProperties Pin (PinId=29F78D0C43DF5644A43532952143C092,PinName="self",PinFriendlyName=NSLOCTEXT("K2Node", "Target", "Target"),PinToolTip="Target\nScene Component Object Reference",PinType.PinCategory="object",PinType.PinSubCategory="",PinType.PinSubCategoryObject="/Script/CoreUObject.Class'/Script/Engine.SceneComponent'",PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PinType.bSerializeAsSinglePrecisionFloat=False,LinkedTo=(K2Node_VariableGet_0 C565AE434067940A00A66E80B4701959,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
   CustomProperties Pin (PinId=F99202584D239A740120B28D2285A7C5,PinName="ReturnValue",PinToolTip="Return Value\nTransform\n\nReturns the transform of the component relative to its parent",Direction="EGPD_Output",PinType.PinCategory="struct",PinType.PinSubCategory="",PinType.PinSubCategoryObject="/Script/CoreUObject.ScriptStruct'/Script/CoreUObject.Transform'",PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PinType.bSerializeAsSinglePrecisionFloat=False,PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
End Object
ㄴ 회전값 가져옴

1.컨트롤 입력 받음
2.포세스한 대상한테만 밀어넣음
3.본체 카메라에 밀어넣음??
ㄴ orient Rotation to Movment 하면 한방에?

Jump는 character 상속
Movenvents Pawn 부터 가능

w 오른쪽
s 왼쪽
d 앞
a 뒤

https://github.com/deadbydaylightNO/DBD

https://github.com/deadbydaylightNO/DBD
/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'

pritave 은 못쓴다. return을 찾아라

projctile movent

/Script/Engine.SkeletalMesh'/Game/models/FPWeapon/Mesh/SK_FPGun.SK_FPGun'
컴포넌트와 매쉬는 다르다. 변수명 구분 확실하게!

스캘래톤은 피식스 에섹이 있어야 충돌 가능 <-> mesh랑 다름 

FirePosition d

////---1.30 수업
jump max count

defualt land movenent

newObject<>() = createdefaultsubobject<>() 
뉴오브젝트는 정적? 고수가되면 써라 

리셋 버튼이 있는건 C++로 적용시켜랏

Uclass* 하면 다 튀어나오기 때문에 TSubclassOf<class ABulletActor 형식 지정이 좋음

timer 쓸려면 
GetWorld() -> GetTimerManager().SetTimer 
getworld 는 포인터 gettimeManger 레퍼런스  ->  .

C++은 자유도가 높다 void 를 아무대나 박아도 쓸수가 있다.- 전역함수

	//람다(ladbda)식, 무명함수(어노니머스 평션)
	//[캡처대상](매개변수)->반환자료형{to do};
	auto lambdaFun = [this]( int a , int b )->int {
		return a + b;
		};

	int result = lambdaFun( 10 , 20 );

reutrn 전에 리졸트 부터 나올수도

람다 캡처

디퓨즈 - 베이스 컬러

/Script/Engine.StaticMesh'/Game/models/SniperGun/sniper1.sniper1'

chooseGrenadeGun
chooseShinperGun

umg 수정해

---------1.30 끝


1--.1.31 시작

C++ lerp 함수

상속성 inhaertied

선형보간

FORCEINLINE 쓰면 헤더에서 기능 작성 가능

summary 기능 개이득

line trace

actor comp
scene comp
primitive comp

-ImpactNormal    = 기능같음
.GetSafeNormal()  <- 얘는 원본 유지함

apwn : Add
APawn::AddControllerPitchInput 걍 사용 가능
Pawn::AddControllerPitchInput' [지정된 모듈을 찾을 수 없습니다.]
LogSelectionDetails: Warning: NavigateToFunctionSource:  Unable to find source file and line number for 'USceneComponent::GetSocketTransform' [지정된 모듈을 찾을 수 없습니다.]
LogSelectionDetails: Warning: NavigateToFunctionSource:  Unable to find source file and line number for 'USceneComponent::GetSocketTransform' [지정된 모듈을 찾을 수 없습니다.]
LogSelectionDetails: Warning: NavigateToFunctionSource:  Unable to find source file and line number for 'UCameraComponent

		FCollisionQueryParams params;
		params.AddIgnoredActor( this );
ㄴ igoner self


----------------------2.1 시작

선형보ㅑ간 - lerp , tween

vector - > rotation -> lerp  3가지 젤 중요함

매쉬(매쉬) 피직에섹(충돌체) 스켈레톤(뼈대)

asset -  export - . 

FSM _ 유한상태기계
finite(유한하다) state(상태) mchine(기계)

상태 - 조건 - 전이

객채 - 추상

if는 같은 수 넣어도 오류 안남
switch는 같은 수 넣으념 오류남 _ 확인 용이  _ 문자도 가능

열거형 enum  쓰면 숫자 자동 삽입   
  ㄴ class 가능 UENUM(매크로)

Cache - 기억하는 메모리

owner - 컴포넌트의 주인 = 액터 or pawn 캐릭터

라디안(호도원의 길이 기준)과 디그리(360도)의 차이

/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'

* 포인터 - 전방선언

get FloatVaule ->Set Relatvie Location

tab enter enter

 TickIdle();    break;
	case EEnemyState::MOVE:   TickMoce();	 break;
	case EEnemyState::ATTACk: TickAttack();  break;
	case EEnemyState::DAMAGE: TickDamage();  break;
	case EEnemyState::DIE:    TickDie();

AActor 는 헤더 추가 되있어서 전방선언 안해도됌

헤더 변수 선언

		
	UPROPERTY( EditAnywhere )
	EEnemyState state;

	UPROPERTY( EditAnywhere )
	float AttackDistance = 200;

	UPROPERTY( EditAnywhere )
	//class AActor* target;
	AActor* target;

	UPROPERTY( EditAnywhere )
	class AEnemy* me;
------2.1 수업 시마이

--------------------------------------------------

2.2 t시작 

열거형 중요

GetDistanceTo

alt shift s - 토마토 써서 검색

토마토 메소드 자동 생성 개이득 (헤더, 소스 둘다)
ctrl shift q

check( 어썰트

코테시발

파라미터 매개변수 아규먼트?

0-000000000000--02.05------------------시작

애니메이션은 스캘레톤매쉬가함

애니메이션은 클래스파인더?

_C는 왜 나옴? 경로 가져갈때도 C 붙여야함

애니메이션 제어
ㄴEventGraph -> 변수의 값을 제어
ㄴAnimGraph -> 그 변수의 값을 조건으로 흐름을 만들어서 어떤 애니메이션을 출력할지 결정한다. 

Blend Poses by bool - stateMchien
ㄴ int, eunm 가능

anime entry - > beginplay 개념  tick은 아님

백터의 곱은 2가지 
ㄴX, C(ross) 외적
ㄴ º, Dot 내적 _ 스칼라

너무 짧은 애니메이션은 import 할때 clost snap 설정 On

자동으로 갈때 Automatic Rule Based on Sequnce

is falling _ 언리얼 내의 중력 값?

alias 하나로 아니메 모든 연결 가능

--------------2.06  화요일 수업 시작

 EventGraph -> 코딩을 하는 곳
animeGraph -> 애니메이션 입히는곳

C++ 작업 하려면 inputAction  오버라이딩 바인딩 끄는게 좋다.

몽타쥬 = slot (간단이해)

슬롯은 원본 애니메이션이 있어야함(stateMechin)

cached - 로 원본 애니메 나누기 가능

AO 는 마지막이 잘 구현됨
------------------------------- 오전수업끝
오후수업시작
class 쓰기 전에 class명 부터 쓰고 있는지 확인!



2.07 VA- rename 이름 한번에 바꿈
전역 변수, 정적 변수 구분해서 쓰쟈 맴버변수는 무엇? 
프로젝트 언로드-> 로드 하면 클래스 생성 후 재시작  ( 새로고침)

제네레이터 H헤더는 항상 만 아래 있어야함
FSM 만들고 애니메이션 사용 가능 비헤이비어tree는? ㅅㅂ


2.13
--------------------------
AnimeNotify_AttackEnd () - 애니메이션 notifty 추가하고 그걸 C++ 에 이름 동일하게 씀으로써 
같이 사용 가능.
ㄴ c++  하면 블루프린트 지워야함.

UPROPERTY  왜 써야함? 리플렉션 하려고! and 시리얼라제이션(직렬화)

UPROPERTY 기능 
	//리플렉션 , 직렬화, 스마트포인터'

Montage 하나에 여러 애니메이션 넣기 가능 ( Montage section)
ㄴ 여기에도 notify 가능