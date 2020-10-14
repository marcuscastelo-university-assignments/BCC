package figuras_geometricas;

public class Retangulo extends FiguraGeometrica {
	private final float base, altura;
	public Retangulo(String cor, boolean filled, float base, float altura) {
		super(cor, filled);
		this.base = base;
		this.altura = altura;
	}
	
	public float getBase() { return base; }
	public float getAltura() { return altura; }

	@Override
	public float getArea() {
		return base * altura;
	}

	@Override
	public float getPerimetro() {
		return 2*base + 2*altura;
	}
	
	@Override
	public String toString() {
		return super.toString() + " de base " + getBase() + " e altura " + getAltura();
	}


}
