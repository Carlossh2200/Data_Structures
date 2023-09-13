import java.util.Scanner;
import java.io.File;
import java.io.IOException;
import java.io.PrintStream;
import java.time.format.DateTimeFormatter;
import java.time.LocalDateTime;
//Practica 2
//CuatroCero
//Tiempo=02:00
public class Main {
	
	public static Scanner consola=new Scanner(System.in);
	public static final int TOTAL_MESES=12;
	static String[] meses=new String[TOTAL_MESES  ];
	public static final int IVA=16;
	public static final int ISR=11;
	public static final int RETENCION_IVA=10;
	public static final int RETENCION_ISR=10;
	public static final int C_100=100;
	public static final int C_1=1;
	public static int seleccionMes=0;
	public static String mesActual="Enero";
	public static float ingresoTotal=0,calculoIva,calculoRetencionIva,calculoRetencionIsr,subtotal,total,
	    gastoTotal=0,gananciaBruta,gananciaNeta,calculoIsr,pagoIsr,gastoIva,pagoIva;
	
	
	
	
	
	
	public static int menuPrincipal() {
		int opcion;
		System.out.println("CALCULO DE IMPUESTOS ANUAL\n");
		System.out.println("Menu principal");
		System.out.println("1. Establecer mes para captura (mes actual es "+mesActual+")");
		System.out.println("2. Captura de ingresos");
		System.out.println("3. Captura de gastos");
		System.out.println("4. Mostrar lista de ingresos anual");
		System.out.println("5. Mostrar lista de gastos anual");
		System.out.println("6. Calculo de impuestos anual");
		System.out.println("7. Salir");
		System.out.println("Opcion: ");
		opcion=consola.nextInt();
		if (opcion<1 || opcion > 12) {
			System.out.println("Opcion no valida...");
			opcion=1;
		}
		consola.nextLine();
		return opcion;
	}
		
	public static void pausar() {
		System.out.println("Presione entrar para continuar...");
		consola.nextLine();
	}

  public static void escribirCalculoImpuestosAnual(PrintStream salida) {
    salida.println("CALCULO DE IMPUESTOS\n");
	  salida.println("***Tabla recibo de honorarios***");
	  salida.println("Ingresos          "+ingresoTotal);
	  salida.println("(+) IVA           "+calculoIva);
	  salida.println("(=) Subtotal      "+subtotal);
	  salida.println("(-) Retencion ISR "+calculoRetencionIsr);
	  salida.println("(=) TOTAL         "+total);
	  salida.println("TABLA GANANCIAS   ");
	  salida.println("Ingresos          "+ingresoTotal);
	  salida.println("(-) Gasto         "+gastoTotal);
	  salida.println("(=) Ganancia Bruta"+gananciaBruta);
	  salida.println("(-) ISR           "+calculoIsr);
	  salida.println("(-) Ganancia Neta "+gananciaNeta);
	  salida.println("TABLA ISR         \n");
	  salida.println("ISR               "+calculoIsr);
	  salida.println("(-) ISR Retenido  "+calculoRetencionIsr);
	  salida.println("(=) ISR a Pagar   "+pagoIsr);
	  salida.println("TABLA IVA         \n");
	  salida.println("IVA               "+calculoIva);
	  salida.println("(-) Gasto IVA     "+gastoIva);
	  salida.println("(-) Retencion IVA "+calculoRetencionIva);
	  salida.println("(=) IVA a Pagar   "+pagoIva);
  }

	public static void main(String[] args) {
		//Declaracion y definicion de constantes
		DateTimeFormatter dtf = DateTimeFormatter.ofPattern("_yyyy_MM_dd_HH_mm_ss");
		LocalDateTime now = LocalDateTime.now();
		final String NOMBRE_ARCHIVO="MiArchivoPractica2"+dtf.format(now)+".txt";
		File archivoFile=new File(NOMBRE_ARCHIVO);
		boolean seguirEjecutandoPrograma=true;
		float[] ingresoIndividual=new float[TOTAL_MESES];
		float[] gastoIndividual=new float[TOTAL_MESES];
		meses[0]="Enero ";
		meses[1]="Febrero ";
		meses[2]="Marzo ";
		meses[3]="Abril ";
		meses[4]="Mayo ";
		meses[5]="Junio ";
		meses[6]="Julio ";
		meses[7]="Agosto ";
		meses[8]="Septiembre ";
		meses[9]="Octubre ";
		meses[10]="Noviembre ";
		meses[11]="Diciembre ";
		//Entrada de datos
    int opcion = 0;
		while(seguirEjecutandoPrograma) {
			switch(opcion = menuPrincipal()) {
			case 1:
				System.out.println("Establecer mes para captura: ");
				for(int i=0;i<TOTAL_MESES;i++) {
					System.out.println(i+C_1+") "+meses[i]);
				}
				System.out.print("Elige el mes (1 a 12): ");
				seleccionMes=consola.nextInt();
				seleccionMes--;
				mesActual=meses[seleccionMes];
				break;
			case 2:
				System.out.println("Captura de ingresos");
				System.out.print("Dame el ingreso del mes de "+mesActual+": ");
				ingresoIndividual[seleccionMes]=consola.nextFloat();
				break;
			case 3: 
				System.out.println("Captura de gastos");
				System.out.println("Dame el gasto del mes de "+mesActual+": ");
				gastoIndividual[seleccionMes]=consola.nextFloat();
				break;
			case 4:
				System.out.println("Lista de ingresos actual");
				for(int i=0;i<TOTAL_MESES;i++) {
					System.out.println(meses[i]+" = "+ingresoIndividual[i]);
				}
				break;
			case 5:
				System.out.println("Lista de gastos anual");
				for(int i=0;i<TOTAL_MESES;i++) {
					System.out.println(meses[i]+" = "+gastoIndividual[i]);
				}
				break;
			case 6:
				for(int i=0;i<TOTAL_MESES;i++) {
					ingresoTotal+=ingresoIndividual[i];
				}
				for(int i=0;i<TOTAL_MESES;i++) {
					gastoTotal+=gastoIndividual[i];
				}
				calculoIva=(IVA*ingresoTotal)/C_100; //Calculo de impuestos
	            calculoRetencionIva=(ingresoTotal*RETENCION_IVA)/C_100;
	            calculoRetencionIsr=(ingresoTotal*RETENCION_ISR)/C_100;
	            subtotal=ingresoTotal+calculoIva;
	            total=subtotal-calculoRetencionIsr-calculoRetencionIva;

	            gananciaBruta=ingresoTotal-gastoTotal;
	            calculoIsr=(gananciaBruta*ISR)/C_100;
	            gananciaNeta=gananciaBruta-calculoIsr;
	            pagoIsr=calculoIsr-calculoRetencionIsr;
	            gastoIva=(gastoTotal*IVA)/C_100;
	            pagoIva=calculoIva-gastoIva-calculoRetencionIva;
	            
	            try {
	            	PrintStream archivo=new PrintStream(archivoFile);
                escribirCalculoImpuestosAnual(archivo);
	            	archivo.close();
	            }catch(IOException e) {
	            	e.printStackTrace(System.err);
	            }
              escribirCalculoImpuestosAnual(System.out);
				break;
			case 7:
				System.out.println("Saliste del programa...");
				seguirEjecutandoPrograma=false;
				break;
      default:
        System.out.println("Error, opcion invalida!");
		  }
      
      if (opcion != 7 ) { 
        pausar();
      }

		}
		consola.close();
	}
}
