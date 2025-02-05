#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveActor1.h"
#include "RotateActor1.h"
#include "RandomActor.generated.h"

UCLASS()
class SIXTH_API ARandomActor : public AActor
{
	GENERATED_BODY()
	
public:	

	ARandomActor();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomActor|Properties")
	float DeleteInterval = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomActor|Properties")
	float SpawnInterval = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomActor|Properties")
	int32 ActorCount = 5;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "RandomActor|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomActor|Components")
	UStaticMeshComponent* StaticMeshComp;

private:

	TArray<FVector> SpawnedLocations;

	bool CheckForOverlap(const FVector& Location, float Radius);

	FTimerHandle SpawnTimerHandle;

	void SpawnActor();

	FVector GenerateRandomLocation();
	FRotator GenerateRandomRotation();

};
