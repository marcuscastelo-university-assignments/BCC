package figuras_geometricas;

public class Teste {
	public static void main(String[] args) {
		FiguraGeometrica[] figuras = {
				new Circulo("vermelho", false, 10f),
				new Retangulo("vermelho", false, 10f, 5f),
				new Quadrado("vermelho", true, 10f)
		};
		
		for (FiguraGeometrica fig : figuras) {
			System.out.println(fig);		
			System.out.println("Área: " + fig.getArea());
			System.out.println("Perímetro: " + fig.getPerimetro());
			System.out.println();
		}
	}
}
