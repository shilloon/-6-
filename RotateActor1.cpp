#include "RotateActor1.h"
#include "Components/StaticMeshComponent.h"

ARotateActor1::ARotateActor1()
{

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 45.0f;

	if (StaticMeshComp)
	{

		StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}


}


void ARotateActor1::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARotateActor1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRocation = FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f);
	AddActorLocalRotation(NewRocation);

}

