import java.util.Scanner;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;
import java.time.format.DateTimeFormatter;
import java.time.LocalDateTime;
//Practica 4
//CuatroCero
//Tiempo=02:30
public class Main {
	
	public static Scanner consola=new Scanner(System.in);
	public static final int TOTAL_MESES=12;
	static String[] meses=new String[TOTAL_MESES  ];
	public static final int MAX_INGRESOS_MES=3;
	public static final int MAX_GASTOS_MES=3;
	public static final int TAMANIO_CONCEPTO=40;
	public static final int TAMANIO_JUSTIFICACION=40;
	public static final int MAX_INGRESOS=20;
	public static final int MAX_GASTOS=20;
	public static float[] ingresoIndividual=new float[TOTAL_MESES];
	public static float[] gastoIndividual=new float[TOTAL_MESES];
	public static Ingreso[] ingresos=new Ingreso[TOTAL_MESES];
	public static Gasto[] gastos=new Gasto[TOTAL_MESES];
	public static final int IVA=16;
	public static final int ISR=11;
	public static final int RETENCION_IVA=10;
	public static final int RETENCION_ISR=10;
	public static final int CANTIDAD_PORCENTAJES_ISR=3;
	public static final int CANTIDAD_RANGOS_ISR=3;
	public static final int C_0=0;
	public static final int C_100=100;
	public static final int C_1=1;
	public static final int C_2=2;
	public static final int PORCENTAJE_ISR_RANGO_UNO=11;
	public static final int PORCENTAJE_ISR_RANGO_DOS=15;
	public static final int PORCENTAJE_ISR_RANGO_TRES=20;
	public static final int LIMITE_INFERIOR_RANGO_UNO=0;
	public static final double LIMITE_INFERIOR_RANGO_DOS=10000.01;
	public static final double LIMITE_INFERIOR_RANGO_TRES=20000.01;
	public static int seleccionMes,isrAplicado,cuentaIngresos=0,cuentaGastos=0;
	public static String mesActual;
	public static float ingresoTotal,calculoIva,calculoRetencionIva,calculoRetencionIsr,subtotal,total,
	    gastoTotal,gananciaBruta,gananciaNeta,calculoIsr,pagoIsr,gastoIva,pagoIva,porcentajeIsr;
	public static int[] tablaPorcentajeIsr=new int[CANTIDAD_PORCENTAJES_ISR];
	public static double[] tablaRangosIsr=new double[CANTIDAD_RANGOS_ISR];
	
	public static void inicializar(File archivoIngreso,File archivoGasto,String NOMBRE_ARCHIVO_INGRESO,String NOMBRE_ARCHIVO_GASTO,
			float[] ingresoIndividual,float[] gastoIndividual) {
		for(int i=0;i<TOTAL_MESES;i++) {
			ingresos[i]=new Ingreso();
			gastos[i]=new Gasto();
		}
		seleccionMes=0;
		mesActual="Enero";
		ingresoTotal=0;
		gastoTotal=0;
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
		tablaPorcentajeIsr[0]=PORCENTAJE_ISR_RANGO_UNO;
		tablaPorcentajeIsr[1]=PORCENTAJE_ISR_RANGO_DOS;
		tablaPorcentajeIsr[2]=PORCENTAJE_ISR_RANGO_TRES;
		tablaRangosIsr[0]=LIMITE_INFERIOR_RANGO_UNO;
		tablaRangosIsr[1]=LIMITE_INFERIOR_RANGO_DOS;
		tablaRangosIsr[2]=LIMITE_INFERIOR_RANGO_TRES;
		try {	
		BufferedReader inIngresos=new BufferedReader(new FileReader(archivoIngreso));
			BufferedReader inGastos=new BufferedReader(new FileReader(archivoGasto));
			System.out.println("Abriendo archivo: "+NOMBRE_ARCHIVO_INGRESO);
			System.out.println("Abriendo archivo: "+NOMBRE_ARCHIVO_GASTO);
			
				System.out.println("Abriendo archivo: "+NOMBRE_ARCHIVO_INGRESO);
				String abrirArchivoIngresos=inIngresos.readLine();
				while(abrirArchivoIngresos!=null) {
					System.out.println("Se leyo: "+abrirArchivoIngresos);
					abrirArchivoIngresos=inIngresos.readLine();
				}
				System.out.println("Abriendo archivo: "+NOMBRE_ARCHIVO_GASTO);
				String abrirArchivoGastos=inGastos.readLine();
				while(abrirArchivoGastos!=null) {
					System.out.println("Se leyo: "+abrirArchivoGastos);
					abrirArchivoGastos=inGastos.readLine();
				}
				inIngresos.close();
				inGastos.close();
			}catch(FileNotFoundException e) {
				System.err.println("Archivo no encontrado: "+archivoIngreso);
				System.err.println("Archivo no encontrado: "+archivoGasto);
				//e.printStackTrace(System.err);
			}catch(IOException e) {
				e.printStackTrace(System.err);
			}
		}
	
	
	
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
		System.out.println("7. Eliminar un ingreso");
		System.out.println("8. Eliminar un gasto");
		System.out.println("9. Buscar ingresos");
		System.out.println("10. Guardar en archivo");
		System.out.println("11. Salir");
		System.out.println("Opcion: ");
		opcion=consola.nextInt();
		if (opcion<1 || opcion > 12) {
			System.out.println("Opcion no valida...");
			opcion=1;
		}
		consola.nextLine();
		return opcion;
	}
	
	public static void establecerMes() {
		System.out.println("ESTABLECER MES");
		System.out.println("Establecer mes para captura: ");
		for(int i=0;i<TOTAL_MESES;i++) {
			System.out.println(i+C_1+") "+meses[i]);
		}
		System.out.print("Elige el mes (1 a 12): ");
		seleccionMes=consola.nextInt();
		seleccionMes--;
		mesActual=meses[seleccionMes];
	}
	
	public static void capturarIngresos(float[] ingresoIndividual) {
		String rfc,concepto;
		int monto;
		System.out.println("Captura de ingresos");
		System.out.print("Dame el ingreso del mes de "+mesActual+"\n ");
		if (cuentaIngresos>MAX_INGRESOS) {
			System.out.println("No hay más espacio para captura...");
		}
		else {
			System.out.println("Provee los datos para el ingreso "+cuentaIngresos+C_1+": ");
			System.out.print("RFC: ");
			rfc=consola.nextLine();
			if (rfc.length()>0 && rfc.length()<=13) {
				ingresos[cuentaIngresos].rfc=rfc;
			}
			else {
				ingresos[cuentaIngresos].rfc="";
			}
			System.out.print("Concepto: ");
			concepto=consola.nextLine();
			if (concepto.length()>0 && concepto.length()<=TAMANIO_CONCEPTO) {
				ingresos[cuentaIngresos].concepto=concepto;
			}
			else {
				ingresos[cuentaIngresos].concepto="";
			}
			System.out.print("Monto: ");
			monto=consola.nextInt();
			if (monto>=0) {
				ingresos[cuentaIngresos].monto=monto;
			}
			else {
				ingresos[cuentaIngresos].monto=0;
			}
			ingresos[cuentaIngresos].mes=meses[seleccionMes];
			ingresoIndividual[seleccionMes]+=ingresos[cuentaIngresos].monto;
			cuentaIngresos++;
		}
	}
	
	public static void capturarGastos(float[] gastoIndividual) {
		String justificacion,concepto;
		int monto;
		System.out.println("Captura de gastos");
		System.out.print("Dame el gasto del mes de "+mesActual+C_1+"\n ");
		
		if (cuentaGastos>MAX_GASTOS) {
			System.out.println("No hay más espacio para captura...");
		}
		else {
			System.out.println("Provee los datos para el gasto "+cuentaGastos+": ");
			System.out.print("Concepto: ");
			concepto=consola.nextLine();
			if (concepto.length()>0 && concepto.length()<=13) {
				gastos[cuentaGastos].concepto=concepto;
			}
			else {
				gastos[cuentaGastos].concepto="";
			}
			System.out.print("Justificacion: ");
			justificacion=consola.nextLine();
			if (justificacion.length()>0 && justificacion.length()<=TAMANIO_JUSTIFICACION) {
				gastos[cuentaGastos].justificacion=justificacion;
			}
			else {
				gastos[cuentaGastos].justificacion="";
			}
			System.out.print("Monto: ");
			monto=consola.nextInt();
			if (monto>=0) {
				gastos[cuentaGastos].monto=monto;
			}
			else {
				gastos[cuentaGastos].monto=0;
			}
			gastos[cuentaGastos].mes=meses[seleccionMes];
			gastoIndividual[seleccionMes]+=gastos[cuentaGastos].monto;
			cuentaGastos++;
		}
	}
	
	public static void listarIngresos(float[] ingresoIndividual) {
		int n=C_0;
		System.out.println("LISTA DE INGRESOS");
		System.out.println("#  MES  MONTO  RFC  Concepto");
		for(int i=0;i<cuentaIngresos;i++) {
			System.out.println(n+C_1+" "+ingresos[i].mes+" = "+ingresos[i].monto+" "+ingresos[i].rfc+" "+ingresos[i].concepto);
			n++;
		}
	}
	
	public static void listarGastos(float[] gastoIndividual) {
		int n=C_0;
		System.out.println("LISTA DE GASTOS");
		System.out.println("# MES  MONTO  CONCEPTO  JUSTIFICACION");
		for(int i=0;i<cuentaGastos;i++) {
			System.out.println(n+C_1+" "+gastos[i].mes+" = "+gastos[i].monto+" "+gastos[i].concepto+" "+gastos[i].justificacion);
			n++;
		}
	}
	
	public static void eliminar(int registroAEliminar) {
		int i=registroAEliminar;
		if (cuentaIngresos>=1) {
			i--;
			for(cuentaIngresos--;i<cuentaIngresos;i++) {
				ingresos[i]=ingresos[i+1];
			}
		}
	}
	
	public static void eliminarElementoGasto(int registroAEliminar) {
		int i=registroAEliminar;
		if (cuentaGastos>=1) {
			i--;
			for(cuentaGastos--;i<cuentaGastos;i++) {
				gastos[i]=gastos[i+1];
			}
		}
	}
	
	public static void mostrarIngreso(int i,int cuentaSubCadena) {
		int n=cuentaSubCadena;
		System.out.println(n+" "+meses[i]+" = "+ingresos[i].monto+" "+ingresos[i].rfc+" "+ingresos[i].concepto);
	}
	
	public static void mostrarGasto(int i,int cuentaSubCadena) {
		int n=cuentaSubCadena;
		System.out.println(n+" "+meses[i]+" = "+gastos[i].monto+" "+gastos[i].concepto+" "+gastos[i].justificacion);
	}
	
	public static void eliminarIngreso() {
		int decision,registroAEliminar,confirmacionEliminacion;
		String subcadena;
		int cuentaSubCadena=0;
		if (cuentaIngresos>C_0) {
		System.out.println("Desea mostrar todos los casos o buscar por RFC? ");
		System.out.println("1. Todos los casos.\n 2. Buscar por RFC.");
		decision=consola.nextInt();
		switch(decision) {
		case 1:
			listarIngresos(ingresoIndividual);
			System.out.println("Qué registro deseas eliminar? ");
			registroAEliminar=consola.nextInt();
			System.out.println("Estas seguro de eliminar este registro? \n (1. Sí 2. No): ");
			confirmacionEliminacion=consola.nextInt();
			if (confirmacionEliminacion==1) {
				eliminar(registroAEliminar);
				System.out.println("Hecho.");
				pausar();
			}
			else {
				System.out.println("No se borró ningún registro...");
				pausar();
			}
			break;
		case 2:
			int eleccionRfc;
			consola.nextLine();
			System.out.println("Dame el RFC que quieres eliminar: ");
			subcadena=consola.nextLine();
			pausar();
			for(int i=0;i<cuentaIngresos;i++) {
				if (ingresos[i].rfc.contains(subcadena)) {
					cuentaSubCadena++;
					mostrarIngreso(i,cuentaSubCadena);
					System.out.print("Deseas eliminar este registro? (1 si, 2 no): ");
					eleccionRfc=consola.nextInt();
					if (eleccionRfc==1) {
						eliminar(i);
					}
					else {
						System.out.println("");
					}
				}
			}
			System.out.println("Se encontraron " + cuentaSubCadena + " registros!");
			pausar();
			break;
		default:
			System.out.println("Opcion no valida...");
		}
		}
		else {
			System.out.println("No hay espacio para captura...");
		}
	}
	
	public static void eliminarGasto() {
		int decision,gastoAEliminar,confirmacionEliminacion;
		String subcadena;
		int cuentaSubCadena=0;
		if (cuentaGastos>C_0) {
		System.out.println("Desea mostrar todos los casos o buscar por RFC? ");
		System.out.println("1. Todos los casos.\n 2. Buscar por RFC.");
		decision=consola.nextInt();
		switch(decision) {
		case 1:
			listarGastos(gastoIndividual);
			System.out.println("Qué registro deseas eliminar? ");
			gastoAEliminar=consola.nextInt();
			System.out.println("Estas seguro de eliminar este registro? \n (1. Sí 2. No): ");
			confirmacionEliminacion=consola.nextInt();
			if (confirmacionEliminacion==1) {
				eliminarElementoGasto(gastoAEliminar);
				System.out.println("Hecho.");
				pausar();
			}
			else {
				System.out.println("No se borró ningún registro...");
				pausar();
			}
			break;
		case 2:
			int eleccionConcepto;
			consola.nextLine();
			System.out.println("Dame el concepto que quieres eliminar: ");
			subcadena=consola.nextLine();
			pausar();
			for(int i=0;i<cuentaGastos;i++) {
				if (gastos[i].concepto.contains(subcadena)) {
					cuentaSubCadena++;
					mostrarGasto(i,cuentaSubCadena);
					System.out.print("Deseas eliminar este registro? (1 si, 2 no): ");
					eleccionConcepto=consola.nextInt();
					if (eleccionConcepto==1) {
						eliminarElementoGasto(i);
					}
					else {
						System.out.println("");
					}
				}
			}
			System.out.println("Se encontraron " + cuentaSubCadena + " registros!");
			pausar();
			break;
		default:
			System.out.println("Opcion no valida...");
		}
		}
		else {
			System.out.println("No hay espacio para captura...");
		}
	}
	
	public static void buscarIngresos() {
		String rfcABuscar;
		int encontrado=0;
		if (cuentaIngresos>C_0) {
			System.out.print("Dame el RFC a buscar: ");
			rfcABuscar=consola.nextLine();
			for(int i=C_0;i<cuentaIngresos;i++) {
				if (ingresos[i].rfc.contains(rfcABuscar)) {
					encontrado++;
					mostrarIngreso(i,encontrado);
				}
			}
		}
		else {
			System.out.println("No hay registros por buscar...");
		}
	}
	
	public static void calcularPorcentajeAplicableIsr(float gananciaBruta) {
		if (gananciaBruta < C_0) {
			isrAplicado=C_0;
		}
		else if (gananciaBruta>tablaRangosIsr[0] && gananciaBruta <tablaRangosIsr[1]) {
        	isrAplicado=tablaPorcentajeIsr[C_0];
        }
        else if (gananciaBruta>tablaRangosIsr[1] && gananciaBruta<tablaRangosIsr[2]) {
        	isrAplicado=tablaPorcentajeIsr[C_1];
        }
        else {
        	isrAplicado=tablaPorcentajeIsr[C_2];
        }
	}
	
	public static void calculoImpuestosAnual(float[] ingresoIndividual,float[] gastoIndividual,File archivoFile,File archivoIngreso,File archivoGasto) {
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
        calcularPorcentajeAplicableIsr(gananciaBruta);
        try {
        	PrintStream archivo=new PrintStream(archivoFile);
        	PrintStream archivoListaIngreso=new PrintStream(archivoIngreso);
        	PrintStream archivoListaGasto=new PrintStream(archivoGasto);
        	escribirCalculoImpuestosAnual(archivo);
        	escribirListaIngresos(archivoListaIngreso,ingresoIndividual);
        	escribirListaGastos(archivoListaGasto,gastoIndividual);
        	archivo.close();
        	archivoListaIngreso.close();
        	archivoListaGasto.close();
        }catch(IOException e) {
        	e.printStackTrace(System.err);
        }
      escribirCalculoImpuestosAnual(System.out);
	}
	
	public static void escribirListaGastos(PrintStream salidaGasto,float[] gastoIndividual) {
		for(int i=C_0;i<TOTAL_MESES;i++) {
			salidaGasto.append(meses[i]+" = "+gastoIndividual[i]+"\n");
		}
	}
	
	public static void escribirListaIngresos(PrintStream salidaIngreso,float[] ingresoIndividual) {
		for(int i=C_0;i<TOTAL_MESES;i++) {
			salidaIngreso.append(meses[i]+" = "+ingresoIndividual[i]+"\n");
		}
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
	  salida.println("ISR          "+isrAplicado+"% "+calculoIsr);
	  salida.println("(-) ISR Retenido  "+calculoRetencionIsr);
	  salida.println("(=) ISR a Pagar   "+pagoIsr);
	  salida.println("TABLA IVA         \n");
	  salida.println("IVA               "+calculoIva);
	  salida.println("(-) Gasto IVA     "+gastoIva);
	  salida.println("(-) Retencion IVA "+calculoRetencionIva);
	  salida.println("(=) IVA a Pagar   "+pagoIva);
  }
  
  public static void pausar() {
		System.out.println("Presione entrar para continuar...");
		consola.nextLine();
	}
  

	public static void main(String[] args) {
		//Declaracion y definicion de constantes
		DateTimeFormatter dtf = DateTimeFormatter.ofPattern("_yyyy_MM_dd_HH_mm_ss");
		LocalDateTime now = LocalDateTime.now();
		final String NOMBRE_ARCHIVO="MiArchivoPractica3"+dtf.format(now)+".txt";
		final String NOMBRE_ARCHIVO_GASTO="TablaGastosPractica3.txt";
		final String NOMBRE_ARCHIVO_INGRESO="TablaIngresoPractica3.txt";
		File archivoFile=new File(NOMBRE_ARCHIVO);
		File archivoGasto=new File(NOMBRE_ARCHIVO_GASTO);
		File archivoIngreso=new File(NOMBRE_ARCHIVO_INGRESO);
		boolean seguirEjecutandoPrograma=true;
		inicializar(archivoIngreso,archivoGasto,NOMBRE_ARCHIVO_INGRESO,NOMBRE_ARCHIVO_GASTO,ingresoIndividual,gastoIndividual);
		//Entrada de datos
    int opcion = 0;
		do {
			switch(opcion = menuPrincipal()) {
			case 1:
				establecerMes();
				break;
			case 2:
				capturarIngresos(ingresoIndividual);
				break;
			case 3: 
				capturarGastos(gastoIndividual);
				break;
			case 4:
				listarIngresos(ingresoIndividual);
				break;
			case 5:
				listarGastos(gastoIndividual);
				break;
			case 6:
				calculoImpuestosAnual(ingresoIndividual,gastoIndividual,archivoFile,archivoIngreso,archivoGasto);
				break;
			case 7:
				eliminarIngreso();
				break;
			case 8:
				eliminarGasto();
			case 9:
				buscarIngresos();
				break;
			case 10:
				System.out.println("En construccion...");
			case 11:
				System.out.println("Saliste del programa...");
				seguirEjecutandoPrograma=false;
				break;
	        default:
	          System.out.println("Error, opcion invalida!");
			    }
			if (opcion != 7 ) { 
				pausar();
			}
		}while(seguirEjecutandoPrograma);
		consola.close();
	}
}
