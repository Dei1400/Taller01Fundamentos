// C++ code
//
const int buttonAddTwo = 4; //Pulsadores
const int buttonAddOne = 3;
const int buttonReset = 2;
const int buttonNegative = 1;

const int ledRGBB0 = 9;     //Led RGB para bits
const int ledRGBB1 = 10;
const int ledRGBB2 = 11;
const int ledRGBB3 = 12;

const int ledRed = 13;     //Led rojo para cuando pasa 15

int stateAddTwo = 0; //estado de los bottones sumadores
int stateAddOne = 0;
int stateReset = 0;
int stateNegative = 0;

static int arregloBinario[4];
static int arregloInvertido[4]; //guardar arreglo invertido
static int arregloSuma1[4]; //guardar despues  de sumar 1

int num = 0;

int cont = 0;

void setup()
{
  	pinMode(ledRGBB0, OUTPUT); //Salidas
	pinMode(ledRGBB1, OUTPUT);
    pinMode(ledRGBB2, OUTPUT);
    pinMode(ledRGBB3, OUTPUT);
 	pinMode(ledRed, OUTPUT);

    pinMode(buttonAddTwo, INPUT); //Entradas
    pinMode(buttonAddOne, INPUT);
    pinMode(buttonReset, INPUT);
    pinMode(buttonNegative, INPUT);
  
  	Serial.begin(9600);
}

void loop()
{
 	stateAddTwo = digitalRead(buttonAddTwo);
  	stateAddOne = digitalRead(buttonAddOne);
  
  	stateReset = digitalRead(buttonReset);
  	//Serial.println(stateReset);
  	//stateNegative = digitalRead(buttonNegative);

 	if (stateReset == HIGH){
      	cont = 0;
      	//
     	Serial.println(cont);
      	digitalWrite(buttonAddTwo, LOW);
     	digitalWrite(buttonAddOne, LOW);
     	digitalWrite(buttonReset,LOW);
      	digitalWrite(buttonNegative,LOW);
     	digitalWrite(ledRed, LOW);
      
  	}if (stateAddTwo == HIGH){
  		cont = cont + 2;
      	Serial.println(cont);
      	digitalWrite(buttonAddTwo, LOW);
     	digitalWrite(buttonAddOne, LOW);
      
    }if (stateAddOne == HIGH){
      	cont = cont +1;
      	Serial.println(cont);
      	digitalWrite(buttonAddOne, LOW);
  	    digitalWrite(buttonAddTwo, LOW);
    }
  	delay(150);
	decimalABinario(cont);
}
//Funcion cambio de base 10->2
int* decimalABinario(int num){
  	if (num > 15){
    	// que encienda el led rojo
      	digitalWrite(ledRed, HIGH);
      
        digitalWrite(buttonAddTwo, LOW);
        digitalWrite(buttonAddOne, LOW);
      
      	digitalWrite(ledRGBB3, LOW);
        digitalWrite(ledRGBB2, LOW);
        digitalWrite(ledRGBB1, LOW);
        digitalWrite(ledRGBB0, LOW);
      
      	return arregloBinario; //regresa el arreglo sin nada ya que la funcion debe retornar un arreglo
    }else{
      for (int i = 3; i >= 0; i--){ //contador incia en 3 por 4bits-1 por inciar en 0
      	arregloBinario[i] = num % 2; //modulo en la posición i
        num = num / 2;
      }
    }
 	mostrarBinario(arregloBinario);
  	return arregloBinario; //Retorno el arreglo
}
//funcion que enciende los rgb
void mostrarBinario(const int* arregloBinario){ //no retorna nada pero recibe un arreglo tipo int
  	
  	digitalWrite(ledRGBB3, LOW);
 	digitalWrite(ledRGBB2, LOW);
 	digitalWrite(ledRGBB1, LOW);
 	digitalWrite(ledRGBB0, LOW);

    /*if (stateNegative == HIGH){
      	Serial.println(stateNegative);
      	mostrarBinario(invertirCerosYUnos(arregloBinario));
      	digitalWrite(buttonNegative, LOW);
      	Serial.println(stateNegative);
      	
    }*/
  	// Controla el LED 1
    if (arregloBinario[0] == 1) {
      	digitalWrite(ledRGBB3, HIGH);
    } else {
      	digitalWrite(ledRGBB3, LOW);
    }

    // Controla el LED 2
    if (arregloBinario[1] == 1) {
      	digitalWrite(ledRGBB2, HIGH);
    } else {
      	digitalWrite(ledRGBB2, LOW);
    }

    // Controla el LED 3
    if (arregloBinario[2] == 1) {
      	digitalWrite(ledRGBB1, HIGH);
    } else {
      	digitalWrite(ledRGBB1, LOW);
    }

    // Controla el LED 4
    if (arregloBinario[3] == 1) {
      	digitalWrite(ledRGBB0, HIGH);
    } else {
      	digitalWrite(ledRGBB0, LOW);
    }
}
//funcion para invertir ceros y uno en arreglo (complemento a dos en dos funciones.)
int* invertirCerosYUnos(const int* arregloBinario) {
  
  	for (int i = 0; i < 4; i++) {
      	if (arregloBinario[i] == 0){
        	arregloInvertido[i] = 1;
      	}else{
        	arregloInvertido[i] = 0;
      	}
    // Si el valor es 0, lo convierte en 1; si es 1, lo convierte en 0
 	}

  	return sumarUnoBinario(arregloInvertido); // Retorna el nuevo arreglo invertido
}
// Función que suma 1 al arreglo binario
int* sumarUnoBinario(const int* arregloBinario) {
  
  	// Sumar 1 al número binario representado por el arreglo invertido
  	int carry = 1; // Inicia con el carry de 1 (para sumar 1)
  
  	for (int i = 3; i >= 0; i--) { // Recorre el arreglo de derecha a izquierda (bit menos significativo a más significativo)
    	int sum = arregloBinario[i] + carry;
    	arregloSuma1[i] = sum % 2; // El nuevo valor del bit (0 o 1)
    	carry = sum / 2; // Si hay un carry, se lleva a la siguiente posición
  	}

  	return arregloSuma1; // Retorna el nuevo arreglo después de sumar 1
}
