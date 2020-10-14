package figuras_geometricas;

public abstract class FiguraGeometrica {
	private final String cor;
	private final boolean filled;
	
	public FiguraGeometrica(String cor, boolean filled) {
		this.cor = cor;
		this.filled = filled;
	}
	
	public abstract float getArea();
	public abstract float getPerimetro();
	public boolean isFilled() { return filled; }
	public String getCor() { return cor; }
	
	@Override
	public String toString() {
		return this.getClass().getName()  + " " + cor + " " + ((isFilled())?"preenchido":"vazio") ;
	}
}
