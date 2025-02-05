#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveActor1.generated.h"

UCLASS()
class SIXTH_API AMoveActor1 : public AActor
{
	GENERATED_BODY()
	
public:	

	AMoveActor1();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveActor1|Properties")
	float LocationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveActor1|Properties")
	float MaxDistanceRange;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MoveActor1|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "MoveActor1|Components")
	UStaticMeshComponent* StaticMeshComp;

	FVector StartLocation;
	FVector TargetLocation;
	bool MovingForward;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
