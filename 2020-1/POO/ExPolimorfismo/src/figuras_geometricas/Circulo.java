package figuras_geometricas;

public class Circulo extends FiguraGeometrica {
	private final float raio;
	public Circulo(String cor, boolean filled, float raio) {
		super(cor, filled);
		this.raio = raio;
	}
	
	public float getRaio() { return raio; }

	@Override
	public float getArea() {
		return (float)(Math.PI * raio * raio);
	}

	@Override
	public float getPerimetro() {
		return (float)(2 * Math.PI * raio);
	}
	
	@Override
	public String toString() {
		return super.toString() + " de raio " + this.getRaio();
	}
	
}
