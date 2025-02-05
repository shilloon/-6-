#include "MoveActor1.h"
#include "Components/StaticMeshComponent.h"

AMoveActor1::AMoveActor1()
{

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;
	LocationSpeed = 200.0f;
	MaxDistanceRange = 280.0f;
	MovingForward = true;

	if (StaticMeshComp)
	{

		StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}

}

void AMoveActor1::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	TargetLocation = StartLocation + FVector(MaxDistanceRange, 0.0f, 0.0f);
}

void AMoveActor1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation;

	if (MovingForward)
	{
		
		NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, LocationSpeed);

		if (FVector::Dist(NewLocation, TargetLocation) < 1.0f)
		{

			MovingForward = false;

		}
		
	}
	else
	{

		NewLocation = FMath::VInterpConstantTo(CurrentLocation, StartLocation, DeltaTime, LocationSpeed);

		if (FVector::Dist(NewLocation, StartLocation) < 1.0f)
		{

			MovingForward = true;

		}

	}

	SetActorLocation(NewLocation);

}

