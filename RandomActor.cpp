#include "RandomActor.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"


bool ARandomActor::CheckForOverlap(const FVector& Location, float Radius)
{

	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(Radius);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	TArray<FHitResult> OutHits;
	bool bHit = GetWorld()->SweepMultiByChannel(OutHits, Location, Location + FVector(0, 0 ,1), FQuat::Identity, ECC_WorldStatic, CollisionShape, QueryParams);

	if (bHit)
	{

		for (const FHitResult& Hit : OutHits)
		{

			if (Hit.GetActor())
			{

				return true;

			}

		}

	}

	return bHit;
	
}

ARandomActor::ARandomActor()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = false;

}

void ARandomActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ARandomActor::SpawnActor, SpawnInterval, true);
}

void ARandomActor::SpawnActor()
{

	for (int32 i = 0; i < ActorCount; i++)
	{

		FVector RandomLocation = GenerateRandomLocation();
		FRotator RandomRotation = GenerateRandomRotation();

		AActor* NewActor = nullptr;

		if (FMath::RandBool())
		{
		
			NewActor = GetWorld()->SpawnActor<AMoveActor1>(AMoveActor1::StaticClass(), RandomLocation, RandomRotation);

		}
		else
		{

			NewActor = GetWorld()->SpawnActor<ARotateActor1>(ARotateActor1::StaticClass(), RandomLocation, RandomRotation);

		}
		if (NewActor)
		{
			UStaticMeshComponent* NewStaticMeshComp = NewActor->FindComponentByClass<UStaticMeshComponent>();
			if (NewStaticMeshComp && StaticMeshComp)
			{
				
				NewStaticMeshComp->SetStaticMesh(StaticMeshComp->GetStaticMesh());
				NewStaticMeshComp->SetRelativeLocation(StaticMeshComp->GetRelativeLocation());
				NewStaticMeshComp->SetRelativeRotation(StaticMeshComp->GetRelativeRotation());
				NewStaticMeshComp->SetRelativeScale3D(StaticMeshComp->GetRelativeScale3D());

				for (int32 MaterialIndex = 0; MaterialIndex < StaticMeshComp->GetNumMaterials(); MaterialIndex++)
				{
					
					UMaterialInterface* Material = StaticMeshComp->GetMaterial(MaterialIndex);

					
					NewStaticMeshComp->SetMaterial(MaterialIndex, Material);
				}

			}

			FTimerHandle DeleteTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(DeleteTimerHandle,
				[NewActor]()
				{
					if (IsValid(NewActor))
					{
						NewActor->Destroy();
					}
				},
				DeleteInterval,
				false
			);

		}

	}

}

FVector ARandomActor::GenerateRandomLocation()
{
	
	FVector RandomLocation;
	bool bValidLocation = false;
	float ObjectRadius = 50.0f;

	int32 MaxAttempts = 1000;
	int32 AttemptCount = 0;

	while (!bValidLocation && AttemptCount <  MaxAttempts)
	{
		AttemptCount++;
		float X = FMath::RandRange(-310.0f, 370.0f);
		float Y = FMath::RandRange(4870.0f, 5820.0f);
		
		RandomLocation = FVector(X, Y, 20.0f);

		if (!CheckForOverlap(RandomLocation, ObjectRadius))
		{
			bool bOverlap = false;
			for (const FVector& ExistingLocation : SpawnedLocations)
			{

				if (FVector::Dist(RandomLocation, ExistingLocation) < 150.0f)
				{

					bOverlap = true;
					break;
				}

			}

			if (!bOverlap)
			{

				bValidLocation = true;
				SpawnedLocations.Add(RandomLocation);

			}
		}
	}

	if (!bValidLocation)
	{

		UE_LOG(LogTemp, Warning, TEXT("Accel"));

	}
	return RandomLocation;
}

FRotator ARandomActor::GenerateRandomRotation()
{

	float Yaw = FMath::RandRange(0.0f, 360.0f);
	return FRotator(0.0f, Yaw, 0.0f);

}