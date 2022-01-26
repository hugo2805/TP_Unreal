#include "Grab.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"

UGrab::UGrab()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	fltDistance = 200;

	// ...
}

void UGrab::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();

	/*SetInputComponent();
	if (inputComponent) {
		inputComponent->BindAction("Grab", IE_Pressed, this, &UCGrab::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UCGrab::Release);
	}
	*/
	// ...

}

void UGrab::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT("Point Line Start : %s"), *PointLineStart().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Point Line End : %s"), *PointLineEnd().ToString());

	UpdateGrabLocation();

	// ...
}

FHitResult UGrab::GetFirstPhysicsBodyInReach()
{
	UWorld* World = GetWorld();

	FHitResult HitResult;

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	if (World->LineTraceSingleByChannel(HitResult, PointLineStart(), PointLineEnd(), ECollisionChannel::ECC_PhysicsBody, TraceParameters)) {
		DrawDebugLine(World, PointLineStart(), PointLineEnd(), FColor::Green, false, 5.f);

	}
	else {
		DrawDebugLine(World, PointLineStart(), PointLineEnd(), FColor::Red, false, 5.f);
	}


	return HitResult;
}

FVector UGrab::PointLineStart() const
{
	//ou GetPlayerViewPoint()
	FVector vStartPoint = GetOwner()->GetActorLocation();

	return vStartPoint;
}

FVector UGrab::PointLineEnd() const
{
	AActor* Actor = GetOwner();
	//ou GetPlayerViewPoint()
	FVector vEndPoint = Actor->GetActorForwardVector() * fltDistance + PointLineStart();

	return vEndPoint;
}

void UGrab::SetInputComponent()
{
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (ensure(inputComponent)) {
		UE_LOG(LogTemp, Warning, TEXT("Component Input Find"));
	}
}

void UGrab::FindPhysicsHandleComponent()
{

	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (ensure(physicsHandle)) {
		UE_LOG(LogTemp, Warning, TEXT("PhysicsHandle Component find"));

	}
}

void UGrab::Handle()
{

	FHitResult Hit = GetFirstPhysicsBodyInReach();

	UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit) {

		physicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation());
	}
}

void UGrab::Grab()
{
	Handle();
}

void UGrab::Release()
{
	physicsHandle->ReleaseComponent();
}

void UGrab::UpdateGrabLocation()const
{
	//Update ref PhysicsHandle component
	if (physicsHandle->GrabbedComponent) {

		physicsHandle->SetTargetLocation(PointLineEnd());
	}
}
