// Incluye el header de esta clase.
#include "DirectorPlataforma.h"
// Builder abstracto (para llamar a sus metodos).
#include "ConstructorPlataforma.h"
// Builder concreto #1.
#include "ConstructorPlataformaBasica.h"
// Builder concreto #2.
#include "ConstructorPlataformaTorre.h"
// Producto final.
#include "Plataforma.h"
// UWorld (para GetWorld).
#include "Engine/World.h"

// Constructor del Director.
ADirectorPlataforma::ADirectorPlataforma()
{
	// Sin Tick: solo actua una vez en BeginPlay.
	PrimaryActorTick.bCanEverTick = false;
	// Separacion por defecto entre plataformas: 1200 unidades (12 metros).
	SeparacionPlataformas = 1200.f;
	// Inicializa los punteros en nulo.
	ConstructorBasica = nullptr;
	ConstructorTorre = nullptr;
}

// Se ejecuta cuando comienza el juego.
void ADirectorPlataforma::BeginPlay()
{
	// Llama al BeginPlay de la clase padre (obligatorio).
	Super::BeginPlay();

	// Sin mundo no se puede construir nada.
	if (!GetWorld())
	{
		return;
	}

	// Crea los Builders concretos (son UObject, se crean con NewObject; "this" es su dueno).
	ConstructorBasica = NewObject<UConstructorPlataformaBasica>(this);
	ConstructorTorre = NewObject<UConstructorPlataformaTorre>(this);

	// Ubicacion base = donde esta el Director en el nivel.
	const FVector Base = GetActorLocation();

	// Plataforma 1: Builder Basico + receta simple (piso y escalera).
	ConstruirYMostrar(ConstructorBasica, Base, false);
	// Plataforma 2: Builder Basico + receta completa (piso, barandas y escalera; sin techo).
	ConstruirYMostrar(ConstructorBasica, Base + FVector(0.f, SeparacionPlataformas, 0.f), true);
	// Plataforma 3: Builder Torre + receta completa (piso, paredes, techo y escalera).
	ConstruirYMostrar(ConstructorTorre, Base + FVector(0.f, SeparacionPlataformas * 2.f, 0.f), true);
}

// Receta simple: piso + escalera.
void ADirectorPlataforma::ConstruirPlataformaSimple(UConstructorPlataforma* Constructor)
{
	// Si no hay Builder, no hace nada.
	if (!Constructor)
	{
		return;
	}
	// Prepara una plataforma nueva y vacia.
	Constructor->Reiniciar();
	// Construye el piso.
	Constructor->ConstruirPiso();
	// Construye la escalera.
	Constructor->ConstruirEscalera();
}

// Receta completa: piso + paredes + techo + escalera.
void ADirectorPlataforma::ConstruirPlataformaCompleta(UConstructorPlataforma* Constructor)
{
	// Si no hay Builder, no hace nada.
	if (!Constructor)
	{
		return;
	}
	// Prepara una plataforma nueva y vacia.
	Constructor->Reiniciar();
	// Construye el piso.
	Constructor->ConstruirPiso();
	// Construye las paredes.
	Constructor->ConstruirParedes();
	// Construye el techo.
	Constructor->ConstruirTecho();
	// Construye la escalera.
	Constructor->ConstruirEscalera();
}

// Ayudante que ejecuta una receta y muestra el resultado.
void ADirectorPlataforma::ConstruirYMostrar(UConstructorPlataforma* Constructor, const FVector& Ubicacion, bool bCompleta)
{
	// Valida el Builder.
	if (!Constructor)
	{
		return;
	}

	// Indica al Builder en que mundo y posicion construir.
	Constructor->Inicializar(GetWorld(), Ubicacion);

	// Elige la receta segun el parametro.
	if (bCompleta)
	{
		// Receta completa.
		ConstruirPlataformaCompleta(Constructor);
	}
	else
	{
		// Receta simple.
		ConstruirPlataformaSimple(Constructor);
	}

	// Pide al Builder el producto terminado.
	APlataforma* Resultado = Constructor->ObtenerPlataforma();
	// Si existe, muestra de que piezas esta hecha.
	if (Resultado)
	{
		Resultado->MostrarComposicion();
	}
}
