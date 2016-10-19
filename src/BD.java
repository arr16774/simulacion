import java.sql.DriverManager;
import java.sql.SQLException;

import com.mysql.jdbc.Connection;

public class BD {
	private String url = "jdbc:mysql://localhost/mydb";
 	private String us="root";
 	private String psw= "uvg";
 	private Connection conn;
 	
 	public BD (){
 		conn = null;
	 	try{
			Class.forName("com.mysql.jdbc.Connection");
			conn = (Connection)DriverManager.getConnection(url, us, psw);
			if(conn != null)
			{
				System.out.println("Conexi-n a base de datos "+url+" . . . Ok");
			}
		}
		catch(SQLException ex){
			System.out.println("Hubo un problema al intentar conecarse a la base de datos"+url);
		}
		catch(ClassNotFoundException ex){
			System.out.println(ex);
		}	
 	}
 	
 	public Connection getCon(){
 		return conn;
 	}
 	
 	public int prueba(){
 		java.sql.Statement st = null;
 		String s=new String();
 		int t=0;
	 	try {
			st = conn.createStatement();
		} catch (SQLException e2) {
			// TODO Auto-generated catch block
			e2.printStackTrace();
		}
	 	
	 	try{
	 		int monto;
		 	s = "Select idDinero from Dinero where idDinero = 16;";
        	try {
				System.out.println(st.executeUpdate(s));
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
	 	} catch (Exception exc){
	 		exc.printStackTrace();
	 	}
	 	return t;
 	}
}
