#include "Master.h"
#include "Cell.h"
#include "Engine/World.h"

// Sets default values
//This class only exists to spawn all the cells.
//Pretty sure I can use something like this in my EMC for world loading if I use a construction script
AMaster::AMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//This is if the default use of a class is desired. Though it will remain commented out
	//ActorToSpawn = TSubclassOf<ACell>();

}

// Called when the game starts or when spawned
void AMaster::BeginPlay()
{
	Super::BeginPlay();
	//The code for creating the start of game ui element.
	UUserWidget* WidgetRef;
	WidgetRef = CreateWidget<UUserWidget>(GetWorld(), WidgetClassVar); //Creates a ui element
	if (WidgetRef != nullptr) //Checks to mke sure a UI element has been created or it'll crash
	{
		WidgetRef->AddToViewport(); //Lets the use see it.
	}
	FActorSpawnParameters SpawnParams;
	//^nothing important needed here in this case.
	for (size_t x = 0; x < 10; x++)
	{
		for (size_t y = 0; y < 10; y++)
		{
			for (size_t z = 0; z < 10; z++)
			{
				GetWorld()->SpawnActor<AActor>(ActorToSpawn, FVector(100*x,100*y,100*z), FRotator(0,0,0),SpawnParams);
				//^ spawns an actor of the type that is specifed in a variable exposed per instance. Sets the position and rotation.
				//A great example of object orientation which in this case is Object(epic games') -> Actor(epic games') -> Master(mine)
			}	

		}
	}
}

// Called every frame
void AMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
