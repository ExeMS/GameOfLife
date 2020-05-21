#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Blueprint/UserWidget.h"
#include "DestroyUI.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFLIFE_API UDestroyUI : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "UI Function")
		static void DelayedDestroySelf(UUserWidget* Caller);
};
