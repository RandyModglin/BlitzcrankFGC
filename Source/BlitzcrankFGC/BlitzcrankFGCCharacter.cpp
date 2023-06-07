// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlitzcrankFGCCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BlitzcrankFGC/Dummy.h"
#include "BlitzcrankFGC/BlitzcrankFGCGameMode.h"

ABlitzcrankFGCCharacter::ABlitzcrankFGCCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 250.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)


	//Set Starting Direction Input
	directionalInput = EDirectionalInput::VE_Default;

	//Reference to Dummy, set in Gamemode Blueprint
	dummyRef = nullptr;

	//Model variables
	transform = FTransform();
	scale = FVector(1.0f, 1.0f, 1.0f);

	//Player Floats
	removeInputFromBufferTime = 1.0f;

	//Player Bools
	isLightAttacking = false;
	isMediumAttacking = false;
	isHeavyAttacking = false;
	isSpecialAttacking = false;
	isCrouching = false;
	isAirborne = false;
	isFlipped = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABlitzcrankFGCCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABlitzcrankFGCCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABlitzcrankFGCCharacter::StopJumping);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ABlitzcrankFGCCharacter::StartCrouching);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ABlitzcrankFGCCharacter::StopCrouching);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABlitzcrankFGCCharacter::MoveRight);

	PlayerInputComponent->BindAction("AttackL", IE_Pressed, this, &ABlitzcrankFGCCharacter::StartAttackL);
	//PlayerInputComponent->BindAction("AttackL", IE_Released, this, &ABlitzcrankFGCCharacter::StopAttackL);
	PlayerInputComponent->BindAction("AttackM", IE_Pressed, this, &ABlitzcrankFGCCharacter::StartAttackM);
	//PlayerInputComponent->BindAction("AttackM", IE_Released, this, &ABlitzcrankFGCCharacter::StopAttackM);
	PlayerInputComponent->BindAction("AttackH", IE_Pressed, this, &ABlitzcrankFGCCharacter::StartAttackH);
	//PlayerInputComponent->BindAction("AttackH", IE_Released, this, &ABlitzcrankFGCCharacter::StopAttackH);
	PlayerInputComponent->BindAction("AttackS", IE_Pressed, this, &ABlitzcrankFGCCharacter::StartAttackS);
	//PlayerInputComponent->BindAction("AttackS", IE_Released, this, &ABlitzcrankFGCCharacter::StopAttacks);

	//PlayerInputComponent->BindAction("AddToInputBuffer", IE_Pressed, this, &ABlitzcrankFGCCharacter::AddInputToBuffer);
}

void ABlitzcrankFGCCharacter::MoveRight(float Value)
{
	if (!isCrouching) {

		//UE_LOG(LogTemp, Warning, TEXT("Directional Input: %f"), Value);

		if (directionalInput != EDirectionalInput::VE_Jumping) {

			if (Value > 0.20f) {
				GetCharacterMovement()->MaxWalkSpeed = 225.f;
				directionalInput = EDirectionalInput::VE_MovingRight;
			}
			else if (Value < -0.20f) {
				GetCharacterMovement()->MaxWalkSpeed = 150.f;
				directionalInput = EDirectionalInput::VE_MovingLeft;
			}
			else {
				directionalInput = EDirectionalInput::VE_Default;
			}

			// add movement in that direction
			AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
		}
	}
}

void ABlitzcrankFGCCharacter::Jump()
{
	ACharacter::Jump();
	directionalInput = EDirectionalInput::VE_Jumping;
	isAirborne = true;
}

void ABlitzcrankFGCCharacter::StopJumping()
{
	ACharacter::StopJumping();
}

void ABlitzcrankFGCCharacter::Landed(const FHitResult& Hit)
{
	directionalInput = EDirectionalInput::VE_Default;
	isAirborne = false;
}

void ABlitzcrankFGCCharacter::StartCrouching()
{
	UE_LOG(LogTemp, Warning, TEXT("Started Crouching"));
	isCrouching = true;
}

void ABlitzcrankFGCCharacter::StopCrouching()
{
	UE_LOG(LogTemp, Warning, TEXT("Stopped Crouching"));
		isCrouching = false;
}

void ABlitzcrankFGCCharacter::StartAttackL()
{
	UE_LOG(LogTemp, Warning, TEXT("Doing a Light Attack!"));
	isLightAttacking = true;
}

void ABlitzcrankFGCCharacter::StartAttackM()
{
	UE_LOG(LogTemp, Warning, TEXT("Doing a Medium Attack!"));
	isMediumAttacking = true;
}

void ABlitzcrankFGCCharacter::StartAttackH()
{
	UE_LOG(LogTemp, Warning, TEXT("Doing a Heavy Attack!"));
	isHeavyAttacking = true;
}

void ABlitzcrankFGCCharacter::StartAttackS()
{
	UE_LOG(LogTemp, Warning, TEXT("Doing a Special Attack!"));
	isSpecialAttacking = true;
}

void ABlitzcrankFGCCharacter::AddInputToBuffer(FInputInfo _inputInfo)
{
	inputBuffer.Add(_inputInfo);
}

void ABlitzcrankFGCCharacter::RemoveInputFromBuffer()
{
	
}

void ABlitzcrankFGCCharacter::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (directionalInput != EDirectionalInput::VE_Jumping) {
		if (dummyRef)
		{
			if (auto characterMovement = GetCharacterMovement()) {
				if (auto dummyMovement = dummyRef->GetCharacterMovement())
				{
					if (dummyMovement->GetActorLocation().Y >= characterMovement->GetActorLocation().Y)
					{
						if (isFlipped)
						{
							if (auto mesh = GetCapsuleComponent()->GetChildComponent(1)) //Get Mesh from Capsule Component
							{
								transform = mesh->GetRelativeTransform();
								scale = transform.GetScale3D();
								scale.Y = -100;
								transform.SetScale3D(scale);
								mesh->SetRelativeTransform(transform);
							}
							dummyRef->FlipDummy();
							isFlipped = false;
						}
					}

					else
					{
						if (!isFlipped)
						{
							if (auto mesh = GetCapsuleComponent()->GetChildComponent(1)) //Get Mesh from Capsule Component
							{
								transform = mesh->GetRelativeTransform();
								scale = transform.GetScale3D();
								scale.Y = 100;
								transform.SetScale3D(scale);
								mesh->SetRelativeTransform(transform);
							}
							dummyRef->FlipDummy();
							isFlipped = true;
						}
					}
				}
			}
		}
	}
}

