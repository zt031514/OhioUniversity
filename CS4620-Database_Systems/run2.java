/****************************************************************/
/* GradeBook Application - grade2.java (Section 5.6)            */
/* Chapter 5; Oracle Programming -- A Primer                    */
/*            by R. Sunderraman                                 */
/****************************************************************/

import java.sql.*; 
import java.io.*; 

class run2 { 

  void print_menu() {
    System.out.println("      Modify runner SUB-MENU\n");
    System.out.println("(1) First Name");
    System.out.println("(2) Last name");
    System.out.println("(3) Email");
    System.out.println("(4) Birthday");
    System.out.println("(5) Tshirt size");
    System.out.println("(6) Phone Number");
    System.out.println("(q) Quit\n");
  }

  void modify_runner(Connection conn, String id, char column) 
      throws SQLException, IOException {
	String query1 = "";  
	
	if(column == 'q'){
		return;
	}
	
	String value = readEntry("Enter a new value: ");
	
	switch (column) {
        case '1' : query1 = "update runners set fname = '" + value + "' " + "where racer_id = " + id; 
				   break;
        case '2' : query1 = "update runners set lname = '" + value + "' " + "where racer_id = " + id;
                   break;
        case '3' : query1 = "update runners set email = '" + value + "' " + "where racer_id = " + id;
                   break;
        case '4' : query1 = "update runners set birthdate = '" + value + "' " + "where racer_id = " + id;
                   break;
        case '5' : query1 = "update runners set tshirt_size = '" + value + "' " + "where racer_id = " + id;
                   break;
		case '6' : query1 = "update runners set phone_number = '" + value + "' " + "where racer_id = " + id;
				   break;
        default  : System.out.println("Type in option again");
    }   
	  
    Statement stmt = conn.createStatement (); 
    ResultSet rset;
	
    try {
      rset = stmt.executeQuery(query1);
    } catch (SQLException e) {
        System.out.println("Error");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }
	  System.out.println("");
}

 
void tshirts(Connection conn) throws SQLException, IOException{
	String query1 = "select name, tshirt_size, count(tshirt_size) from ((runners natural join participates_in) join races on races.race_id = participates_in.race_id ) group by tshirt_size, name order by name";			   
	String query2 = "select tshirt_size, count(tshirt_size) from runners where racer_id = racer_id group by tshirt_size";
	String query3 = "select (count(tshirt_size)) from runners";
	
	Statement stmt = conn.createStatement (); 
    ResultSet rset;
	
    try {
      rset = stmt.executeQuery(query1);
    } catch (SQLException e) {
        System.out.println("Error");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }
	  System.out.println("");

	 ResultSetMetaData metadata = rset.getMetaData();
	int columns = metadata.getColumnCount();
	
	System.out.println("Number of t-shirts of each size per race");
	System.out.println("NAME                                                                    " +
					   "                                                                    " +
					   "           TSH   COUNT(TSHIRT_SIZE)");
	System.out.println("--------------------------------------------------------------" +
					   "-------------------------------------------------------");
    while (rset.next()) { 
      for(int i = 1; i <= columns; i++)
	  {
		  if(i == 1){
			  System.out.print(String.format("%1$-150s", rset.getString(i)));
			  System.out.print(" ");
		  }
		  else if(i == 2){
			  System.out.print(String.format("%1$3s", rset.getString(i)));
			  System.out.print(" ");
		  }
		  else {
			  System.out.print(String.format("%1$3s", rset.getString(i)));
			  System.out.print(" ");
		  }
	  }
	  System.out.println(""); //done printing a row, continue to the next line
    } 
    System.out.println("");
	
	try {
      rset = stmt.executeQuery(query2);
    } catch (SQLException e) {
        System.out.println("Error");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }
	  System.out.println("");

	metadata = rset.getMetaData();
	columns = metadata.getColumnCount();
	
	System.out.println("Total count of each size of t-shirt");
	System.out.println("TSH\tCOUNT(TSHIRT_SIZE)");
	System.out.println("-----------------------");
	
    while (rset.next()) { 
      for(int i = 1; i <= columns; i++)
	  {
		  if(i == 1){
			  System.out.print(String.format("%1$3s", rset.getString(i)));
			  System.out.print(" ");
		  }
		  else {
			  System.out.print(String.format("%1$3s", rset.getString(i)));
			  System.out.print(" ");
		  }
	  }
	  System.out.println(""); //done printing a row, continue to the next line
    } 
    System.out.println("");
	
	try {
      rset = stmt.executeQuery(query3);
    } catch (SQLException e) {
        System.out.println("Error");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }
	  System.out.println("");

	metadata = rset.getMetaData();
	columns = metadata.getColumnCount();
	
	System.out.println("Total number of t-shirts");
	System.out.println("COUNT(TSHIRT_SIZE)");
	System.out.println("------------------");
	
    while (rset.next()) { 
      for(int i = 1; i <= columns; i++)
	  {
		System.out.print(String.format("%1$3s", rset.getString(i)));
		System.out.print(" ");
	  }
	  System.out.println(""); //done printing a row, continue to the next line
    } 
    System.out.println("");
  }

void employees(Connection conn) throws SQLException, IOException{
	//Total Salary per race
	String query1 = "select name, sum(salary) from ((employees natural join works_on) join races on races.race_id = works_on.race_id) group by races.name order by name";
	
	//Number of employees per race
	String query2 = "select name, count(emp_id) from ((employees natural join works_on) join races on races.race_id = works_on.race_id) group by races.name order by name";

	//Total Payroll
	String query3 = "select sum(salary) from employees";
	
	Statement stmt = conn.createStatement (); 
    ResultSet rset;
	
    try {
      rset = stmt.executeQuery(query1);
    } catch (SQLException e) {
        System.out.println("Error");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }
	  System.out.println("");

	ResultSetMetaData metadata = rset.getMetaData();
	int columns = metadata.getColumnCount();
	
	System.out.println("Total Salary per Race");
	System.out.println("NAME                                                                    " +
					   "                                                                    " +
					   "           SUM(SALARY)");
	System.out.println("--------------------------------------------------------------" +
					   "-------------------------------------------------------");
    while (rset.next()) { 
      for(int i = 1; i <= columns; i++)
	  {
		  if(i == 1){
			  System.out.print(String.format("%1$-150s", rset.getString(i)));
			  System.out.print(" ");
		  }
		  else{
			  System.out.print(String.format("%1$10s", rset.getString(i)));
			  System.out.print(" ");
		  }
	  }
	  System.out.println(""); //done printing a row, continue to the next line
    } 
    System.out.println("");
	
	try {
      rset = stmt.executeQuery(query2);
    } catch (SQLException e) {
        System.out.println("Error");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }
	  System.out.println("");

	metadata = rset.getMetaData();
	columns = metadata.getColumnCount();
	
	System.out.println("Employees per Race");
	System.out.println("NAME                                        NUM_EMPLOYEES");
	System.out.println("----------------------------------------------" +
					   "----------------------------------------------" +
					   "-------------------------");
	
    while (rset.next()) { 
      for(int i = 1; i <= columns; i++)
	  {
		  if(i == 1){
			  System.out.print(String.format("%1$-150s", rset.getString(i)));
			  System.out.print(" ");
		  }
		  else {
			  System.out.print(String.format("%1$10s", rset.getString(i)));
			  System.out.print(" ");
		  }
	  }
	  System.out.println(""); //done printing a row, continue to the next line
    } 
    System.out.println("");
	
	try {
      rset = stmt.executeQuery(query3);
    } catch (SQLException e) {
        System.out.println("Error");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }

	metadata = rset.getMetaData();
	columns = metadata.getColumnCount();
	
	System.out.println("Total Payroll");
	System.out.println("SUM(SALARY)");
	System.out.println("-----------");
	
    while (rset.next()) { 
      for(int i = 1; i <= columns; i++)
	  {
		System.out.print(String.format("%1$10s", rset.getString(i)));
		System.out.print(" ");
	  }
	  System.out.println(""); //done printing a row, continue to the next line
    } 
    System.out.println("");
	
	//Cost of employees per race
	//Total payroll*/
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