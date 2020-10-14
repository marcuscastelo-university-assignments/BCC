/**
 * Esta classe representa o placar de um jogo de Bozó. Permite que combinações de dados sejam alocadas às posições e mantém o escore de um jogador.
 * @author marucs
 *
 */
public class Placar {
	
	/**
	 * Número de posições que armazenam pontuação no placar.
	 */
	final int NUM_POSICOES = 10;
	
	/**
	 * Vetor com a pontuação de cada posição.
	 */
	int[] pontuacoes;
	
	/**
	 * Acumulador da pontuação total através de todas as rodadas.
	 */
	int pontuacaoTotal;
	
	/**
	 * Inicializa os membros do objeto com seus valores padrão
	 */
	public Placar() {
		pontuacaoTotal = 0;
		pontuacoes = new int[NUM_POSICOES + 1];
		for (int i = 0; i < pontuacoes.length; i++) {
			pontuacoes[i] = -1;
		}
	}
	
	/**
	 * Adiciona uma sequencia de dados em uma determinada posição do placar. Após a chamada, aquela posição torna-se ocupada e não pode ser usada uma segunda vez.
	 * @param posicao em que posição (1 a 10) adicionar-se-á a pontuação
	 * @param dados vetor com os números rolados nos dados.
	 * @throws IndexOutOfBoundsException caso a posição informada esteja fora do limite 1 a 10 inclusivo.
	 * @throws IllegalArgumentException caso tente adicionar pontuação em uma posição não vazia
	 */
	public void add(int posicao, int[] dados) throws IndexOutOfBoundsException, IllegalArgumentException {
		if (posicao < 1 || posicao > NUM_POSICOES) throw new IndexOutOfBoundsException();
		if (pontuacoes[posicao] != -1) throw new IllegalArgumentException("Posição " + posicao + " já foi definida");
		
		int pontuacao = 0, potencialPontuacao = 0;
		
		if (posicao == 8) {
			int accum = 0;
			boolean[] jafoi = {false,false,false,false,false,false};
			for (int i = 0; i < dados.length; i++) {
				jafoi[dados[i]-1] = true;
			}
			for (int i = 0; i < jafoi.length; i++) {
				if (!jafoi[i]) {
					if (++accum >= 2) {
						pontuacoes[posicao] = 0;
						return; 
					}
				}
			}
			pontuacoes[posicao] = pontuacao = 20;
		} else if (posicao == 7 || posicao == 9 || posicao == 10) { 
			int accum = 0;
			if (posicao == 7) { 
				accum = 3; 
				potencialPontuacao = 15;
			}
			else {
				accum = 11-posicao;
			}
			
			int[] comparacoes = {0,0,0,0,0};
			for (int i = 0, j = 0; i < dados.length; i++) {
				for (j = 0; j < accum; j++) {
					if (dados[i] != comparacoes[j]) {
						if (comparacoes[j] == 0) {
							comparacoes[j] = dados[i];
							break;
						}
					} else break;
				}
				if (j >= accum)  {
					pontuacoes[posicao] = 0;
					return;
				}
			}
		
			if (potencialPontuacao != 15) potencialPontuacao = 10*(posicao-6);
			pontuacoes[posicao] = pontuacao = potencialPontuacao;
			
		} else {
			for (int i = 0; i < dados.length; i++) {
				if (dados[i] == posicao) pontuacao += posicao;
			}
			pontuacoes[posicao] = pontuacao;
		}
		
		pontuacaoTotal += pontuacao;
	}
	
	/**
	 * Computa a soma dos valores obtidos, considerando apenas as posições que já estão ocupadas.
	 * @return O valor da soma
	 */
	public int getScore() {
		return pontuacaoTotal;
	}
	
	/**
	 * Função auxiliar para formatar a saída do toString()
	 * @return espaços laterais
	 */
	private String _reprSpace() {
		return "  ";
	}
	
	/**
	 * Função auxiliar para formatar a saída do toString()
	 * @return separador
	 */
	private String _reprSepar() {
		return _reprSpace() + "|" + _reprSpace();
	}
	
	/**
	 * Função auxiliar para formatar a saída do toString()
	 * @return linha separadora verticalmente
	 */
	private String _reprLine() {
		return "--------------------------\n";
	}
	
	/**
	 * Função auxiliar para formatar a saída do toString()
	 * @return valor da posição "(xx)" se vazio ou " xx " se preenchido
	 */
	private String _reprValue(int index) {
		if (pontuacoes[index] == -1) return "(" + _forceLeftZero(index) + ")";
		else return " " + _forceLeftZero(pontuacoes[index]) + " ";
	}
	
	
	/**
	 * Função auxiliar para formatar a saída do toString()
	 * @param i número a ser convertido
	 * @return número informado como string 0x se i < 10 ou xx se 10 <= i < 100
	 * @throws NumberFormatException se i > 99, três dígitos então quebra a formatação. 
	 */
	private String _forceLeftZero(int i) throws NumberFormatException{
		String strNum = Integer.toString(i);
		if (strNum.length() < 2) strNum = "0" + strNum;
		if (strNum.length() > 2) throw new NumberFormatException("O número enviado foi maior que 99");
		return strNum;
	}
	
	/**
	 * A representação na forma de string, mostra o placar completo, indicando quais são as posições livres (com seus respectivos números) e o valor obtido nas posições já ocupadas. Por exemplo:
 	 *	(1)    |   (7)    |   (4) 
 	 *	--------------------------
 	 *	(2)    |   20     |   (5) 
 	 *	--------------------------
 	 *	(3)    |   30     |   (6) 
	 *	--------------------------
     *   	   |   (10)   |
     *   	   +----------+ 
	 * mostra as posições 8 (sequencia) e 9 (quadra) ocupadas.
	 */
	@Override
	public String toString() {
		String representacao = "";
		final int TOT_COLS = 3, TOT_LINS = 3;
		for (int linha = 1; linha <= TOT_LINS; linha++) {
			representacao += _reprSpace();
			for (int coluna = 1; coluna <= TOT_COLS; coluna++) {
				int startIndex = (coluna%2!=0)?3*(coluna/2):6;
				int index = startIndex + linha;
				representacao += _reprValue(index);
				if (coluna != TOT_COLS) representacao += _reprSepar();
			}
			representacao += _reprSpace();
			representacao += "\n";
			representacao += _reprLine();
		}
		representacao += "        |  ";
		representacao += _reprValue(10);
		representacao += "  |        \n";
		representacao += "        +--------+        ";		
		
		return representacao;
	}
}
