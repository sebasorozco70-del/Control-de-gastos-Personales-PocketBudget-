# PocketBudget
## Integrantes 
Sebastian Orozco Quintero

## 📌 Nombre de la aplicación y problema que resuelve
* **Nombre de la aplicación:** PocketBudget (Control de Gastos Personales en Consola).
* **Problema que resuelve:** Permite a los usuarios llevar un registro ordenado y en tiempo real de sus egresos diarios y finanzas personales, calculando de forma automática los balances, ingresos extra y emitiendo alertas cuando el presupuesto límite es superado.

---

## 🛠️ Patrones de Diseño Seleccionados

1. **Creacional: Factory Method**
   * **Rol en la aplicación:** Encapsula y centraliza la lógica de creación de objetos de tipo `Gasto` (distinguiendo entre gastos normales y gastos fijos), evitando que la fachada o la función principal dependan directamente de constructores complejos con operadores `new`.
2. **Estructural: Facade**
   * **Rol en la aplicación:** Oculta la complejidad del sistema interno (manejo de vectores de punteros, cálculos de totales y llamadas al observador) exponiendo una interfaz unificada y limpia (`BilleteraFacade`) para el menú principal.
3. **De Comportamiento: Observer**
   * **Rol en la aplicación:** Desacopla el sistema de notificaciones financieras. La fachada notifica de forma reactiva al observador (`AlertaConsola`) cada vez que se agrega un gasto o un ingreso, actualizando las alertas financieras en pantalla sin mezclar lógica de impresión con la lógica de negocio.

---
Salida de Consola Esperada

```text
=== CONFIGURACION INICIAL POCKETBUDGET ===
Ingrese su presupuesto limite inicial ($): 50000

--- MENU PRINCIPAL ---
1. Registrar gasto normal
2. Registrar gasto fijo (Fabrica)
3. Agregar ingreso extra 💵
4. Ver historial y balance
5. Salir
Seleccione una opcion: 1
Descripcion: Almuerzo
Categoria: Comida
Monto ($): 15000
¡Gasto registrado con exito!
----------------------------------------
💡 [AVISO OBSERVER] Presupuesto total disponible: $35000.00

--- MENU PRINCIPAL ---
1. Registrar gasto normal
2. Registrar gasto fijo (Fabrica)
3. Agregar ingreso extra 💵
4. Ver historial y balance
5. Salir
Seleccione una opcion: 3
Monto del ingreso extra ($): 20000
💵 ¡Ingreso extra de $20000.00 agregado correctamente!
----------------------------------------
💡 [AVISO OBSERVER] Presupuesto total disponible: $55000.00. 

-----

  ##Diagrama de Clases y Relaciones entre Patrones

```mermaid
classDiagram
    class Gasto {
        <<abstract>>
        #string descripcion
        #string categoria
        #double monto
        +getMonto() double
        +mostrar()* void
    }

    class GastoGeneral {
        +GastoGeneral(string desc, string cat, double m)
        +mostrar() void
    }

    class GastoFactory {
        +crearGasto(int tipo, string desc, string cat, double monto) Gasto*
    }

    class ObservadorPresupuesto {
        <<interface>>
        +actualizar(double totalGastado, double limite)* void
    }

    class AlertaConsola {
        +actualizar(double totalGastado, double limite) void
    }

    class BilleteraFacade {
        -vector~Gasto*~ gastos
        -double presupuestoLimite
        -ObservadorPresupuesto* observador
        +BilleteraFacade(double limite, ObservadorPresupuesto* obs)
        +registrarGasto(int tipo, string desc, string cat, double monto) void
        +agregarIngresoExtra(double montoExtra) void
        +calcularTotalGastos() double
        +notificarObservador() void
        +mostrarHistorial() void
    }

    Gasto <|-- GastoGeneral : Hereda
    GastoFactory ..> Gasto : Produce (Factory Method)
    ObservadorPresupuesto <|.. AlertaConsola : Implementa (Observer)
    BilleteraFacade --> GastoFactory : Usa
    BilleteraFacade o-- Gasto : Contiene
    BilleteraFacade --> ObservadorPresupuesto : Notifica a


  
