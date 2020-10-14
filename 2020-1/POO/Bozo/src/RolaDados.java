/**
 * Essa é uma classe auxiliar que permite gerencia um conjunto de vários dados simultaneamente. Operações como rolar alguns dos dados ou exibir o resultado de todos eles, são implementadas.
 * @author marucs
 *
 */
public class RolaDados {
	Dado[] dados;
	/**
	 * Construtor que cria e armazena vários objetos do tipo Dado. Usa para isso o construtor padrão daquela classe, ou seja, um dado de 6 lados e gerando sempre uma semente aleatória para o gerador de números aleatórios. Os dados criados podem ser referenciados por números, entre 1 e n.
	 * @param n número de dados 
	 */
	public RolaDados(int n) {
		dados = new Dado[n];
		try {			
			for (int i = 0; i < dados.length; i++) {
				Thread.sleep(1);
				dados[i] = new Dado();
			}
		} catch(InterruptedException e) {
			// Programa foi interrompido durante o sleep, fechar
			e.printStackTrace();
			System.exit(1);
		}
	}
	
	/**
	 * Função auxiliar que cria um vetor de dados a serem rolados, com um valor padrão
	 * @param value valor a ser atribuído a todas as posições do vetor
	 * @return vetor com todas as posições definidas como value
	 */
	private boolean[] _rolar_default_value(boolean value) {
		boolean[] quais = new boolean[dados.length];
		for (int i = 0; i < quais.length; i++) {
			quais[i] = value;
		}
		return quais;
	}
	
	/**
	 * Rola todos os dados.
	 * @return vetor com os novos valores dos dados rolados
	 */
	public int[] rolar() {
		//Apesar de gastar mais recursos para criar esse vetor, dessa forma o trabalho de rolar os dados não possuirá código duplicado, possibilitando uma melhor manutenção num possível replanejamento da função rolar, será necessário apenas modificar a função que recebe o booleano, e não esta.
		boolean[] quais = _rolar_default_value(true);
		return rolar(quais);
	}
	
	/**
	 * Rola alguns dos dados.
	 * @param s string que representa os dados a serem rolados separados por espaço
	 * @return Retorna o valor de cada um dos dados, inclusive os que não foram rolados. Nesse caso, o valor retornado é o valor anterior que ele já possuia.
	 * @throws IndexOutOfBoundsException Se forem informados mais dados que o esperado, comparado ao informado no construtor
	 */
	public int[] rolar(String s) throws IndexOutOfBoundsException {
		boolean[] quais = _rolar_default_value(false);
		
		if (s.length() == 0) return rolar(quais);
		
		String[] caracteres = s.split(" ");
		if (caracteres.length > dados.length) throw new IndexOutOfBoundsException("Foram informados mais dados que o vetor de dados informado no construtor");
		for (int i = 0; i < caracteres.length; i++) {
			int number = Integer.parseInt(caracteres[i]);
			quais[number-1] = true;
		}
		return rolar(quais);
	}
	
	/**
	 * Rola alguns dos dados.
	 * @param quais vetor de booleanos que indica quais dados devem ser rolados
	 * @return Retorna o valor de cada um dos dados, inclusive os que não foram rolados. Nesse caso, o valor retornado é o valor anterior que ele já possuia.
	 * @throws IndexOutOfBoundsException se o vetor quais n for do mesmo tamanho dos dados informados no construtor
	 */
	public int[] rolar(boolean[] quais) throws IndexOutOfBoundsException {
		if (quais.length != dados.length) throw new IndexOutOfBoundsException("O vetor quais não é do mesmo tamanho que o vetor de dados informado no construtor");
		
		int[] valores = new int[dados.length];
		for (int i = 0; i < quais.length; i++) {
			if (quais[i])
				valores[i] = dados[i].rolar();
			else
				valores[i] = dados[i].getLado();
		}
		return valores;
	}
	
	/**
	 * Usa a representação em string do dados, para mostrar o valor de todos os dados do conjunto. Exibe os dados horisontalmente, por exemplo:
 	 *	1          2          3          4          5
	 *	+-----+    +-----+    +-----+    +-----+    +-----+    
	 *	|*   *|    |     |    |*    |    |*    |    |*   *|    
	 *	|  *  |    |  *  |    |     |    |  *  |    |     |    
	 *	|*   *|    |     |    |    *|    |    *|    |*   *|    
	 *	+-----+    +-----+    +-----+    +-----+    +-----+    
	 */
	@Override
	public String toString() {
		String representacao = "";
		
		for (int i = 1; i <= dados.length; i++) {
			representacao += " " + i + "     ";
			representacao += "    ";
		}
		representacao += "\n";
		
		for (int linha = 0; linha < Dado.REPR_NUM_LINHAS; linha++) {
			for (int i = 0; i < dados.length; i++) {
				representacao += dados[i].reprParcial(linha);
				representacao += "    ";
			}
			representacao += "\n";
		}
		return representacao;
	}
	
	/**
	 * 
	 * @throws Exception
	 */
	public static void main(String[] args) throws Exception {
		RolaDados rd = new RolaDados(5);
		rd.rolar();
		System.out.println(rd);
	}
	
}
