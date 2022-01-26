#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grab.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CYCLE_3_BXLS_NL_2021_API UGrab : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrab();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	FHitResult GetFirstPhysicsBodyInReach();

	FVector PointLineStart() const;

	FVector PointLineEnd()const;

	void SetInputComponent();

	void FindPhysicsHandleComponent();

	void Handle();

	UFUNCTION(BlueprintCallable, Category = "Grab")
		void Grab();

	UFUNCTION(BlueprintCallable, Category = "Grab")
		void Release();

	void UpdateGrabLocation()const;




private:

	UPROPERTY(EditDefaultsOnly, Category = "Dist Propoerty")
		float fltDistance;

	UInputComponent* inputComponent;

	UPhysicsHandleComponent* physicsHandle;


};