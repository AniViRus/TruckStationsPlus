#pragma once

#include "CoreMinimal.h"
#include "FGConstructDisqualifier.h"
#include "Hologram/FGBuildableHologram.h"
#include "FGBuildableDockingStation.h"
#include "FGFactoryConnectionComponent.h"
#include "AVRPTruckChargerHologram.generated.h"

#define LOCTEXT_NAMESPACE "TruckStationsPlusLocnamespace"
UCLASS()
class TRUCKSTATIONSPLUS_API UTruckChargerCD_MustSnapToTruckStation : public UFGConstructDisqualifier
{
	GENERATED_BODY()
public:
	UTruckChargerCD_MustSnapToTruckStation()
	{
		mDisqfualifyingText = LOCTEXT("TruckCharger_MustSnapToTruckStation", "Must snap to a Truck Station!");
	}
};

UCLASS()
class TRUCKSTATIONSPLUS_API UTruckChargerCD_NoFuelInput : public UFGConstructDisqualifier
{
	GENERATED_BODY()
public:
	UTruckChargerCD_NoFuelInput()
	{
		mDisqfualifyingText = LOCTEXT("TruckCharger_NoFuelInput", "Truck Station has no fuel input connection!");
	}
};

UCLASS()
class TRUCKSTATIONSPLUS_API UTruckChargerCD_FuelInputOccupied : public UFGConstructDisqualifier
{
	GENERATED_BODY()
public:
	UTruckChargerCD_FuelInputOccupied()
	{
		mDisqfualifyingText = LOCTEXT("TruckCharger_FuelInputOccupied", "Fuel input connection is occupied!");
	}
};

#undef LOCTEXT_NAMESPACE

/**
 * Hologram for Truck Charger
 */
UCLASS()
class TRUCKSTATIONSPLUS_API AAVRPTruckChargerHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AAVRPTruckChargerHologram();
protected:
	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	virtual bool TrySnapToActor(const FHitResult& hitResult) override;
	virtual void ConfigureActor(class AFGBuildable* inBuildable) const override;
	virtual void ConfigureComponents(class AFGBuildable* inBuildable) const override;
	virtual void CheckValidPlacement() override;
private:
	UPROPERTY( Transient )
	AFGBuildableDockingStation* Snapped = nullptr;
	UPROPERTY(Transient)
	UFGFactoryConnectionComponent* SnappedFactoryConnection = nullptr;
};