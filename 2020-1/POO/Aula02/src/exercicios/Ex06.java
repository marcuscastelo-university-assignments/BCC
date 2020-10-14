package exercicios;

import entrada.FilteredInput;

public class Ex06 {
	public static void main(String[] args) {
		double temp, maior, menor;
		temp = maior = menor = FilteredInput.readAsDouble("Digite um número (0 para terminar): ");
		while (temp != 0) {
			temp = FilteredInput.readAsDouble("Digite um número (0 para terminar): ");
			if (temp > maior) maior = temp;
			else if (temp < menor) menor = temp;
		}
		System.out.println("Maior: " + maior + " \nMenor: " + menor);
	}
}
