
public class Livro extends Produto {
	public Livro(int codigoBarras, String nome, int quantidade) {
		super(codigoBarras, nome, quantidade);
	}
	
	@Override
	public String getTipo() {
		return "Livro";
	}
}

