#include "AVRPBuildableTruckCharger.h"

AAVRPBuildableTruckCharger::AAVRPBuildableTruckCharger() : Super()
{
	fuelOutputConnection = CreateDefaultSubobject<UFGFactoryConnectionComponent>(TEXT("OutputFuelConnection"));
	mFuelInventory = CreateDefaultSubobject<UFGInventoryComponent>(TEXT("FuelInventory"));
}

void AAVRPBuildableTruckCharger::BeginPlay()
{
	Super::BeginPlay();
	//GetFuelInventory()->Resize();
	//fuelOutputConnection->SetInventory(GetFuelInventory());
	//fuelOutputConnection->SetInventoryAccessIndex(0);
}

bool AAVRPBuildableTruckCharger::CanProduce_Implementation() const
{
	return IsValid(truckStation) && HasPower() && GetFuelInventory()->HasEnoughSpaceForItem(FInventoryItem(mTruckPowerClass));
}

void AAVRPBuildableTruckCharger::Factory_TickProducing(float dt)
{
	Super::Factory_TickProducing(dt);
	if (not HasAuthority()) {
		return;
	}
	GetFuelInventory()->AddStack(FInventoryStack(1500 * dt, mTruckPowerClass), true);
}