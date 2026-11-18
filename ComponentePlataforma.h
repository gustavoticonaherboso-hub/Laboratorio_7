// Evita que este header se incluya mas de una vez.
#pragma once

// Tipos basicos de Unreal (FString, FVector, FLinearColor...).
#include "CoreMinimal.h"
// Clase base AActor de la que hereda todo objeto colocable en el nivel.
#include "GameFramework/Actor.h"
// Archivo generado por Unreal Header Tool; SIEMPRE debe ser el ultimo include.
#include "ComponentePlataforma.generated.h"

// Declaracion adelantada: evita incluir headers pesados aqui.
class UStaticMeshComponent;
// Declaracion adelantada del material dinamico (para cambiar el color en ejecucion).
class UMaterialInstanceDynamic;

/**
 * PARTE DEL PATRON BUILDER: "Componente" (pieza basica).
 * Clase base de todas las piezas que forman una plataforma (piso, pared, techo, escalera).
 */
UCLASS() // Macro que registra la clase en el sistema de reflexion de Unreal.
class LAB_7_API AComponentePlataforma : public AActor // LAB_7_API exporta la clase del modulo Lab_7.
{
	GENERATED_BODY() // Macro que genera el codigo interno necesario de Unreal.

public: // Seccion publica: accesible desde cualquier clase.
	// Constructor: crea la malla (cubo) y le asigna material.
	AComponentePlataforma();

	// Ajusta la escala (tamano) y el color de la pieza; lo usan los Builders.
	void Configurar(const FVector& NuevaEscala, const FLinearColor& NuevoColor);

	// Devuelve el nombre del tipo de pieza ("Piso", "Pared"...); las clases hijas lo sobrescriben.
	virtual FString ObtenerTipo() const;

protected: // Seccion protegida: accesible por esta clase y sus hijas.
	// Malla estatica (un cubo) que representa visualmente la pieza.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componente") // Visible en el editor, solo lectura en Blueprint.
	UStaticMeshComponent* Malla;

	// Material dinamico que permite cambiar el color en tiempo de ejecucion.
	UPROPERTY() // UPROPERTY evita que el recolector de basura destruya el objeto.
	UMaterialInstanceDynamic* MaterialDinamico;
};
