#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotateActor1.generated.h"

UCLASS()
class SIXTH_API ARotateActor1 : public AActor
{
	GENERATED_BODY()
	
public:	
	ARotateActor1();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateActor1|Properties")
	float RotationSpeed;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RotateActor|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateActor1|Components")
	UStaticMeshComponent* StaticMeshComp;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
