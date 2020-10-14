package exercicios;

import entrada.FilteredInput;

public class Ex05 {
	public static void main(String[] args){
		int numToTest = FilteredInput.readAsInt("Type number to test: ");
		
		if (numToTest++ < 2) System.out.println("Não há números primos");
		
		while (--numToTest > 0)
			if (isPrime(numToTest)) {
				System.out.println("Primo encontrado: " + numToTest);
				break;
			} 
		
	}
	
	static boolean isPrime(int num) {
		for (int i = 2; i*i <= num; i++) {
			if (num%i == 0) return false;
		}
		return true;
	}
}
