// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKongCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Proyectil.h"
#include "Engine/World.h" // Corrige esta l�nea
#include "UObject/ConstructorHelpers.h"

ADonkeyKongCharacter::ADonkeyKongCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	/*InitializeEsferaClass();*/
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADonkeyKongCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADonkeyKongCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADonkeyKongCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADonkeyKongCharacter::TouchStopped);

	// A�ade esta l�nea para vincular la acci�n SpawnEsfera
	PlayerInputComponent->BindAction("SpawnEsfera", IE_Pressed, this, &ADonkeyKongCharacter::SpawnEsfera);
}

void ADonkeyKongCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void ADonkeyKongCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ADonkeyKongCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void ADonkeyKongCharacter::SpawnEsfera()
{
	ProjectileClass = AProyectil::StaticClass();
	if (ProjectileClass)
	{
		// Obtener la ubicaci�n y rotaci�n del jugador
		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f; // Ajustar la distancia de spawn
		FRotator SpawnRotation = GetActorRotation();

		// Par�metros de spawn
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// Spawnear el proyectil
		AProyectil* SpawnedProjectile = GetWorld()->SpawnActor<AProyectil>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

		if (SpawnedProjectile)
		{
			// Inicializar el proyectil con la direcci�n actual del personaje
			FVector ForwardDirection = GetActorForwardVector();
			SpawnedProjectile->Initialize(ForwardDirection);
		}
	}
}

//void ADonkeyKongCharacter::InitializeEsferaClass()
//{
//   ProjectileClass = AProyectil::StaticClass();
//    if (ProjectileClass)
//    {
//        if (GEngine)
//        {
//            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("EsferaClass configurada correctamente"));
//        }
//    }
//    else
//    {
//        if (GEngine)
//        {
//            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No se pudo encontrar la clase Esfera"));
//        }
//    }
//}