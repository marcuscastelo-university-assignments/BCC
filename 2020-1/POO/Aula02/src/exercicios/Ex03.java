package exercicios;

import entrada.FilteredInput;

public class Ex03 {
	public static void main(String[] args) {
		int treeSize = FilteredInput.readAsInt("Digite o tamanho da árvore: ");
		for (int i=treeSize; i > 0; i--) {
			int j;
			for (j = 0; j < treeSize - i; j++) {
				System.out.print(" ");
			}
			for (;j<treeSize; j++) {
				System.out.print("*");
			}
			System.out.println();
		}
	}
}
