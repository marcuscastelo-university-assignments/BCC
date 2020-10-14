

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Esta classe foi desenhada para facilitar a entrada de dados
 * pelo teclado. Basicamente ela implementa funções para
 * ler strings, inteiros e doubles. 
 * Ela faz verificações se o que foi digitado realmente
 * é o esperado. 
 * @author delamaro
 *
 */
public class EntradaTeclado {
static InputStreamReader isr = new InputStreamReader(System.in);
static BufferedReader br = new BufferedReader(isr);
	
	/**
	 * Le um string digitado pelo teclado, até que seja pressionado
	 * um enter. Ou seja, le a linha toda.
	 * @return o string que foi digitado pelo usuário.
	 */
	public static String leString() {
		String x = "";
		try {
			x = br.readLine();	
		} catch ( IOException e) {
			e.printStackTrace();
			System.err.println("Houve um erro de I/O, fechando...");
			System.exit(2);
		}
		return x;

	}

	/**
	 * Le um string do teclado (uma linha toda) e tenta transformá-lo num inteiro. 
	 * Porém não faz qualquer verificação sobre a validade do dado digitado.
	 * @return  o valor inteiro digitado pelo usuário. 
	 * @throws IOException
	 */
	public static int leInt() {
		String x = leString();
		return Integer.parseInt(x);
	}

	/**
	 * Le um string do teclado (uma linha toda) e tenta transformá-lo num double. 
	 * Porém não faz qualquer verificação sobre a validade do dado digitado.
	 * @return  o valor double digitado pelo usuário. 
	 */

	public static double leDouble() {
		String x = leString();
		return Double.parseDouble(x);
	}
}