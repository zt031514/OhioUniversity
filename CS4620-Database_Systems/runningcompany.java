/****************************************************************/
/* runningCompany main class              						*/
/* Needs run1.java and run2.java to be compiled            		*/
/* Chapter 5; Oracle Programming -- A Primer                    */
/*            by R. Sunderraman and Zach Tumbleson              */
/****************************************************************/

import java.io.*; 
import java.sql.*;

class runningCompany { 

  public static void main (String args []) 
      throws SQLException, IOException { 

    run1 r1 = new run1();
    boolean done;
    char ch,ch1;
    byte num = 0;

    try {
      Class.forName ("oracle.jdbc.driver.OracleDriver");
    } catch (ClassNotFoundException e) {
        System.out.println ("Could not load the driver");
        return;
      }
    String user, pass;
    user = readEntry("userid  : ");
    pass = readEntry("password: ");

    //  The following line was modified by Prof. Marling to work on prime

    Connection conn = DriverManager.getConnection
       ("jdbc:oracle:thin:@deuce.cs.ohio.edu:1521:class", user, pass);

	done = false;
    do {
      r1.print_menu();
      System.out.print("Type in your option:");
      System.out.flush();
      ch = (char) System.in.read();
      ch1 = (char) System.in.read();
      switch (ch) {
        case '1' : r1.add_runner(conn);
                   break;
        case '2' : r1.edit_runner(conn);
                   break;
        case '3' : r1.delete_runner(conn);
                   break;
        case '4' : r1.see_runners(conn);
                   break;
		case '5' : r1.reports(conn);
				   break;
        case 'q' : done = true;
                   break;
        default  : System.out.println("Type in option again");
      }
    } while (!done);

    conn.close();
  }

  //readEntry function -- to read input string
  static String readEntry(String prompt) {
     try {
       StringBuffer buffer = new StringBuffer();
       System.out.print(prompt);
       System.out.flush();
       int c = System.in.read();
       while(c != '\n' && c != -1) {
         buffer.append((char)c);
         c = System.in.read();
       }
       return buffer.toString().trim();
     } catch (IOException e) {
       return "";
       }
   }
} 
