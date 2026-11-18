// Incluye el header de esta clase.
#include "Plataforma.h"
// Necesitamos la definicion completa de las piezas.
#include "ComponentePlataforma.h"
// Componente de escena (raiz).
#include "Components/SceneComponent.h"
// Acceso a GEngine para mostrar mensajes en pantalla.
#include "Engine/Engine.h"

// Define una categoria de Log propia para filtrar mensajes en la ventana Output Log.
DEFINE_LOG_CATEGORY_STATIC(LogPlataforma, Log, All);

// Constructor de la plataforma.
APlataforma::APlataforma()
{
	// Sin Tick: la plataforma es estatica y no necesita actualizarse.
	PrimaryActorTick.bCanEverTick = false;

	// Crea el componente raiz como subobjeto.
	Raiz = CreateDefaultSubobject<USceneComponent>(TEXT("Raiz"));
	// Lo define como raiz del actor.
	RootComponent = Raiz;

	// Nombre inicial por defecto.
	NombrePlataforma = TEXT("Plataforma");
}

// Agrega una pieza a la plataforma.
void APlataforma::AgregarComponente(AComponentePlataforma* Componente)
{
	// Si el puntero es nulo, no hace nada (evita crashes).
	if (!Componente)
	{
		return;
	}

	// Guarda la pieza en la lista.
	Componentes.Add(Componente);
	// La une al actor de la plataforma conservando su posicion y escala en el mundo.
	Componente->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
}

// Muestra de que piezas esta hecha la plataforma.
void APlataforma::MostrarComposicion() const
{
	// Mapa: tipo de pieza -> cantidad de piezas de ese tipo.
	TMap<FString, int32> Conteo;

	// Recorre todas las piezas guardadas.
	for (const AComponentePlataforma* Componente : Componentes)
	{
		// Solo cuenta piezas validas.
		if (Componente)
		{
			// Suma 1 al contador de ese tipo (lo crea en 0 si no existia).
			Conteo.FindOrAdd(Componente->ObtenerTipo())++;
		}
	}

	// Empieza el texto con el nombre de la plataforma.
	FString Texto = FString::Printf(TEXT("%s -> "), *NombrePlataforma);

	// Recorre el mapa para anexar "Tipo xCantidad".
	for (const TPair<FString, int32>& Par : Conteo)
	{
		// Anexa el tipo y su cantidad al texto.
		Texto += FString::Printf(TEXT("%s x%d   "), *Par.Key, Par.Value);
	}

	// Escribe el resultado en el Output Log.
	UE_LOG(LogPlataforma, Log, TEXT("%s"), *Texto);

	// Si el motor esta disponible, tambien lo muestra en pantalla 15 segundos.
	if (GEngine)
	{
		// -1 = mensaje nuevo (no reemplaza a otro), 15 seg, color amarillo.
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, Texto);
	}
}

// Cambia el nombre de la plataforma.
void APlataforma::AsignarNombre(const FString& NuevoNombre)
{
	// Guarda el nuevo nombre.
	NombrePlataforma = NuevoNombre;
}
