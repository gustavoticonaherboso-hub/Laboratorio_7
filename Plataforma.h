// Evita que este header se incluya mas de una vez.
#pragma once

// Tipos basicos de Unreal.
#include "CoreMinimal.h"
// Clase base AActor.
#include "GameFramework/Actor.h"
// Archivo generado por Unreal Header Tool; siempre el ultimo include.
#include "Plataforma.generated.h"

// Declaracion adelantada de las piezas que contiene la plataforma.
class AComponentePlataforma;

/**
 * PATRON BUILDER: "PRODUCTO".
 * Es el objeto complejo final que los Builders construyen pieza por pieza.
 */
UCLASS() // Registra la clase en el sistema de reflexion.
class LAB_7_API APlataforma : public AActor // Exportada con la macro del modulo Lab_7.
{
	GENERATED_BODY() // Codigo interno generado por Unreal.

public: // Seccion publica.
	// Constructor: crea el componente raiz.
	APlataforma();

	// Agrega una pieza a la plataforma (la guarda y la une al actor raiz).
	void AgregarComponente(AComponentePlataforma* Componente);

	// Imprime en pantalla y en el Log que piezas componen la plataforma.
	void MostrarComposicion() const;

	// Asigna un nombre descriptivo a la plataforma.
	void AsignarNombre(const FString& NuevoNombre);

protected: // Seccion protegida.
	// Componente raiz invisible; las piezas se enlazan (attach) a este.
	UPROPERTY(VisibleAnywhere, Category = "Plataforma")
	USceneComponent* Raiz;

	// Lista de todas las piezas que forman esta plataforma.
	UPROPERTY(VisibleAnywhere, Category = "Plataforma")
	TArray<AComponentePlataforma*> Componentes;

	// Nombre descriptivo (por ejemplo "Plataforma Basica").
	UPROPERTY(VisibleAnywhere, Category = "Plataforma")
	FString NombrePlataforma;
};
