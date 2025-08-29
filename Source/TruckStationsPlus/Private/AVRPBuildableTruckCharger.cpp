#include "AVRPBuildableTruckCharger.h"

AAVRPBuildableTruckCharger::AAVRPBuildableTruckCharger() : Super()
{
	fuelOutputConnection = CreateDefaultSubobject<UFGFactoryConnectionComponent>(TEXT("OutputFuelConnection"));
	//mFuelInventory = CreateDefaultSubobject<UFGInventoryComponent>(TEXT("FuelInventory"));
}

bool AAVRPBuildableTruckCharger::CanProduce_Implementation() const
{
	return HasPower() && IsValid(truckStation) && (GetTruckStation()->IsLoadUnloading() || GetTruckStation()->GetFuelInventory()->HasEnoughSpaceForItem(FInventoryItem(mTruckPowerClass)));
}

void AAVRPBuildableTruckCharger::Factory_Tick(float dt)
{
	Super::Factory_Tick(dt);
	if (!HasAuthority()) {
		return;
	}
	GetTruckStation()->GetFuelInventory()->AddStack(FInventoryStack(10000, mTruckPowerClass), true);
}