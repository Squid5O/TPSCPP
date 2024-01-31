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

