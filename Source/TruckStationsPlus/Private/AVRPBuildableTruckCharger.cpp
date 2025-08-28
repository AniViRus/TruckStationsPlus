#include "AVRPBuildableTruckCharger.h"

AAVRPBuildableTruckCharger::AAVRPBuildableTruckCharger()
{
	fuelOutputConnection = CreateDefaultSubobject<UFGFactoryConnectionComponent>(TEXT("OutputFuelConnection"));
}

void AAVRPBuildableTruckCharger::BeginPlay()
{
	Super::BeginPlay();
}

bool AAVRPBuildableTruckCharger::CanProduce_Implementation() const
{
	return IsValid(truckStation) && HasPower() && truckStation->GetFuelInventory()->HasEnoughSpaceForItem(FInventoryItem(mTruckPowerClass));
}

void AAVRPBuildableTruckCharger::Factory_TickProducing(float dt)
{
	Super::Factory_TickProducing(dt);
	if (not HasAuthority()) {
		return;
	}
	truckStation->GetFuelInventory()->AddStack(FInventoryStack(1500 * dt, mTruckPowerClass), true);
}