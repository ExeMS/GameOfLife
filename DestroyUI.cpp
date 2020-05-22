#include "DestroyUI.h"
//Yes this does really on a blueprint but for UI elements those are necessary.
void UDestroyUI::DelayedDestroySelf(UUserWidget * Caller) 
	// Takes in a ui element called caller which the blueprints(a node based language) feed a value into.
	//It the destroys this widget.
{
	Caller->RemoveFromParent(); 
	//Remove from the parent widget
	
	Caller->Destruct(); 
	//Destroy it, I think this deals with memory leaks.
} 
