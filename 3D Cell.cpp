// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/InputComponent.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/MeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"


// Sets default values

//This function basicly constructes the class. It sets the mesh and the collision.
ACell::ACell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//UStaticMeshComponent* 
	//This line creates a sub object that is a human visible mesh.
	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main"));
	//MainMesh->SetupAttachment(RootComponent);
	RootComponent = MainMesh;
	//Each actor needs a root component it's best for this to be the main mesh.
	
	//This line finds the mesh that will be used. All the assets are default engine content that the engine won't work without so nothing needs to be downloaded.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube1.Cube1'"));
	
	if (CubeAsset.Succeeded()) {//Checks that the asset has been loadeed successfully. This really shouldn't fail but if it does GOL won't work but it won't crash.
		MainMesh->SetStaticMesh(CubeAsset.Object);
		//Sets the mesh of the object.
	}
	
	
	//Getting and creating materials not important 
	MainMat = CreateDefaultSubobject<UMaterialInterface>(TEXT("Varient Material"));
	OtherMat = CreateDefaultSubobject<UMaterialInterface>(TEXT("Other Material"));
	static ConstructorHelpers::FObjectFinder<UMaterial> mDeadAsset(TEXT("Material'/Engine/VREditor/UI/ArrowMaterial.ArrowMaterial'")); //These calls are going to need to succeed --Translucent blue
	static ConstructorHelpers::FObjectFinder<UMaterial> mAliveAsset(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'")); //opaque white

	//Setting up of the collision box.
	CollBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	//CollBox->SetWorldScale3D(FVector(1.2f,1.2f,1.2f));
	CollBox->SetBoxExtent(FVector(65,65,65));
	CollBox->SetupAttachment(MainMesh);
	CollBox->SetActive(true);
	
	//if (GetActorLocation() == FVector(0,0,0)) { //Only needs to be done for one of the cells.


		//if (mDeadAsset.Succeeded())
		//{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Dead material has been loaded correctly.")));
		//}
		//else {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Error: Dead material is not found.")));
		//}

		//if (mAliveAsset.Succeeded())
		//{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Alive material has been loaded correctly.")));
		//}
		//else {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Error: Alive material is not found.")));
		//}

	//}
	
	//  ^ For some reason this code causes a crash on engine startup.
	
	MainMesh->SetMaterial(0, MainMat);
	CollBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	
	//Now to initiate the dead or alive colours



}

// Called when the game starts or when spawned
void ACell::BeginPlay() //This function is initiated upon play. All it does it wait for 1 second the call another function.
{
	Super::BeginPlay();
	//When the game starts a loop is created that waits then runs a function. I don't think there's another way to do it.
	GetWorld()->GetTimerManager().SetTimer(MainLoop, this, &ACell::InitCell, 1, true, 1.0f);

}

// Called every frame
void ACell::Tick(float DeltaTime) // This function is somewhat unneeded however it does make sure that the cell is always in the correct state.
{

	Super::Tick(DeltaTime);
	if (bAlive) {
		MainMesh->SetVisibility(true,false);
		//^Makes the cube visible
	}
	else {
		MainMesh->SetVisibility(false, false);
		//^Makes the cube invisible just ignore the second bool
	}
	//onTimerFire();

}

void ACell::InitCell() //This inititates the cell, setting up the randomness and then calling the main looping function.
{
	//This thing is only ran once. The reason it needs to wait before it is run is because other wise not all of the cubes would have spawned.
	bAlive = rand() % 2;
	//TArray<AActor*> NeighboursInit;
	GetOverlappingActors(NeighboursInit, TSubclassOf<ACell>()); //Sets a variable to all the objects its overlapping.
	//FTimerHandle MainLoop;
	if (GetActorLocation() == FVector(0, 0, 0))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("How many neighbours x: %f"), NeighboursInit.Num()));
	}
	//^This code is more for debuging the if statement checks to make sure that it's only the cell at 0,0,0 that runs the code so that only one print statement will occure.
	//Note the command AddOnScreenDebugMessage will only be used in editor versions hence it's fine if an exe is needed.
	GetWorld()->GetTimerManager().SetTimer(MainLoop, this, &ACell::onTimerFire, 1, true, 0.5f);
	//^The main loop
}

void ACell::onTimerFire() //every 0.5 seconds this function occurs. It makes sure that all the neighbours work properly and then it will increment the neighbour number if that is true.
{
	int NeighbourNum = 0;
	ACell* TempCell; //This is just a temporary variable, not point in creating a universal variable.
	for (size_t i = 0; i < (NeighboursInit.Num()); i++)
	{
		TempCell = Cast<ACell>(NeighboursInit[i]);
		//The if statement makes sure that the object casted to was a cell object and not just something else.
		if (TempCell != nullptr)
		{

			if (TempCell->bAlive == true) {
				NeighbourNum += 1;
			} //It might sometimes fail and if it does it is fine.
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Invalid class caught")));
		}

	}
	//The logic that decides what will happen to the cell.
	if (bAlive == true) {  
		if (NeighbourNum < 2) {
			bAlive = false;
		}
		else if (NeighbourNum > 3)
		{
			bAlive = false;
		}
	}
	else {
		if (NeighbourNum == 3) {
			bAlive = true;
		}
	}
}





