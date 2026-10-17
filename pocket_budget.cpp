#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// --- PATRÓN DE COMPORTAMIENTO: OBSERVER (Sistema de Alertas) ---
class ObservadorPresupuesto {
public:
    virtual void actualizar(double totalGastado, double limite) = 0;
    virtual ~ObservadorPresupuesto() {}
};

class AlertaConsola : public ObservadorPresupuesto {
public:
    void actualizar(double totalGastado, double limite) override {
        cout << "----------------------------------------\n";
        if (totalGastado > limite) {
            cout << "⚠️ [ALERTA OBSERVER] ¡Presupuesto superado! Gastado: $" 
                 << fixed << setprecision(2) << totalGastado << " | Limite actual: $" << limite << endl;
        } else {
            cout << "💡 [AVISO OBSERVER] Presupuesto total disponible: $" 
                 << fixed << setprecision(2) << (limite - totalGastado) << endl;
        }
    }
};

// --- CLASE BASE DE GASTOS ---
class Gasto {
protected:
    string descripcion;
    string categoria;
    double monto;
public:
    Gasto(string desc, string cat, double m) : descripcion(desc), categoria(cat), monto(m) {}
    virtual double getMonto() const { return monto; }
    virtual void mostrar() const = 0;
    virtual ~Gasto() {}
};

class GastoGeneral : public Gasto {
public:
    GastoGeneral(string desc, string cat, double m) : Gasto(desc, cat, m) {}
    void mostrar() const override {
        cout << left << setw(20) << descripcion << setw(15) << categoria << "$" << fixed << setprecision(2) << monto << endl;
    }
};

// --- PATRÓN CREACIONAL: FACTORY METHOD (Fábrica de Gastos) ---
class GastoFactory {
public:
    static Gasto* crearGasto(int tipo, string desc, string cat, double monto) {
        if (tipo == 2) {
            return new GastoGeneral(desc + " [FIJO]", cat, monto);
        }
        return new GastoGeneral(desc, cat, monto);
    }
};

// --- PATRÓN ESTRUCTURAL: FACADE (Fachada de la Billetera) ---
class BilleteraFacade {
private:
    vector<Gasto*> gastos;
    double presupuestoLimite;
    ObservadorPresupuesto* observador;

public:
    BilleteraFacade(double limite, ObservadorPresupuesto* obs) {
        presupuestoLimite = limite;
        observador = obs;
    }

    ~BilleteraFacade() {
        for (size_t i = 0; i < gastos.size(); ++i) {
            delete gastos[i];
        }
    }

    void registrarGasto(int tipo, string desc, string cat, double monto) {
        Gasto* nuevoGasto = GastoFactory::crearGasto(tipo, desc, cat, monto);
        gastos.push_back(nuevoGasto);
        cout << "¡Gasto registrado con exito!\n";
        notificarObservador();
    }

    void agregarIngresoExtra(double montoExtra) {
        if (montoExtra <= 0) {
            cout << "El monto del ingreso debe ser mayor a cero.\n";
            return;
        }
        presupuestoLimite += montoExtra;
        cout << "💵 ¡Ingreso extra de $" << fixed << setprecision(2) << montoExtra << " agregado correctamente!\n";
        notificarObservador();
    }

    double calcularTotalGastos() const {
        double total = 0;
        for (size_t i = 0; i < gastos.size(); ++i) {
            total += gastos[i]->getMonto();
        }
        return total;
    }

    void notificarObservador() const {
        observador->actualizar(calcularTotalGastos(), presupuestoLimite);
    }

    void mostrarHistorial() const {
        if (gastos.empty()) {
            cout << "\nNo hay gastos registrados todavia.\n";
            cout << "Presupuesto Limite Actual: $" << fixed << setprecision(2) << presupuestoLimite << endl;
            return;
        }
        cout << "\n========================================\n";
        cout << "          HISTORIAL DE GASTOS           \n";
        cout << "========================================\n";
        cout << left << setw(20) << "Descripcion" << setw(15) << "Categoria" << "Monto" << endl;
        cout << "----------------------------------------\n";
        for (size_t i = 0; i < gastos.size(); ++i) {
            gastos[i]->mostrar();
        }
        cout << "========================================\n";
        cout << "Total Gastado:             $" << fixed << setprecision(2) << calcularTotalGastos() << endl;
        cout << "Presupuesto Limite Total:  $" << fixed << setprecision(2) << presupuestoLimite << endl;
        notificarObservador();
    }
};

// --- FUNCIÓN PRINCIPAL ---
int main() {
    double limiteInicial;
    cout << "=== CONFIGURACION INICIAL POCKETBUDGET ===\n";
    cout << "Ingrese su presupuesto limite inicial ($): ";
    cin >> limiteInicial;

    AlertaConsola alertaSistema;
    BilleteraFacade miBilletera(limiteInicial, &alertaSistema);
    int opcion;

    do {
        cout << "\n--- MENU PRINCIPAL ---\n";
        cout << "1. Registrar gasto normal\n";
        cout << "2. Registrar gasto fijo (Fabrica)\n";
        cout << "3. Agregar ingreso extra 💵\n";
        cout << "4. Ver historial y balance\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1 || opcion == 2) {
            string desc, cat;
            double monto;
            cout << "Descripcion: ";
            cin.ignore();
            getline(cin, desc);
            cout << "Categoria: ";
            getline(cin, cat);
            cout << "Monto ($): ";
            cin >> monto;

            miBilletera.registrarGasto(opcion, desc, cat, monto);

        } else if (opcion == 3) {
            double ingresoExtra;
            cout << "Monto del ingreso extra ($): ";
            cin >> ingresoExtra;
            miBilletera.agregarIngresoExtra(ingresoExtra);

        } else if (opcion == 4) {
            miBilletera.mostrarHistorial();
        }

    } while (opcion != 5);

    cout << "\nSaliendo del programa. ¡Hasta luego!\n";
    return 0;
}