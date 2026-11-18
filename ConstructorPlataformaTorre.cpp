// Incluye el header de esta clase.
#include "ConstructorPlataformaTorre.h"
// Pieza: piso.
#include "PlataformaPiso.h"
// Pieza: pared.
#include "PlataformaPared.h"
// Pieza: techo.
#include "PlataformaTecho.h"
// Pieza: escalera (escalon).
#include "PlataformaEscalera.h"

// Constantes de este Builder en un namespace con nombre propio (evita choques en los "unity builds" de Unreal; 100 uu = 1 metro).
namespace ConfigTorre
{
	// Mitad del lado de la plataforma (lado total = 600).
	constexpr float Mitad = 300.f;
	// Altura de la superficie del piso.
	constexpr float AlturaPiso = 100.f;
	// Grosor del piso.
	constexpr float GrosorPiso = 20.f;
	// Altura de las paredes.
	constexpr float AlturaPared = 250.f;
	// Grosor de las paredes.
	constexpr float GrosorPared = 20.f;
	// Grosor del techo.
	constexpr float GrosorTecho = 20.f;
	// Cantidad de escalones.
	constexpr int32 NumEscalones = 5;
	// Ancho de la escalera (eje Y).
	constexpr float AnchoEscalera = 250.f;
	// Profundidad de cada escalon (eje X).
	constexpr float FondoEscalon = 50.f;
}

// PASO 1: construye el piso.
void UConstructorPlataformaTorre::ConstruirPiso()
{
	// Lado completo del piso.
	const float Lado = ConfigTorre::Mitad * 2.f;
	// Crea el piso centrado con su cara superior en ConfigTorre::AlturaPiso.
	CrearComponente(APlataformaPiso::StaticClass(),
		FVector(0.f, 0.f, ConfigTorre::AlturaPiso - ConfigTorre::GrosorPiso / 2.f), // Posicion relativa.
		FVector(Lado / 100.f, Lado / 100.f, ConfigTorre::GrosorPiso / 100.f), // Escala (X, Y, Z).
		FLinearColor(0.2f, 0.2f, 0.25f)); // Color gris azulado.
}

// PASO 2: construye 3 paredes altas (el lado +X queda abierto como entrada).
void UConstructorPlataformaTorre::ConstruirParedes()
{
	// Lado completo.
	const float Lado = ConfigTorre::Mitad * 2.f;
	// Altura del centro de las paredes.
	const float Z = ConfigTorre::AlturaPiso + ConfigTorre::AlturaPared / 2.f;
	// Color de las paredes.
	const FLinearColor Color(0.5f, 0.1f, 0.1f);

	// Pared del lado +Y.
	CrearComponente(APlataformaPared::StaticClass(), FVector(0.f, ConfigTorre::Mitad - ConfigTorre::GrosorPared / 2.f, Z),
		FVector(Lado / 100.f, ConfigTorre::GrosorPared / 100.f, ConfigTorre::AlturaPared / 100.f), Color);
	// Pared del lado -Y.
	CrearComponente(APlataformaPared::StaticClass(), FVector(0.f, -(ConfigTorre::Mitad - ConfigTorre::GrosorPared / 2.f), Z),
		FVector(Lado / 100.f, ConfigTorre::GrosorPared / 100.f, ConfigTorre::AlturaPared / 100.f), Color);
	// Pared del lado -X (fondo).
	CrearComponente(APlataformaPared::StaticClass(), FVector(-(ConfigTorre::Mitad - ConfigTorre::GrosorPared / 2.f), 0.f, Z),
		FVector(ConfigTorre::GrosorPared / 100.f, Lado / 100.f, ConfigTorre::AlturaPared / 100.f), Color);
}

// PASO 3: construye el techo sobre las paredes.
void UConstructorPlataformaTorre::ConstruirTecho()
{
	// Lado completo del techo.
	const float Lado = ConfigTorre::Mitad * 2.f;
	// Altura del centro del techo: piso + paredes + mitad del grosor del techo.
	const float Z = ConfigTorre::AlturaPiso + ConfigTorre::AlturaPared + ConfigTorre::GrosorTecho / 2.f;
	// Crea el techo.
	CrearComponente(APlataformaTecho::StaticClass(), FVector(0.f, 0.f, Z),
		FVector(Lado / 100.f, Lado / 100.f, ConfigTorre::GrosorTecho / 100.f),
		FLinearColor(0.1f, 0.1f, 0.4f)); // Color azul oscuro.
}

// PASO 4: construye la escalera ancha por el lado +X.
void UConstructorPlataformaTorre::ConstruirEscalera()
{
	// Recorre los escalones desde el mas bajo hasta el mas alto.
	for (int32 k = 1; k <= ConfigTorre::NumEscalones; ++k)
	{
		// Altura total del escalon k.
		const float Altura = (ConfigTorre::AlturaPiso / ConfigTorre::NumEscalones) * k;
		// Posicion X: los mas altos quedan junto al piso.
		const float X = ConfigTorre::Mitad + ConfigTorre::FondoEscalon / 2.f + (ConfigTorre::NumEscalones - k) * ConfigTorre::FondoEscalon;
		// Crea el escalon apoyado en el suelo.
		CrearComponente(APlataformaEscalera::StaticClass(), FVector(X, 0.f, Altura / 2.f),
			FVector(ConfigTorre::FondoEscalon / 100.f, ConfigTorre::AnchoEscalera / 100.f, Altura / 100.f),
			FLinearColor(0.7f, 0.7f, 0.7f)); // Color gris claro.
	}
}

// Nombre descriptivo del tipo de plataforma.
FString UConstructorPlataformaTorre::ObtenerNombreTipo() const
{
	// Se mostrara en pantalla al terminar la construccion.
	return TEXT("Plataforma Torre");
}
