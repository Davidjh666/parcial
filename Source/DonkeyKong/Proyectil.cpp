// Fill out your copyright notice in the Description page of Project Settings.


#include "Proyectil.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProyectil::AProyectil()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectilMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (ProjectileMeshAsset.Succeeded())
	{
		ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
		ProjectileMesh->SetWorldScale3D(FVector(0.5f)); // Ajusta el tama�o seg�n sea necesario
		ProjectileMesh->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("Material'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'")));
	}
/*	ProjectileMesh->SetNotifyRigidBodyCollision(true);
	ProjectileMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProyectil::OnHit);*/		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	ProjectileColision = CreateDefaultSubobject<USphereComponent>(TEXT("Barril_Colision"));
	ProjectileColision->SetSphereRadius(50.0f);
	ProjectileColision->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	ProjectileColision->SetVisibility(true);
	ProjectileColision->SetupAttachment(GetRootComponent());

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 100.f; // Velocidad inicial lenta
	ProjectileMovement->MaxSpeed = 100.f; // Velocidad m�xima
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.3f;
	ProjectileMovement->ProjectileGravityScale = 0.0f; // Sin gravedad
}

void AProyectil::Initialize(const FVector& Direction)
{
	ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed;
}

// Called when the game starts or when spawned
void AProyectil::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProyectil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProyectil::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	Destroy();
}

//void AProyectil::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Proyectil hit!"));
//	// Only add impulse and destroy projectile if we hit a physics
//	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
//	{
//		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
//	}
//
//	Destroy();
//}

