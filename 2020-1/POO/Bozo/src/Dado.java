
public class Dado {
	
	/**
	 * Tamanho vertical da representação do dado
	 */
	public static final int REPR_NUM_LINHAS = 5;
	
	/**
	 * Representação de cada número que o dado pode rolar, linha por linha
	 */
	public static final String[][] REPRESENTACOES = {{"+-----+","|     |","|  *  |","|     |","+-----+"},
			{"+-----+","|*    |","|     |","|    *|","+-----+"},
			{"+-----+","|*    |","|  *  |","|    *|","+-----+"},
			{"+-----+","|*   *|","|     |","|*   *|","+-----+"},
			{"+-----+","|*   *|","|  *  |","|*   *|","+-----+"},
			{"+-----+","|* * *|","|     |","|* * *|","+-----+"}};
	
	/**
	 * Número de lados informado no construtor
	 */
	private int numLados;
	
	/**
	 * Último número sorteado pelo método rolar()
	 */
	private int numSelecionado;
	
	/**
	 * Variável que armazena o aleatorizador usado no dado.
	 */
	Random rand;
	
	/**
	 * Cria objeto com um número qualquer de lados
	 * @param n número de lados do dado
	 */
	public Dado(int n) {
		numLados = n;
		numSelecionado = 1;
		rand = new Random();
	}
	
	/**
	 * Cria um dado com 6 lados (um cubo)
	 */
	public Dado() {
		// Seis lados por padrão
		this(6);
	
	}
	
	/**
	 * Recupera o último número selecionado.
	 * @return o número do último lado selecionado.
	 */
	public int getLado() {
		return numSelecionado;
	}
	
	/**
	 * Simula a rolagem do dado por meio de um gerador aleatório. O número selecionado pode posteriormente ser recuperado com a chamada a getLado()
	 * @return o número que foi sorteado
	 */
	public int rolar() {
		numSelecionado = rand.getIntRand(numLados) + 1;
		return numSelecionado;
	}
	

	/**
	 * Função auxiliar usada para obter uma parte da representação do dado (linha por linha)
	 * @param linha linha da representação (começando em 0)
	 * @return string da linha informada
	 */
	public String reprParcial(int linha) {
		return REPRESENTACOES[numSelecionado-1][linha];
	}
	
	/**
	 * Transforma representação do dado em String. É mostrada uma representação do dado que está para cima. Note que só funciona corretamente para dados de 6 lados. Exemplo:
	 *	+-----+    
	 *	|*   *|    
	 *	|  *  |    
	 *	|*   *|    
	 *	+-----+     
	 */
	@Override
	public String toString() {
		String representacao = "";
		for (int i = 0; i < REPR_NUM_LINHAS; i++) {
			representacao += reprParcial(i) + "\n";
		}
		return representacao;
	}
	
	/**
	 * Não tem função real dentro da classe. Foi usada apenas para testar os métodos implementados
	 * @param args Sem uso
	 */
	public static void main(String[] args) {
		Dado d = new Dado();
		for (int i = 1; i <= 6; i++) {
			d.rolar();
			System.out.println(d);	
		}
	}
	
}
