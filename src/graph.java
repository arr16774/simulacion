import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.Statement;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.DefaultComboBoxModel;

public class graph {

	private JFrame frame;
	private JTextField textIngreso;
	private JTextField txtNombre;
	private JTextField textCant;
	private JLabel lblIngresarGasto;
	private JLabel lblIngresarDinero;
	private JLabel lblTipo;
	private JLabel lblCosto;
	private JLabel lblPeriodicidad;
	private JLabel lblDia;
	private JLabel lblMes;
	private JComboBox cmbDia;
	private JComboBox cmbMes;
	private JComboBox comboBoxTiempo;
	private JComboBox cmbTipo;
	private JButton btnVerDatos;
	private JButton btnGraficar;
	private JButton btnAniadirGasto;
	private JButton btnIngresarCantidad;
	private JButton btnModificarGasto;
	private JFrame grafica;
	private Statement state;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					graph window = new graph();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public graph() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setBounds(100, 100, 598, 346);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		
		grafica = new JFrame();
		grafica.setBounds(100, 100, 598, 346);
		grafica.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		grafica.getContentPane().setLayout(null);
		grafica.setVisible(false);
		
		
		JLabel lblIngresarGasto = new JLabel("Ingresar Gasto");
		lblIngresarGasto.setBounds(67, 25, 177, 16);
		frame.getContentPane().add(lblIngresarGasto);
		
		JLabel lblIngresarDinero = new JLabel("A\u00F1adir cantidad a Ingresos");
		lblIngresarDinero.setBounds(346, 25, 219, 16);
		frame.getContentPane().add(lblIngresarDinero);
		
		textIngreso = new JTextField();
		textIngreso.setBounds(364, 54, 116, 22);
		frame.getContentPane().add(textIngreso);
		textIngreso.setColumns(10);
		
		txtNombre = new JTextField();
		txtNombre.setBounds(158, 53, 116, 22);
		frame.getContentPane().add(txtNombre);
		txtNombre.setColumns(10);
		
		JLabel lblTipoDeGasto = new JLabel("Tipo de Gasto:");
		lblTipoDeGasto.setBounds(12, 94, 128, 16);
		frame.getContentPane().add(lblTipoDeGasto);
		
		btnIngresarCantidad = new JButton("Ingresar Cantidad");
		btnIngresarCantidad.setBounds(345, 90, 169, 25);
		frame.getContentPane().add(btnIngresarCantidad);
		btnIngresarCantidad.addActionListener(new Listener());
		
		btnModificarGasto = new JButton("Modificar Gasto");
		btnModificarGasto.setBounds(346, 235, 168, 25);
		frame.getContentPane().add(btnModificarGasto);
		btnModificarGasto.addActionListener(new Listener());
		
		btnGraficar = new JButton("Graficar");
		btnGraficar.setBounds(364, 184, 97, 25);
		frame.getContentPane().add(btnGraficar);
		btnGraficar.addActionListener(new Listener());
		
		cmbTipo = new JComboBox();
		cmbTipo.setModel(new DefaultComboBoxModel(new String[] {"Osio","Servicios","Comida","Estudios"}));
		cmbTipo.setBounds(158, 90, 116, 22);
		frame.getContentPane().add(cmbTipo);
		
		JLabel lblCosto = new JLabel("Costo:");
		lblCosto.setBounds(54, 123, 72, 16);
		frame.getContentPane().add(lblCosto);
		
		textCant = new JTextField();
		textCant.setBounds(158, 122, 116, 22);
		frame.getContentPane().add(textCant);
		textCant.setColumns(10);
		
		JLabel lblNombre = new JLabel("Nombre:");
		lblNombre.setBounds(42, 54, 109, 16);
		frame.getContentPane().add(lblNombre);
		
		JLabel lblDia = new JLabel("Dia:");
		lblDia.setBounds(23, 173, 35, 16);
		frame.getContentPane().add(lblDia);
		
		cmbDia = new JComboBox();
		cmbDia.setModel(new DefaultComboBoxModel(new String[] {"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31",}));
		cmbDia.setBounds(70, 170, 56, 22);
		frame.getContentPane().add(cmbDia);
		
		JLabel lblMes = new JLabel("Mes:");
		lblMes.setBounds(138, 173, 35, 16);
		frame.getContentPane().add(lblMes);
		
		cmbMes = new JComboBox();
		cmbMes.setModel(new DefaultComboBoxModel(new String[] {"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre",}));
		cmbMes.setBounds(185, 170, 89, 22);
		frame.getContentPane().add(cmbMes);
		
		btnVerDatos = new JButton("Ver Datos");
		btnVerDatos.setBounds(364, 135, 128, 25);
		frame.getContentPane().add(btnVerDatos);
		btnVerDatos.addActionListener(new Listener());
		
		JLabel lblPeriodicidad = new JLabel("Periodicidad:");
		lblPeriodicidad.setBounds(23, 217, 103, 16);
		frame.getContentPane().add(lblPeriodicidad);
		
		comboBoxTiempo = new JComboBox();
		comboBoxTiempo.setModel(new DefaultComboBoxModel(new String[] {"Ninguna","Diaria","Semanal","Mensual","Anual"}));
		comboBoxTiempo.setBounds(158, 214, 116, 22);
		frame.getContentPane().add(comboBoxTiempo);
		
		btnAniadirGasto = new JButton("A\u00F1adir Gasto");
		btnAniadirGasto.setBounds(94, 261, 132, 25);
		frame.getContentPane().add(btnAniadirGasto);
		btnAniadirGasto.addActionListener(new Listener());
		
	
	}
	
	class Listener implements ActionListener{
		private BD mydb = new BD();
		@Override
		public void actionPerformed(ActionEvent e) {
			 if (e.getSource() == btnAniadirGasto) {
					 	
					 	java.sql.Statement st = null;
					 	Connection conn = mydb.getCon();
					 	
					 	try {
							st = conn.createStatement();
						} catch (SQLException e2) {
							// TODO Auto-generated catch block
							e2.printStackTrace();
						}
					 	
					 	try{
					 		int monto;
					 		
					 		String s;
						 	s = "INSERT INTO Dinero VALUES (0,"+ textCant.getText() +" , '" + txtNombre.getText()+"', '"+ cmbTipo.getSelectedItem().toString() +"',"+ cmbDia.getSelectedItem().toString()+",'"+ cmbMes.getSelectedItem().toString()+"', 0 );";
				        	try {
								st.executeUpdate(s);
							} catch (SQLException e1) {
								// TODO Auto-generated catch block
								e1.printStackTrace();
							}
					 	} catch (Exception exc){
					 		exc.printStackTrace();
					 	}

			 } 	
			 if (e.getSource() == btnGraficar) {
				 	
				 	grafica.setVisible(true);
		        	System.out.println(mydb.prueba());
		        }
		        
		     if (e.getSource() == btnVerDatos) {
		        	System.out.println("Pasa algo");
		        }
		        
		     if (e.getSource() == btnModificarGasto) {
		        	System.out.println("Pasa algo");
		        }
		        
		     if (e.getSource() == btnIngresarCantidad) {
		    	 	try{
			        	int ingreso = Integer.parseInt(textIngreso.getText());
			        	System.out.println("Pasa algo");
		    	 	}
		    	 	catch (Exception s){
		    	 		
		    	 	}
		        }
		
		}

	
	}
}	

