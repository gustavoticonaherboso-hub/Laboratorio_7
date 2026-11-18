// Evita que este header se incluya mas de una vez.
#pragma once

// Tipos basicos de Unreal.
#include "CoreMinimal.h"
// Clase base AActor.
#include "GameFramework/Actor.h"
// Archivo generado por Unreal Header Tool; siempre el ultimo include.
#include "DirectorPlataforma.generated.h"

// Declaracion adelantada del Builder abstracto.
class UConstructorPlataforma;

/**
 * PATRON BUILDER: "DIRECTOR".
 * Conoce el ORDEN de los pasos de construccion y los pide a cualquier Builder.
 * Se coloca en el nivel; al presionar Play construye varias plataformas de ejemplo.
 */
UCLASS() // Registra la clase en el sistema de reflexion.
class LAB_7_API ADirectorPlataforma : public AActor
{
	GENERATED_BODY() // Codigo interno generado por Unreal.

public: // Seccion publica.
	// Constructor del Director.
	ADirectorPlataforma();

	// Receta 1: construye solo piso y escalera.
	void ConstruirPlataformaSimple(UConstructorPlataforma* Constructor);

	// Receta 2: construye piso, paredes, techo y escalera.
	void ConstruirPlataformaCompleta(UConstructorPlataforma* Constructor);

protected: // Seccion protegida.
	// Se ejecuta al iniciar el juego (Play); aqui se crean las plataformas de ejemplo.
	virtual void BeginPlay() override;

	// Ayudante: inicializa un Builder, ejecuta una receta y muestra el resultado.
	void ConstruirYMostrar(UConstructorPlataforma* Constructor, const FVector& Ubicacion, bool bCompleta);

	// Separacion (en unidades) entre una plataforma y la siguiente en el eje Y.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Director")
	float SeparacionPlataformas;

	// Builder concreto #1 (referencia para que no lo borre el recolector de basura).
	UPROPERTY()
	UConstructorPlataforma* ConstructorBasica;

	// Builder concreto #2.
	UPROPERTY()
	UConstructorPlataforma* ConstructorTorre;
};
