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
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> ActorToSpawn;
	UPROPERTY(EditAnywhere) //The particular widget class for an object to be spawned from.
		TSubclassOf<UUserWidget> WidgetClassVar;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ^ This code isn't really needed however it does allow the user to interchange the cell that is spawned.

};
