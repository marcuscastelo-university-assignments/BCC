package loja;

public class DVD extends Produto {
	public DVD(int codigoBarras, String nome, int quantidade) {
		super(codigoBarras, nome, quantidade);
	}
	
	@Override
	public String getTipo() {
		return "DVD";
	}
}
