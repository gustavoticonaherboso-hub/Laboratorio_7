// Incluye el header de esta clase.
#include "ConstructorPlataforma.h"
// Necesita la definicion de la plataforma (producto).
#include "Plataforma.h"
// Necesita la definicion de las piezas.
#include "ComponentePlataforma.h"
// Necesita UWorld para hacer SpawnActor.
#include "Engine/World.h"

// Guarda el mundo y la ubicacion de construccion.
void UConstructorPlataforma::Inicializar(UWorld* NuevoMundo, const FVector& NuevaUbicacion)
{
	// Guarda el mundo recibido.
	Mundo = NuevoMundo;
	// Guarda la ubicacion base.
	Ubicacion = NuevaUbicacion;
	// Todavia no hay plataforma en construccion.
	PlataformaActual = nullptr;
}

// Crea una plataforma nueva y vacia.
void UConstructorPlataforma::Reiniciar()
{
	// Sin mundo no se puede crear nada.
	if (!Mundo)
	{
		return;
	}

	// Parametros de creacion: aparece siempre aunque haya colisiones.
	FActorSpawnParameters Parametros;
	// Indica que debe crearse aunque otro objeto este en esa posicion.
	Parametros.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Crea el actor APlataforma en la ubicacion base, sin rotacion.
	PlataformaActual = Mundo->SpawnActor<APlataforma>(APlataforma::StaticClass(), Ubicacion, FRotator::ZeroRotator, Parametros);

	// Si se creo correctamente...
	if (PlataformaActual)
	{
		// ...le asigna el nombre del tipo de Builder.
		PlataformaActual->AsignarNombre(ObtenerNombreTipo());
	}
}

// Entrega la plataforma terminada.
APlataforma* UConstructorPlataforma::ObtenerPlataforma()
{
	// Guarda la plataforma actual en una variable local.
	APlataforma* Resultado = PlataformaActual;
	// Suelta la referencia para que el Builder quede listo para otra construccion.
	PlataformaActual = nullptr;
	// Devuelve el producto terminado.
	return Resultado;
}

// Nombre por defecto.
FString UConstructorPlataforma::ObtenerNombreTipo() const
{
	// Los hijos lo sobrescriben con algo mas descriptivo.
	return TEXT("Plataforma");
}

// Crea una pieza y la agrega a la plataforma.
AComponentePlataforma* UConstructorPlataforma::CrearComponente(TSubclassOf<AComponentePlataforma> Clase, const FVector& OffsetLocal, const FVector& Escala, const FLinearColor& Color)
{
	// Validaciones: necesitamos mundo, plataforma en construccion y una clase valida.
	if (!Mundo || !PlataformaActual || Clase.Get() == nullptr)
	{
		return nullptr;
	}

	// Posicion final = ubicacion base + desplazamiento de la pieza.
	const FVector PosicionFinal = Ubicacion + OffsetLocal;

	// Parametros de creacion: siempre aparece.
	FActorSpawnParameters Parametros;
	// Ignora colisiones al crear.
	Parametros.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Crea la pieza en el mundo.
	AComponentePlataforma* Pieza = Mundo->SpawnActor<AComponentePlataforma>(Clase.Get(), PosicionFinal, FRotator::ZeroRotator, Parametros);

	// Si se creo correctamente...
	if (Pieza)
	{
		// ...aplica tamano y color...
		Pieza->Configurar(Escala, Color);
		// ...y la agrega a la plataforma en construccion.
		PlataformaActual->AgregarComponente(Pieza);
	}

	// Devuelve la pieza creada (o nullptr si fallo).
	return Pieza;
}
