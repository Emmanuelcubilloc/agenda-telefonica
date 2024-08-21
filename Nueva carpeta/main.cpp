#include <iostream>
#include <string>
#include <algorithm>
#include <locale>

using namespace std;

struct Contacto {
    string nombre;
    string telefono;
    string direccion;
};

const int MAX_CONTACTOS = 100;
Contacto agenda[MAX_CONTACTOS];
int numContactos = 0;

// Funciones
void agregarContacto();
void buscarContacto();
void modificarContacto();
void eliminarContacto();
void imprimirReporte();
void ordenarAgenda();
int buscarIndicePorNombre(string nombre);
bool compararPorNombre(Contacto a, Contacto b); // Declaración de la función de comparación

int main() {
    int opcion;

    do {
        cout << "\n--- Agenda Telefónica ---\n";
        cout << "1. Agregar Contacto\n";
        cout << "2. Buscar Contacto\n";
        cout << "3. Modificar Contacto\n";
        cout << "4. Eliminar Contacto\n";
        cout << "5. Imprimir Reporte\n";
        cout << "6. Salir\n";
        cout << "Elija una opción: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                agregarContacto();
                break;
            case 2:
                buscarContacto();
                break;
            case 3:
                modificarContacto();
                break;
            case 4:
                eliminarContacto();
                break;
            case 5:
                imprimirReporte();
                break;
            case 6:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
                break;
        }
    } while (opcion != 6);

    return 0;
}

void agregarContacto() {
    if (numContactos >= MAX_CONTACTOS) {
        cout << "La agenda está llena. No se pueden agregar más contactos.\n";
        return;
    }

    Contacto nuevoContacto;
    cout << "Ingrese el nombre: ";
    getline(cin, nuevoContacto.nombre);
    cout << "Ingrese el teléfono: ";
    getline(cin, nuevoContacto.telefono);
    cout << "Ingrese la dirección: ";
    getline(cin, nuevoContacto.direccion);

    agenda[numContactos] = nuevoContacto;
    numContactos++;
    cout << "Contacto agregado con éxito.\n";
}

void buscarContacto() {
    string nombreBusqueda;
    cout << "Ingrese el nombre o parte del nombre del contacto a buscar: ";
    getline(cin, nombreBusqueda);

    bool encontrado = false;
    for (int i = 0; i < numContactos; i++) {
        if (agenda[i].nombre.find(nombreBusqueda) != string::npos) {
            cout << "\nNombre: " << agenda[i].nombre;
            cout << "\nTeléfono: " << agenda[i].telefono;
            cout << "\nDirección: " << agenda[i].direccion << "\n";
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontró ningún contacto con ese nombre.\n";
    }
}

void modificarContacto() {
    string nombreBusqueda;
    cout << "Ingrese el nombre del contacto a modificar: ";
    getline(cin, nombreBusqueda);

    int indice = buscarIndicePorNombre(nombreBusqueda);
    if (indice != -1) {
        cout << "Ingrese el nuevo nombre (anterior: " << agenda[indice].nombre << "): ";
        getline(cin, agenda[indice].nombre);
        cout << "Ingrese el nuevo teléfono (anterior: " << agenda[indice].telefono << "): ";
        getline(cin, agenda[indice].telefono);
        cout << "Ingrese la nueva dirección (anterior: " << agenda[indice].direccion << "): ";
        getline(cin, agenda[indice].direccion);

        cout << "Contacto modificado con éxito.\n";
    } else {
        cout << "No se encontró ningún contacto con ese nombre.\n";
    }
}

void eliminarContacto() {
    string nombreBusqueda;
    cout << "Ingrese el nombre del contacto a eliminar: ";
    getline(cin, nombreBusqueda);

    int indice = buscarIndicePorNombre(nombreBusqueda);
    if (indice != -1) {
        for (int i = indice; i < numContactos - 1; i++) {
            agenda[i] = agenda[i + 1];
        }
        numContactos--;
        cout << "Contacto eliminado con éxito.\n";
    } else {
        cout << "No se encontró ningún contacto con ese nombre.\n";
    }
}

void imprimirReporte() {
    if (numContactos == 0) {
        cout << "La agenda está vacía.\n";
        return;
    }

    ordenarAgenda();

    cout << "\n--- Agenda Telefónica Ordenada ---\n";
    for (int i = 0; i < numContactos; i++) {
        cout << "\nNombre: " << agenda[i].nombre;
        cout << "\nTeléfono: " << agenda[i].telefono;
        cout << "\nDirección: " << agenda[i].direccion << "\n";
    }
}

void ordenarAgenda() {
    sort(agenda, agenda + numContactos, compararPorNombre);
}

// Función de comparación sin usar lambda
bool compararPorNombre(Contacto a, Contacto b) {
    return a.nombre < b.nombre;
}

int buscarIndicePorNombre(string nombre) {
    for (int i = 0; i < numContactos; i++) {
        if (agenda[i].nombre == nombre) {
            return i;
        }
    }
    return -1; // Si no se encuentra el contacto
}

