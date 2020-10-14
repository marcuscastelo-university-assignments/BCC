package loja;

public abstract class Produto {
	private final int codigoBarras;
	private final String nome;
	private int quantidade;
	
	public Produto(int codigoBarras, String nome, int quantidade) {
		this.codigoBarras = codigoBarras;
		this.nome = nome;
		this.quantidade = quantidade;
	}
	
	public int getCodigoBarras() { return codigoBarras; }
	public String getNome() { return nome; }
	
	@Override
	public boolean equals(Object obj) {
		return (obj instanceof Produto)? ((Produto)obj).getCodigoBarras() == this.codigoBarras: false;
	}
	
	public void setQuantidade(int quantidade) {
		this.quantidade = quantidade;
	}
	
	public int getQuantidade() {
		return quantidade;
	}
	
	public abstract String getTipo();
	
	@Override
	public String toString() {
		return String.format("[%s] Cod: [%s] --- Nome: '%s' --- Quantidade: %d", getTipo(), getCodigoBarras(), getNome(), getQuantidade());
	}
}
