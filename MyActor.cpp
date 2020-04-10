// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// => HTN Planning includes
#include "HTNDomain.h"
#include "HTNBuilder.h"
#include "HTNPlanner.h"
// <= HTN Planning includes

DEFINE_LOG_CATEGORY(MyLogHTNPlanner);

enum class EMockHTNWorldState : uint8
{
	EnemyHealth,
	EnemyActor,
	Ammo,
	AbilityRange,
	HasWeapon,
	MoveDestination,
	PickupLocation,
	CurrentLocation,
	CanSeeEnemy,

	MAX
};

enum class EMockHTNTaskOperator : uint8
{
	DummyOperation,
	FindPatrolPoint,
	FindWeapon,
	NavigateTo,
	PickUp,
	UseWeapon,

	MAX
};

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(MyLogHTNPlanner, Warning, TEXT("==> Beginning the test of the HTN Plugin"));

	FHTNBuilder_Domain DomainBuilder;
	FHTNWorldState WorldState;
	FHTNResult Result;
	FHTNPlanner MyHTNPlanner;

	MyHTNPlanner.GeneratePlan(*(DomainBuilder.DomainInstance), WorldState, Result);
	if (Result.TaskIDs.Num() == 0)
		UE_LOG(MyLogHTNPlanner, Warning, TEXT("Planning with an empty domain results in an empty plan."))
	else
		UE_LOG(MyLogHTNPlanner, Warning, TEXT("Ooops !!!!!"));

	UE_LOG(MyLogHTNPlanner, Warning, TEXT("<== End the test of the HTN Plugin"));

	DomainBuilder.SetRootName(TEXT("Root"));
	{
		FHTNBuilder_CompositeTask& CompositeTaskBuilder = DomainBuilder.AddCompositeTask(TEXT("Root"));
		{
			FHTNBuilder_Method& MethodsBuilder = CompositeTaskBuilder.AddMethod(
				TArray<FHTNCondition>({
				FHTNCondition(EMockHTNWorldState::EnemyHealth, EHTNWorldStateCheck::Greater).SetRHSAsValue(0)
				, FHTNCondition(EMockHTNWorldState::EnemyActor, EHTNWorldStateCheck::IsTrue)
					}));
			MethodsBuilder.AddTask(TEXT("AttackEnemy"));
		}
		{
			FHTNBuilder_Method& MethodsBuilder = CompositeTaskBuilder.AddMethod();
			MethodsBuilder.AddTask(TEXT("FindPatrolPoint"));
			MethodsBuilder.AddTask(TEXT("NavigateToMoveDestination"));
		}
	}
	{
		FHTNBuilder_CompositeTask& CompositeTaskBuilder = DomainBuilder.AddCompositeTask(TEXT("AttackEnemy"));
		{
			FHTNBuilder_Method& MethodsBuilder = CompositeTaskBuilder.AddMethod(FHTNCondition(EMockHTNWorldState::HasWeapon, EHTNWorldStateCheck::IsTrue));
			MethodsBuilder.AddTask(TEXT("NavigateToEnemy"));
			MethodsBuilder.AddTask(TEXT("UseWeapon"));
			MethodsBuilder.AddTask(TEXT("Root"));
		}
		{
			FHTNBuilder_Method& MethodsBuilder = CompositeTaskBuilder.AddMethod();
			MethodsBuilder.AddTask(TEXT("FindWeapon"));
			MethodsBuilder.AddTask(TEXT("NavigateToWeapon"));
			MethodsBuilder.AddTask(TEXT("PickUp"));
			MethodsBuilder.AddTask(TEXT("AttackEnemy"));
		}
	}
	{
		FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder = DomainBuilder.AddPrimitiveTask(TEXT("FindPatrolPoint"));
		PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::FindPatrolPoint, EMockHTNWorldState::MoveDestination);
	}
	{
		FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder = DomainBuilder.AddPrimitiveTask(TEXT("FindWeapon"));
		PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::FindWeapon, EMockHTNWorldState::PickupLocation);
	}
	{
		FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder = DomainBuilder.AddPrimitiveTask(TEXT("NavigateToMoveDestination"));
		PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::NavigateTo, EMockHTNWorldState::MoveDestination);	// Local Variables?
		PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::CurrentLocation, EHTNWorldStateOperation::Set).SetRHSAsWSKey(EMockHTNWorldState::MoveDestination));
	}
	{
		FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder = DomainBuilder.AddPrimitiveTask(TEXT("NavigateToEnemy"));
		PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::NavigateTo, EMockHTNWorldState::EnemyActor);
		PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::CurrentLocation, EHTNWorldStateOperation::Set).SetRHSAsWSKey(EMockHTNWorldState::EnemyActor));
		PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::CanSeeEnemy, EHTNWorldStateOperation::Set).SetRHSAsValue(1));
	}
	{
		FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder = DomainBuilder.AddPrimitiveTask(TEXT("NavigateToWeapon"));
		PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::NavigateTo, EMockHTNWorldState::PickupLocation);
		PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::CurrentLocation, EHTNWorldStateOperation::Set).SetRHSAsWSKey(EMockHTNWorldState::PickupLocation));
	}
	{
		FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder = DomainBuilder.AddPrimitiveTask(TEXT("PickUp"));
		PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::PickUp, EMockHTNWorldState::PickupLocation);
		PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::HasWeapon, EHTNWorldStateOperation::Set).SetRHSAsValue(1));
	}
	{
		FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder = DomainBuilder.AddPrimitiveTask(TEXT("UseWeapon"));
		PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::UseWeapon, EMockHTNWorldState::EnemyActor);
		PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::Ammo, EHTNWorldStateOperation::Decrease).SetRHSAsValue(1));
		PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::EnemyHealth, EHTNWorldStateOperation::Decrease).SetRHSAsValue(1));
	}

	bool bCompile = true;
	if (bCompile)
	{
		DomainBuilder.Compile();
	}

	MyHTNPlanner.GeneratePlan(*(DomainBuilder.DomainInstance), WorldState, Result);

	UE_LOG(MyLogHTNPlanner, Warning, TEXT("A plan of length %d has been generated"), Result.TaskIDs.Num())

		for (int i = 0; i < Result.TaskIDs.Num(); ++i)
		{
			UE_LOG(MyLogHTNPlanner, Warning, TEXT("[i = %d] Action Id = %d -- "), i, Result.ActionsSequence[i].ActionID)
		}

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

