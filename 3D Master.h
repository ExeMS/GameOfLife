#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Master.generated.h"

UCLASS()
class EMCGAME_API AMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> ActorToSpawn;

};
