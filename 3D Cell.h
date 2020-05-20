// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Cell.generated.h"

UCLASS()
class EMCGAME_API ACell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACell();
	FTimerHandle MainLoop;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//class UBoxComponent* OverlapObj;

public:	
	// UProperties are basicly just global variables for the class. All private variables are in the main cpp file.
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool bAlive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default") //This variable isn't really needed as the NeighboursInit variable is used.
		TArray<ACell*> Neighbours;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TArray<AActor*> NeighboursInit;

	//UPROPERTY(VisibleAnywhere)
		//UStaticMeshComponent* MainMesh;


	UPROPERTY(EditAnywhere) 
		class UMaterialInterface* MainMat;
	UPROPERTY(EditAnywhere)
		class UMaterialInterface* OtherMat;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MainMesh; //The mesh that will be used. It's only technicallt a reference to a class such that a mesh can be spawned.

	UPROPERTY(EditAnywhere) //The invisible collision that is used to find out which of the cells are this ones neighbours.
		UBoxComponent* CollBox;



	UFUNCTION()
		void onTimerFire();

	UFUNCTION()
		void InitCell();

	//UFUNCTION()
		//OnOverlapBegin(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
