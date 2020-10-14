
public class Quadrado extends Retangulo {
	public Quadrado(String cor, boolean filled, float lado) {
		super(cor, filled, lado, lado);
	}
	
	public float getLado() { return getBase(); }
	
	@Override
	public String toString() {
		return "Quadrado " + getCor() + " " + (isFilled()?"preenchido":"vazio") + " de lado " + getLado(); 
	}
}
