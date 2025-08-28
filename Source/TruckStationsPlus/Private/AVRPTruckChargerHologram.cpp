#include "AVRPTruckChargerHologram.h"
#include "AVRPBuildableTruckCharger.h"
#include "FGFactoryConnectionComponent.h"

AAVRPTruckChargerHologram::AAVRPTruckChargerHologram() : Super() {

}

bool AAVRPTruckChargerHologram::TrySnapToActor(const FHitResult& hitResult)
{
	const auto Actor = hitResult.GetActor();
	if (!IsValid(Actor) || !Actor->IsA<AFGBuildableDockingStation>())
	{
		Snapped = nullptr;
		SnappedFactoryConnection = nullptr;
		AddConstructDisqualifier(UTruckChargerCD_MustSnapToTruckStation::StaticClass());
		return false;
	}
	Snapped = Cast<AFGBuildableDockingStation>(Actor);
	Snapped->ForEachComponent<UFGFactoryConnectionComponent>(true, [&](UFGFactoryConnectionComponent* FactoryConn) {
		if (FactoryConn->ComponentHasTag("Fuel") && FactoryConn->GetDirection() == EFactoryConnectionDirection::FCD_INPUT) {
			SnappedFactoryConnection = FactoryConn;
		}
		});
	if (!IsValid(SnappedFactoryConnection)) {
		Snapped = nullptr;
		SnappedFactoryConnection = nullptr;
		AddConstructDisqualifier(UTruckChargerCD_NoFuelInput::StaticClass());
		return false;
	}
	if (!SnappedFactoryConnection->IsConnected())
	{
		SetActorLocationAndRotation(SnappedFactoryConnection->GetComponentLocation(), SnappedFactoryConnection->GetComponentRotation());
		return true;
	}
	Snapped = nullptr;
	SnappedFactoryConnection = nullptr;
	AddConstructDisqualifier(UTruckChargerCD_FuelInputOccupied::StaticClass());
	return false;
}

void AAVRPTruckChargerHologram::ConfigureActor(AFGBuildable* inBuildable) const
{
	Super::ConfigureActor(inBuildable);
	Cast<AAVRPBuildableTruckCharger>(inBuildable)->SetTruckStation(Snapped);
}

void AAVRPTruckChargerHologram::ConfigureComponents(AFGBuildable* inBuildable) const
{
	Super::ConfigureComponents(inBuildable);
	Cast<AAVRPBuildableTruckCharger>(inBuildable)->ConnectWithStation(SnappedFactoryConnection);
}
