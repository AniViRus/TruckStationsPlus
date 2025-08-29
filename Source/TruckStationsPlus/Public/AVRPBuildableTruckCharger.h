#pragma once

#include "CoreMinimal.h"
#include "FGBuildableDockingStation.h"
#include "FGFactoryConnectionComponent.h"
#include "Buildables/FGBuildableFactory.h"
#include "AVRPBuildableTruckCharger.generated.h"

/**
 * Truck Charger which gets snapped to Truck Stations with fuel input connections
 */
UCLASS()
class TRUCKSTATIONSPLUS_API AAVRPBuildableTruckCharger : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	AAVRPBuildableTruckCharger();

	//~ Begin FGBuildableFactory Interface
	virtual bool CanProduce_Implementation() const override;
	virtual void Factory_Tick(float dt) override;
	//~ End FGBuildableFactory Interface

	UFUNCTION( BlueprintCallable, BlueprintPure )
	FORCEINLINE AFGBuildableDockingStation* GetTruckStation() const { return truckStation; }
	//UFUNCTION(BlueprintCallable, BlueprintPure)
	//FORCEINLINE UFGInventoryComponent* GetFuelInventory() const { return mFuelInventory; }
	UFUNCTION()
	FORCEINLINE void SetTruckStation(AFGBuildableDockingStation* newTruckStation) { truckStation = newTruckStation; }
	UFUNCTION()
	FORCEINLINE void ConnectWithStation(UFGFactoryConnectionComponent* stationConnection) { fuelOutputConnection->SetConnection(stationConnection); }
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UFGItemDescriptor> mTruckPowerClass;
private:
	UPROPERTY(SaveGame)
	AFGBuildableDockingStation* truckStation;
	//UPROPERTY(EditAnywhere, SaveGame)
	//UFGInventoryComponent* mFuelInventory;
	UPROPERTY(EditAnywhere, SaveGame)
	UFGFactoryConnectionComponent* fuelOutputConnection;
};
