// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong_L01GameMode.h"
#include "DonkeyKong_L01Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Obstaculo.h"
#include "ComponentePlataforma.h"
#include "Enemigo.h"

#include <ctime>	
#include <cstdlib>

ADonkeyKong_L01GameMode::ADonkeyKong_L01GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	obstaculo01 = nullptr;
	player01 = nullptr;

	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		player01 = Cast<ADonkeyKong_L01Character>(PlayerPawnBPClass.Class);
	}
}

void ADonkeyKong_L01GameMode::BeginPlay()
{
	Super::BeginPlay();

	FVector posicionInicial = FVector(1160.0f, -1100.0f, 400.f);
	FRotator rotacionInicial = FRotator(0.0f, 0.0f, 10.0f);
	FTransform SpawnLocationCP;
	FTransform SpawnLocation6;
	FTransform SpawnLocation7;
	FTransform SpawnLocation8;
	FTransform SpawnLocationCP2;
	float anchoComponentePlataforma = 600.0f;
	float incrementoAltoComponentePlataforma = -105.0f;
	float incrementoAltoEntrePisos = 350.0f;
	float incrementoInicioPiso = 50.0f;
	int ncp = 0;

	//muro
	//SpawnLocation7.SetLocation(FVector(1070.0f, -200.0f, 3600.0f));
	//SpawnLocation7.SetRotation(FQuat(FRotator(0.0f, 180.0f, 0.0f)));

	//// Generar el actor Plataforma
	//GetWorld()->SpawnActor<Amuro>(Amuro::StaticClass(), SpawnLocation7);


	////muroexplosivo
	//SpawnLocation8.SetLocation(FVector(1070.0f, -200.0f, 3900.0f));
	//SpawnLocation8.SetRotation(FQuat(FRotator(0.0f, 180.0f, 0.0f)));

	//// Generar el actor Plataforma
	//GetWorld()->SpawnActor<Amuro_explosivo>(Amuro_explosivo::StaticClass(), SpawnLocation8);








	for (int npp = 0; npp < 5; npp++) {
		rotacionInicial.Roll = rotacionInicial.Roll * -1;
		incrementoInicioPiso = incrementoInicioPiso * -1;
		incrementoAltoComponentePlataforma = incrementoAltoComponentePlataforma * -1;
		if (npp % 2 == 0) {
			SpawnLocationCP.SetRotation(FQuat(rotacionInicial));

			for (ncp = 0; ncp < 10; ncp++) {
				SpawnLocationCP.SetLocation(FVector(posicionInicial.X, posicionInicial.Y + anchoComponentePlataforma * ncp, posicionInicial.Z));
				componentesPlataforma.Add(GetWorld()->SpawnActor<AComponentePlataforma>(AComponentePlataforma::StaticClass(), SpawnLocationCP));
				if (ncp < 9) {
					posicionInicial.Z = posicionInicial.Z + incrementoAltoComponentePlataforma;
				}


			}
		}
		else {
			// spawnear sin rotacion
			SpawnLocationCP2.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f))); // Asegurarse de que la rotación sea cero


			for (ncp = 0; ncp < 10; ncp++) {
				SpawnLocationCP2.SetLocation(FVector(posicionInicial.X, posicionInicial.Y + anchoComponentePlataforma * ncp, posicionInicial.Z));
				componentesPlataforma.Add(GetWorld()->SpawnActor<AComponentePlataforma>(AComponentePlataforma::StaticClass(), SpawnLocationCP2));
				if (ncp < 9) {
					posicionInicial.Z = posicionInicial.Z;
				}

			}
		}

		posicionInicial.Z = posicionInicial.Z + incrementoAltoEntrePisos;
		posicionInicial.Y = posicionInicial.Y + incrementoInicioPiso;
	}
}
void ADonkeyKong_L01GameMode::mover()
{
	//mover ComponentePlataforma de arriba a abajo
	//mover ComponentePlataforma de abajo a arriba




}




void ADonkeyKong_L01GameMode::Tick(float DeltaTime)
{
}

