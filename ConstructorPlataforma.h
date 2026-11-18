// Evita que este header se incluya mas de una vez.
#pragma once

// Tipos basicos de Unreal.
#include "CoreMinimal.h"
// Clase base UObject (el Builder no necesita estar en el nivel, es solo logica).
#include "UObject/NoExportTypes.h"
// Archivo generado por Unreal Header Tool; siempre el ultimo include.
#include "ConstructorPlataforma.generated.h"

// Declaraciones adelantadas para evitar includes pesados.
class APlataforma;
class AComponentePlataforma;
class UWorld;

/**
 * PATRON BUILDER: "BUILDER" (constructor abstracto).
 * Define los PASOS para construir una plataforma. Los Builders concretos
 * deciden COMO se construye cada paso.
 */
UCLASS(Abstract) // Abstract: no se puede instanciar directamente, solo sus hijas.
class LAB_7_API UConstructorPlataforma : public UObject
{
	GENERATED_BODY() // Codigo interno generado por Unreal.

public: // Seccion publica.
	// Guarda el mundo y la ubicacion donde se construira la plataforma.
	void Inicializar(UWorld* NuevoMundo, const FVector& NuevaUbicacion);

	// Crea una plataforma nueva y vacia (se llama antes de empezar a construir).
	virtual void Reiniciar();

	// PASO 1: construir el piso. Pura virtual: cada Builder concreto la implementa.
	virtual void ConstruirPiso() PURE_VIRTUAL(UConstructorPlataforma::ConstruirPiso, );

	// PASO 2: construir las paredes/barandas. Pura virtual.
	virtual void ConstruirParedes() PURE_VIRTUAL(UConstructorPlataforma::ConstruirParedes, );

	// PASO 3: construir el techo. Pura virtual.
	virtual void ConstruirTecho() PURE_VIRTUAL(UConstructorPlataforma::ConstruirTecho, );

	// PASO 4: construir la escalera de acceso. Pura virtual.
	virtual void ConstruirEscalera() PURE_VIRTUAL(UConstructorPlataforma::ConstruirEscalera, );

	// Entrega la plataforma terminada y suelta la referencia interna.
	virtual APlataforma* ObtenerPlataforma();

protected: // Seccion protegida: solo para esta clase y sus hijas.
	// Nombre descriptivo que los hijos pueden sobrescribir.
	virtual FString ObtenerNombreTipo() const;

	// Metodo ayudante: crea una pieza, la configura y la agrega a la plataforma actual.
	AComponentePlataforma* CrearComponente(TSubclassOf<AComponentePlataforma> Clase, const FVector& OffsetLocal, const FVector& Escala, const FLinearColor& Color);

	// Mundo donde se crearan las piezas.
	UPROPERTY()
	UWorld* Mundo;

	// Ubicacion base de la plataforma en el mundo.
	FVector Ubicacion;

	// Plataforma que se esta construyendo actualmente.
	UPROPERTY()
	APlataforma* PlataformaActual;
};
