특정 조건에 따라 이동, 회전하는 액터와 랜덤으로 생성 및 삭제되는 액터를 구현하였습니다.

# 주요 기능
1. AMoveActor1: 지정된 속도로 이동하는 액터
2. ARotateActor1: 지정된 속도로 회전하는 액터
3. ARandomActor: 일정한 시간 간격으로 액터를 생성 및 삭제하는 시스템

# AMoveActor1 (이동 액터)
* LocationSpeed: 이동 속도 조절 가능
* MaxDistanceRange: 이동할 최대 거리 설정 가능
* StaticMeshComp: 액터의 외형을 담당하는 정적 메시 컴포넌트

# MoveActor1 주요 코드
<pre>
<code>
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
</code>
</pre>

# RotateActor1 (회전 액터)
* RotationSpeed: 회전 속도 조절 가능
* StaticMeshComp: 액터의 외형을 담당하는 정적 메시 컴포넌트

# RotateActor1 주요 코드
<pre>
<code>
void ARotateActor1::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FRotator NewRotation = FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f);
    AddActorLocalRotation(NewRotation);
}
</code>
</pre>

# RandomActor (랜덤 액터)
* DeleteInterval: 일정 시간 후 액터 삭제
* SpawnInterval: 일정 시간 간격으로 액터 생성
* ActorCount: 최대 스폰 가능한 액터 개수

<pre>
<code>
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
            FTimerHandle DeleteTimerHandle;
            GetWorld()->GetTimerManager().SetTimer(DeleteTimerHandle, [NewActor]()
            {
                if (IsValid(NewActor))
                {
                    NewActor->Destroy();
                }
            }, DeleteInterval, false);
        }
    }
}
</code>
</pre> 
