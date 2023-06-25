#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitboxActor.generated.h"


UENUM(BlueprintType)
enum class HitboxEnum : uint8
{
	HB_Proximity UMETA(DisplayName = "Proximity"),
	HB_Strike UMETA(DisplayName = "Strike"),
	HB_Hurtbox UMETA(DisplayName = "Hurtbox")
};

UCLASS()
class BLITZCRANKFGC_API AHitboxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitboxActor();


	//Hitbox Enum Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		HitboxEnum hitboxType;

	//Location to spawn the hitbox
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		FVector hitboxLocation;

	//How much damage the hitbox does
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float hitboxDamage;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
