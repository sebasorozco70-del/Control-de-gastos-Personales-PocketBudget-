#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Clase base para representar un Gasto individual
class Gasto {
private:
    string descripcion;
    string categoria;
    double monto;

public:
    Gasto(string desc, string cat, double m) {
        descripcion = desc;
        categoria = cat;
        monto = m;
    }

    double getMonto() const { 
        return monto; 
    }

    void mostrar() const {
        cout << "- " << descripcion << " [" << categoria << "]: $" << monto << endl;
    }
};

// Clase gestora para manejar la colección de gastos y el límite
class Billetera {
private:
    vector<Gasto> gastos;
    double presupuestoLimite;

public:
    Billetera(double limite) {
        presupuestoLimite = limite;
    }

    void agregarGasto(const Gasto& g) {
        gastos.push_back(g);
    }

    void mostrarResumen() const {
        cout << "\n=== HISTORIAL DE GASTOS ===\n";
        if (gastos.empty()) {
            cout << "No hay registros aun.\n";
            return;
        }

        double total = 0;
        for (size_t i = 0; i < gastos.size(); ++i) {
            gastos[i].mostrar();
            total += gastos[i].getMonto();
        }

        cout << "---------------------------\n";
        cout << "Total gastado:   $" << total << endl;
        cout << "Presupuesto max: $" << presupuestoLimite << endl;
        
        if (total > presupuestoLimite) {
            cout << "⚠️ Alerta: Has superado tu limite.\n";
        }
    }
};

// Función principal con flujo lineal y sencillo de mostrar en pantalla
int main() {
    double limiteInicial;
    cout << "=== CONFIGURACION INICIAL ===\n";
    cout << "Ingrese el presupuesto limite: $";
    cin >> limiteInicial;

    Billetera miBilletera(limiteInicial);
    int opcion;

    do {
        cout << "\n--- MENU PRINCIPAL ---\n";
        cout << "1. Registrar gasto\n";
        cout << "2. Ver resumen y balance\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string desc, cat;
            double monto;
            
            cout << "Descripcion: ";
            cin.ignore();
            getline(cin, desc);
            cout << "Categoria: ";
            getline(cin, cat);
            cout << "Monto ($): ";
            cin >> monto;

            miBilletera.agregarGasto(Gasto(desc, cat, monto));
            cout << "¡Gasto registrado con exito!\n";

        } else if (opcion == 2) {
            miBilletera.mostrarResumen();
        }

    } while (opcion != 3);

    cout << "\nSaliendo del programa. ¡Hasta luego!\n";
    return 0;
}