// Incluye el header de esta clase.
#include "ComponentePlataforma.h"
// Componente de malla estatica.
#include "Components/StaticMeshComponent.h"
// Material dinamico (para cambiar color).
#include "Materials/MaterialInstanceDynamic.h"
// Interfaz base de materiales.
#include "Materials/MaterialInterface.h"
// Clase UStaticMesh (el asset del cubo).
#include "Engine/StaticMesh.h"
// ConstructorHelpers: permite cargar assets dentro de un constructor.
#include "UObject/ConstructorHelpers.h"

// Constructor de la pieza base.
AComponentePlataforma::AComponentePlataforma()
{
	// Desactiva el Tick (la pieza no necesita actualizarse cada frame; ahorra rendimiento).
	PrimaryActorTick.bCanEverTick = false;

	// Crea el componente de malla estatica como subobjeto del actor.
	Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
	// Hace que la malla sea el componente raiz del actor.
	RootComponent = Malla;
	// Movable permite cambiar escala/posicion en ejecucion sin advertencias.
	Malla->SetMobility(EComponentMobility::Movable);

	// Busca el cubo basico incluido en el motor (100x100x100 unidades).
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaCubo(TEXT("/Engine/BasicShapes/Cube.Cube"));
	// Si se encontro el cubo...
	if (MallaCubo.Succeeded())
	{
		// ...se lo asignamos a la malla.
		Malla->SetStaticMesh(MallaCubo.Object);
	}

	// Busca el material basico del motor (tiene un parametro vectorial llamado "Color").
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialBase(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	// Si se encontro el material...
	if (MaterialBase.Succeeded())
	{
		// ...se lo asignamos al slot 0 de la malla.
		Malla->SetMaterial(0, MaterialBase.Object);
	}

	// Inicializa el puntero del material dinamico en nulo.
	MaterialDinamico = nullptr;
}

// Configura tamano y color de la pieza.
void AComponentePlataforma::Configurar(const FVector& NuevaEscala, const FLinearColor& NuevoColor)
{
	// Aplica la escala al actor completo (cubo de 100 unidades x escala = tamano final).
	SetActorScale3D(NuevaEscala);

	// Si aun no existe el material dinamico...
	if (!MaterialDinamico)
	{
		// ...lo crea a partir del material del slot 0 y lo asigna a la malla.
		MaterialDinamico = Malla->CreateAndSetMaterialInstanceDynamic(0);
	}

	// Si el material dinamico existe...
	if (MaterialDinamico)
	{
		// ...cambia su parametro "Color" por el color pedido.
		MaterialDinamico->SetVectorParameterValue(TEXT("Color"), NuevoColor);
	}
}

// Nombre generico del tipo; las clases hijas lo sobrescriben.
FString AComponentePlataforma::ObtenerTipo() const
{
	// Devuelve un texto por defecto.
	return TEXT("Componente");
}
