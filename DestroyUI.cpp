#include "DestroyUI.h"

void UDestroyUI::DelayedDestroySelf(UUserWidget * Caller) //Yes this does really on a blueprint but for UI elements those are necessary.
{
	Caller->RemoveFromParent(); //Remove from the parent widget
	Caller->Destruct(); //Destroy it, I think this deals with memory leaks.
} 
