**Steps For a Simple C++ Test of the UE4.24.3 HTN Planner Plugin**

[\@NoFrogPlansMore](https://twitter.com/nofrogplansmore)

**Objective:** A First C++ test of the HTN Planner Plugin with UE4.24.3

**Content:**

>   **Minimum Requirement: UE4 Documentation section on** [Programming Quick
>   Start](https://docs.unrealengine.com/latest/INT/Programming/QuickStart/index.html)

>   **Section 1: Required Project Setup**

>   [Subsection 1.1: Make the HTN Planner Plugin available for your
>   project](#Partie_1_1)

>   [Subsection 1.2: Add a C++ Class to the project](#Partie_1_2)

>   **Section 2: Testing plan generation**

>   [Subsection 2.1: Enabling Console Logging](#Partie_2_1)

>   [Subsection 2.2: (Empty) Test of the HTN Planner](#Partie_2_2)

>   [Subsection 2.3: Testing a simple planning domain](#Partie_2_3)

[Appendix 1: “MyActor.h”](#Annexe_1)

[Appendix 2 : “MyActor.cpp”](#Annexe_2)

  
**Section 1 : Required Project Setup (≤1/4h) (Unreal Documentation – Programming
Quick Start)**

You should have a copy of **Visual Studio 2017** for Desktop (Preferably
Community or Professional Edition) installed before starting this tutorial. For
setup instructions, please see [Setting Up Visual Studio for
UE4](https://docs.unrealengine.com/latest/INT/Programming/Development/VisualStudioSetup/index.html)
.

1.  Open **Unreal Engine** from the Launcher. The [Unreal Project
    Browser](https://docs.unrealengine.com/latest/INT/Engine/Basics/Projects/Browser/index.html)
    window will appear. Select “Games” in New Project Categories and click on
    “Next”.

![](media/e53c2bdf405d1fbdc9b4a713240dc87a.png)

1.  Select the Blank Template and then click on “Next”:

![](media/14761be76a7c65e968455382f00e2df4.png)

1.  In the Project Settings window, make sure to select **C++** and as this is a
    simple test, **Without Starter Content**. Eventually enter a name for your
    project; I here chose “TestUE4243HTNPlanner” as a project name. We can now
    click **Create Project** and get started:

![](media/cc13c8af2f3e2e28d3fd7552334fad13.png)

The **Unreal Editor** will now open our new project. **Visual Studio** will also
open and load the solution file that our project has created.

**Subsection 1.1 : Make the HTN Planner Plugin available for your project**

1.  Left-click sur Settings \> Plugins et look for HTN; when you click on the
    “Enabled” box, a Message appears telling you the Plugin is a beta version:

![](media/9ec91bf91b54cabce05d351a3aa5743d.png)

1.  Left-click on “Yes” and then on “Restart Now”. Unreal shuts down and
    immediately restarts with the HTN Planner Plugin enabled. Close the Plugins
    window.

2.  In the Solution explorer of **Visual Studio**, you can check the access of
    the C++ code of the “HTNPlanner” from EngineUE4PluginsAIHTNPlannerSource:

>    

![](media/f3f9be21cdba34e9e6f4f2ebcb0ff353.png)

1.  In Visual Studio, open the file:

>   GamesTestUE4HTNPlanner Source TestUE4HTNPlanner TestUE4HTNPlanner.Build.cs

1.  Line 13, add "HTNPlanner" to the list of Private Dependency Module Names:

>   PrivateDependencyModuleNames.AddRange(new string[] { "HTNPlanner" });

>   If you forgot to do this, the compiler won’t be able to \#include the
>   necessary HTN Planner Plugin public files for this test.

1.  Get back to the Unreal Editor to left-click on “Compile”. Wait for the
    compilation to complete successfully.

**Subsection 1.2 : Add a C++ class to the project**

We now add a class to our project to later call the HTN Planner with the
BeginPlay() method.

1.  In the Unreal Editor, Left-Click File \> New C++ Class… Choose “Actor” as a
    Parent Class:

![](media/aa9aba1a3b305019d3c89459f0827493.png)

1.  Left-Click on “Create Class” (UE4 proposes to name your Actor Class
    “MyActor” which is just fine for this test) to generate and compile various
    files to your project:

![](media/97aaf441012079470069c1156737c136.png)

1.  Switch to Visual Studio and check file ‘’MyActor.cpp” is open and looks like
    this:

![](media/2dbbabff6f9ad58c6133e3abfee35652.png)

**Section 2 : Testing plan generation (≤3/4h)**

**Subsection 2.1 : Enabling console logging**

1.  Open “MyActor.h” in Visual Studio and insert the following after \#include
    "MyActor.generated.h" (which you can find in line 7) :

>   DECLARE_LOG_CATEGORY_EXTERN(MyLogHTNPlanner, Log, All);

>   This could be inserted line 9, for instance.

1.  Add the following to “MyActor.cpp” , just after \#include "MyActor.h" (ligne
    4):

>   DEFINE_LOG_CATEGORY(MyLogHTNPlanner);

>   This could be inserted line 6, for instance.

1.  Add the following to the body of BeginPlay() in “MyActor.cpp”:

>   UE_LOG(MyLogHTNPlanner, Warning, TEXT("==\> Beginning the test of the HTN
>   Plugin"));

>   This could be inserted line 21, for instance.

![](media/db8eecb10fe5d36d1194bd5da16e390a.png)

1.  Back to the Unreal Editor, make sure C++ Classes \> TestUE4HTNPlanner is
    open in the Content Browser:

![](media/7a75c901730cdcc94d5dff6358873187.png)

1.  Drag and drop MyActor anywhere in the game scene; “MyActor1” must now appear
    in the “World Outliner”:

![](media/e2c593805467d4d76d3c94bd4e7c8a86.png)

1.  If the Output Log tab isn’t already available right to the Content Browser
    tab, make it so: Left-Click on Window \> Developer Tools \> Output Log; then
    Click on the Output Log tab to see its contents.

2.  Now, Left-Click on “Compile’’ and wait for compilation to complete; then
    Left-Clik on “Play” to see the BeginPlay() log from “MyActor.cpp”:

![](media/3b2353a9d86bc22bfedc6bb3eb3d2b12.png)

**Subsection 2.2 : (Empty) Test of the HTN Planner**

We’re now to make an empty call to the planner and log this call.

1.  In Visual Studio, add the following inclusion of “. h” files to
    “MyActor.cpp” in order to enable the declaration and the building of a
    planning domain, and the call to the planner:

>   // =\> HTN Planning includes

>   \#include "HTNDomain.h"

>   \#include "HTNBuilder.h"

>   \#include "HTNPlanner.h"

>   // \<= HTN Planning includes

This can start line 6, for instance.

1.  Add the following to the body of in “MyActor.cpp”:

>   FHTNBuilder_Domain DomainBuilder;

>   FHTNWorldState WorldState;

>   FHTNResult Result;

>   FHTNPlanner MyHTNPlanner;

>   This can start line 29, for instance.

1.  Back to the Unreal Editor to Click on “Compile” and check that the
    compilation completed successfully; that is, both the inclusion of the HTN
    Plugin public files and the above delcarations were successful.

2.  Now let’s add an empty call to the HTN Planner to test the above variables;
    for instance, this can start in line 34 of “MyActor.cpp”:

>   MyHTNPlanner.GeneratePlan(\*(DomainBuilder.DomainInstance), WorldState,
>   Result);

>   if (Result.TaskIDs.Num() == 0)

>   UE_LOG(MyLogHTNPlanner, Warning, TEXT("Planning with an empty domain results
>   in an empty plan."))

>   else

>   UE_LOG(MyLogHTNPlanner, Warning, TEXT("Ooops !!!!!"));

1.  Add the following log to the body of BeginPlay() in “MyActor.cpp”, for
    instance line 40:

>   UE_LOG(MyLogHTNPlanner, Warning, TEXT("\<== End the test of the HTN
>   Plugin"));

1.  Back to the Unreal Editor to Left-Click on “Compile” and check that the
    compilation completed successfully; then Left-Click on “Play” and check the
    logs:

![](media/a0055e90f642b16e2db326306b4aafad.png)

**Subsection 2.3: Testing a simple planning domain**

1.  Give a look at the test code which comes with the HTN Planner Plugin; for
    instance, give a look (or read, or study) files “MokHTN.h” and
    “HTNTest.cpp”:

![](media/05954b7e11b0eff545b125709809e7f6.png)

1.  Copy lines 11 to 36 from “MokHTN.h” and paste them in “MyActor.cpp”, for
    instance starting line 14:

>   enum class EMockHTNWorldState : uint8

>   {

>   EnemyHealth,

>   EnemyActor,

>   Ammo,

>   AbilityRange,

>   HasWeapon,

>   MoveDestination,

>   PickupLocation,

>   CurrentLocation,

>   CanSeeEnemy,

>   MAX

>   };

>   enum class EMockHTNTaskOperator : uint8

>   {

>   DummyOperation,

>   FindPatrolPoint,

>   FindWeapon,

>   NavigateTo,

>   PickUp,

>   UseWeapon,

>   MAX

>   };

1.  Copy lines 39 à 106 from “HTNTest.cpp’’ and paste them in the body of
    BeginPlay() in “MyActor.cpp”, for instance starting line 69:

DomainBuilder.SetRootName(TEXT("Root"));

{

FHTNBuilder_CompositeTask& CompositeTaskBuilder =
DomainBuilder.AddCompositeTask(TEXT("Root"));

{

FHTNBuilder_Method& MethodsBuilder = CompositeTaskBuilder.AddMethod(

TArray\<FHTNCondition\>({

FHTNCondition(EMockHTNWorldState::EnemyHealth,
EHTNWorldStateCheck::Greater).SetRHSAsValue(0)

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

FHTNBuilder_CompositeTask& CompositeTaskBuilder =
DomainBuilder.AddCompositeTask(TEXT("AttackEnemy"));

{

FHTNBuilder_Method& MethodsBuilder =
CompositeTaskBuilder.AddMethod(FHTNCondition(EMockHTNWorldState::HasWeapon,
EHTNWorldStateCheck::IsTrue));

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

FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder =
DomainBuilder.AddPrimitiveTask(TEXT("FindPatrolPoint"));

PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::FindPatrolPoint,
EMockHTNWorldState::MoveDestination);

}

{

FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder =
DomainBuilder.AddPrimitiveTask(TEXT("FindWeapon"));

PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::FindWeapon,
EMockHTNWorldState::PickupLocation);

}

{

FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder =
DomainBuilder.AddPrimitiveTask(TEXT("NavigateToMoveDestination"));

PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::NavigateTo,
EMockHTNWorldState::MoveDestination); // Local Variables?

PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::CurrentLocation,
EHTNWorldStateOperation::Set).SetRHSAsWSKey(EMockHTNWorldState::MoveDestination));

}

{

FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder =
DomainBuilder.AddPrimitiveTask(TEXT("NavigateToEnemy"));

PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::NavigateTo,
EMockHTNWorldState::EnemyActor);

PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::CurrentLocation,
EHTNWorldStateOperation::Set).SetRHSAsWSKey(EMockHTNWorldState::EnemyActor));

PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::CanSeeEnemy,
EHTNWorldStateOperation::Set).SetRHSAsValue(1));

}

{

FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder =
DomainBuilder.AddPrimitiveTask(TEXT("NavigateToWeapon"));

PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::NavigateTo,
EMockHTNWorldState::PickupLocation);

PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::CurrentLocation,
EHTNWorldStateOperation::Set).SetRHSAsWSKey(EMockHTNWorldState::PickupLocation));

}

{

FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder =
DomainBuilder.AddPrimitiveTask(TEXT("PickUp"));

PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::PickUp,
EMockHTNWorldState::PickupLocation);

PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::HasWeapon,
EHTNWorldStateOperation::Set).SetRHSAsValue(1));

}

{

FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder =
DomainBuilder.AddPrimitiveTask(TEXT("UseWeapon"));

PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::UseWeapon,
EMockHTNWorldState::EnemyActor);

PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::Ammo,
EHTNWorldStateOperation::Decrease).SetRHSAsValue(1));

PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::EnemyHealth,
EHTNWorldStateOperation::Decrease).SetRHSAsValue(1));

>   }

1.  Following the previous insertion, add the following lines (the if can be
    found line 108 to 111 in “HTNTest.cpp”) to the body of BeginPlay() in
    “MyActor.cpp”, for instance starting line 138:

>   bool bCompile = true;

>   if (bCompile)

>   {

>   DomainBuilder.Compile();

>   }

1.  Now add the following call to the HTN Planner, for instance starting line
    144 in the body of BeginPlay() in “MyActor.cpp”:

>   MyHTNPlanner.GeneratePlan(\*(DomainBuilder.DomainInstance), WorldState,
>   Result);

1.  Eventually insert a log of the length of the plan and its actions, for
    instance starting line 146 in the body of BeginPlay() in “MyActor.cpp”:

>   UE_LOG(MyLogHTNPlanner, Warning, TEXT("A plan of length %d has been
>   generated"), Result.TaskIDs.Num())

>   for (int i = 0; i \< Result.TaskIDs.Num(); ++i)

>   {

>   UE_LOG(MyLogHTNPlanner, Warning, TEXT("[i = %d] Action Id = %d -- "), i,
>   Result.ActionsSequence[i].ActionID)

>   }

1.  Back to the Unreal Editor, Left-Click on “Compile” (which should result in a
    successful compilation) and then “Play” to check the following logs:

![](media/0509fb2dd91f81e66c6aa5d6a043cc39.png)

1.  That’s All Folks!

**Appendix 1:** “MyActor.h”

// Fill out your copyright notice in the Description page of Project Settings.

\#pragma once

\#include "CoreMinimal.h"

\#include "GameFramework/Actor.h"

\#include "MyActor.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(MyLogHTNPlanner, Log, All);

UCLASS()

class TESTUE4243HTNPLANNER_API AMyActor : public AActor

{

GENERATED_BODY()

public:

// Sets default values for this actor's properties

AMyActor();

protected:

// Called when the game starts or when spawned

virtual void BeginPlay() override;

public:

// Called every frame

virtual void Tick(float DeltaTime) override;

};

**Appendix 2 :** “MyActor.cpp”

// Fill out your copyright notice in the Description page of Project Settings.

\#include "MyActor.h"

// =\> HTN Planning includes

\#include "HTNDomain.h"

\#include "HTNBuilder.h"

\#include "HTNPlanner.h"

// \<= HTN Planning includes

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

// Set this actor to call Tick() every frame. You can turn this off to improve
performance if you don't need it.

PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned

void AMyActor::BeginPlay()

{

Super::BeginPlay();

UE_LOG(MyLogHTNPlanner, Warning, TEXT("==\> Beginning the test of the HTN
Plugin"));

FHTNBuilder_Domain DomainBuilder;

FHTNWorldState WorldState;

FHTNResult Result;

FHTNPlanner MyHTNPlanner;

MyHTNPlanner.GeneratePlan(\*(DomainBuilder.DomainInstance), WorldState, Result);

if (Result.TaskIDs.Num() == 0)

UE_LOG(MyLogHTNPlanner, Warning, TEXT("Planning with an empty domain results in
an empty plan."))

else

UE_LOG(MyLogHTNPlanner, Warning, TEXT("Ooops !!!!!"));

UE_LOG(MyLogHTNPlanner, Warning, TEXT("\<== End the test of the HTN Plugin"));

DomainBuilder.SetRootName(TEXT("Root"));

{

FHTNBuilder_CompositeTask& CompositeTaskBuilder =
DomainBuilder.AddCompositeTask(TEXT("Root"));

{

FHTNBuilder_Method& MethodsBuilder = CompositeTaskBuilder.AddMethod(

TArray\<FHTNCondition\>({

FHTNCondition(EMockHTNWorldState::EnemyHealth,
EHTNWorldStateCheck::Greater).SetRHSAsValue(0)

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

FHTNBuilder_CompositeTask& CompositeTaskBuilder =
DomainBuilder.AddCompositeTask(TEXT("AttackEnemy"));

{

FHTNBuilder_Method& MethodsBuilder =
CompositeTaskBuilder.AddMethod(FHTNCondition(EMockHTNWorldState::HasWeapon,
EHTNWorldStateCheck::IsTrue));

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

FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder =
DomainBuilder.AddPrimitiveTask(TEXT("FindPatrolPoint"));

PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::FindPatrolPoint,
EMockHTNWorldState::MoveDestination);

}

{

FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder =
DomainBuilder.AddPrimitiveTask(TEXT("FindWeapon"));

PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::FindWeapon,
EMockHTNWorldState::PickupLocation);

}

{

FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder =
DomainBuilder.AddPrimitiveTask(TEXT("NavigateToMoveDestination"));

PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::NavigateTo,
EMockHTNWorldState::MoveDestination); // Local Variables?

PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::CurrentLocation,
EHTNWorldStateOperation::Set).SetRHSAsWSKey(EMockHTNWorldState::MoveDestination));

}

{

FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder =
DomainBuilder.AddPrimitiveTask(TEXT("NavigateToEnemy"));

PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::NavigateTo,
EMockHTNWorldState::EnemyActor);

PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::CurrentLocation,
EHTNWorldStateOperation::Set).SetRHSAsWSKey(EMockHTNWorldState::EnemyActor));

PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::CanSeeEnemy,
EHTNWorldStateOperation::Set).SetRHSAsValue(1));

}

{

FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder =
DomainBuilder.AddPrimitiveTask(TEXT("NavigateToWeapon"));

PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::NavigateTo,
EMockHTNWorldState::PickupLocation);

PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::CurrentLocation,
EHTNWorldStateOperation::Set).SetRHSAsWSKey(EMockHTNWorldState::PickupLocation));

}

{

FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder =
DomainBuilder.AddPrimitiveTask(TEXT("PickUp"));

PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::PickUp,
EMockHTNWorldState::PickupLocation);

PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::HasWeapon,
EHTNWorldStateOperation::Set).SetRHSAsValue(1));

}

{

FHTNBuilder_PrimitiveTask& PrimitiveTaskBuilder =
DomainBuilder.AddPrimitiveTask(TEXT("UseWeapon"));

PrimitiveTaskBuilder.SetOperator(EMockHTNTaskOperator::UseWeapon,
EMockHTNWorldState::EnemyActor);

PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::Ammo,
EHTNWorldStateOperation::Decrease).SetRHSAsValue(1));

PrimitiveTaskBuilder.AddEffect(FHTNEffect(EMockHTNWorldState::EnemyHealth,
EHTNWorldStateOperation::Decrease).SetRHSAsValue(1));

}

bool bCompile = true;

if (bCompile)

{

DomainBuilder.Compile();

}

MyHTNPlanner.GeneratePlan(\*(DomainBuilder.DomainInstance), WorldState, Result);

UE_LOG(MyLogHTNPlanner, Warning, TEXT("A plan of length %d has been generated"),
Result.TaskIDs.Num())

for (int i = 0; i \< Result.TaskIDs.Num(); ++i)

{

UE_LOG(MyLogHTNPlanner, Warning, TEXT("[i = %d] Action Id = %d -- "), i,
Result.ActionsSequence[i].ActionID)

}

}

// Called every frame

void AMyActor::Tick(float DeltaTime)

{

Super::Tick(DeltaTime);

}
