 /****************************************************************/
/* GradeBook Application: grade1.java (Section 5.6)             */
/* Needs run2.java to be compiled                             */
/* Chapter 5; Oracle Programming -- A Primer                    */
/*            by R. Sunderraman                                 */
/****************************************************************/

import java.sql.*; 
import java.io.*; 

class run1 { 

  void print_menu() {
    System.out.println("      RUNNING COMPANY\n");
    System.out.println("(1) Add a runner");
    System.out.println("(2) Edit personal information for a runner");
    System.out.println("(3) Delete a runner ");
    System.out.println("(4) See information for all runners");
	System.out.println("(5) Print a report");
    System.out.println("(q) Quit\n");
  }

  void add_runner(Connection conn) 
    throws SQLException, IOException {
         
    Statement stmt = conn.createStatement(); 

	String id = readEntry("Enter a racer id: ");
    String fname = readEntry("Enter the runner's first name: ");
    String lname = readEntry("Enter the runner's last name: ");
	String email = readEntry("What is the runner's email address?: ");
	String birthdate = readEntry("What is the runner's birthday?: ");
	String tshirt_size = readEntry("Enter the runner's t-shirt size: ");
	String phone_number = readEntry("Enter the runner's phone number: ");
        String query = "insert into runners values (" + id +
            ",'" + fname + "','" + lname + "','" +
            email + "','" + birthdate + "','" + 
			tshirt_size + "','" + phone_number + "')";
    try {
      int nrows = stmt.executeUpdate(query);
    } catch (SQLException e) {
        System.out.println("Error Adding Runner");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }
    stmt.close();
    System.out.println("Added Runner Entry");
  }

  void delete_runner(Connection conn) 
	throws SQLException, IOException { 
	
	String select = "select * from runners";
     
    Statement stmt = conn.createStatement (); 
    ResultSet rset = stmt.executeQuery(select);
	
	System.out.println("  ID                Fname" +
						"                         Lname"
						+ "\n--------------------------------------------------------");

	while (rset.next ()) { 
 	  
	  for(int i = 1; i <= 3; i++)
	  {
		  if(i == 1){
			  System.out.print(String.format("%1$4s", rset.getString(i)));
			  System.out.print(" ");
		  }
		  else if(i == 2){
			  System.out.print(String.format("%1$20s", rset.getString(i)));
			  System.out.print(" ");
		  }
		  else{
			  System.out.print(String.format("%1$30s", rset.getString(i)));
			  System.out.print(" ");
		  }
	  }
	  System.out.println("");
	}


    String id = readEntry("Enter the id of the runner you wish to delete: ");
    String query = "delete from runners where racer_id = " + id;
	
	try {
      int nrows = stmt.executeUpdate(query);
    } catch (SQLException e) {
        System.out.println("Error Adding Catalog Entry");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }
    stmt.close();
    System.out.println("Runner successfully deleted.");
    
  }

void edit_runner(Connection conn) 
	throws SQLException, IOException {
    String select = "select * from runners";
     
    Statement stmt = conn.createStatement (); 
    ResultSet rset = stmt.executeQuery(select);
	
	System.out.println("  ID                Fname" +
						"                         Lname");
	System.out.println("--------------------------------------------------------");

	while (rset.next ()) { 
 	  
	  for(int i = 1; i <= 3; i++)
	  {
		  if(i == 1){
			  System.out.print(String.format("%1$4s", rset.getString(i)));
			  System.out.print(" ");
		  }
		  else if(i == 2){
			  System.out.print(String.format("%1$20s", rset.getString(i)));
			  System.out.print(" ");
		  }
		  else{
			  System.out.print(String.format("%1$30s", rset.getString(i)));
			  System.out.print(" ");
		  }
	  }
	  System.out.println("");
	}


    String id = readEntry("Enter the id of the runner you wish to update: ");
    
	//TODO Display current attributes for the selected racer_id
	
	Statement stmt2 = conn.createStatement (); 	
	String query = "select * from runners where racer_id = " + id;
	
	try {
      int nrows = stmt2.executeUpdate(query);
    } catch (SQLException e) {
        System.out.println("Error finding runner.");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }
	
	 ResultSet singleRunner = stmt.executeQuery(query);
	
 	  
	System.out.println("  ID                Fname" +
						"                         Lname" +
						"                           Email\tBirthdate"
						+ " TSS PHONE_NUMBER");
	System.out.println("--------------------------------------" +
					   "--------------------------------------" +
					   "--------------------------------------");
	
	while (singleRunner.next ()) { 
		for(int i = 1; i <= 7; i++)
		{
			if(i == 1){
				System.out.print(String.format("%1$4s", singleRunner.getString(i)));
				System.out.print(" ");
			}
			else if(i == 2){
				System.out.print(String.format("%1$20s", singleRunner.getString(i)));
				System.out.print(" ");
			}
			else if(i == 3){
				System.out.print(String.format("%1$30s", singleRunner.getString(i)));
				System.out.print(" ");
			}
			  else if(i == 4){
				  System.out.print(String.format("%1$30s", singleRunner.getString(i)));
				  System.out.print(" ");
			  }
			  else if(i == 5){
				  String bdate = singleRunner.getString(i).substring(0,10); //remove time from date object
				  System.out.print(bdate);
				  System.out.print(" ");
			  }
			  else if(i == 6){
				  System.out.print(String.format("%1$3s", singleRunner.getString(i)));
				  System.out.print(" ");
			  }
			  else{
				  System.out.print(String.format("%1$10s", singleRunner.getString(i)));
				  System.out.print(" ");
			  }
		}
		System.out.println("");
	} 
	System.out.println("");
	
	run2 r2 = new run2();
	char ch, ch1;
	boolean done = false;
    do {
      r2.print_menu();
      System.out.print("Which value would you like to change?: ");
      System.out.flush();
      ch = (char) System.in.read();
	  if(ch == 'q'){
		  done = true;
	  }
      ch1 = (char) System.in.read();
      
	  r2.modify_runner(conn, id, ch);
    } while (!done);    
  }		
		
void reports(Connection conn) throws SQLException, IOException {
	
	run2 r2 = new run2();
	char ch, ch1;
	
	System.out.print("Reports\n--------------------\n" + 
					 "1.) T-shirt order\n2.) Employee Breakdown\nq.) quit.\n");
	System.out.print("Select a report to print: ");
      System.out.flush();
      ch = (char) System.in.read();
	  if(ch == 'q'){
		  return;
	  }
      ch1 = (char) System.in.read();
	  
	  switch (ch) {
		  case '1': r2.tshirts(conn);
					break;
		  case '2': r2.employees(conn);
					break;
		  default : break;
	  }
	  
	
}
		
  void see_runners(Connection conn) 
    throws SQLException, IOException {

    String query = "select * from runners";
     
    Statement stmt = conn.createStatement (); 
    ResultSet rset = stmt.executeQuery(query);
    ResultSetMetaData metadata = rset.getMetaData();
	int columns = metadata.getColumnCount();
	
	System.out.println("  ID                Fname" +
						"                         Lname" +
						"                           Email\tBirthdate"
						+ " TSS PHONE_NUMBER");
	System.out.println("--------------------------------------" +
					   "--------------------------------------" +
					   "--------------------------------------");
    while (rset.next ()) { 
      for(int i = 1; i <= columns; i++)
	  {
		  if(i == 1){
			  System.out.print(String.format("%1$4s", rset.getString(i)));
			System.out.print(" ");
		  }
		  else if(i == 2){
			  System.out.print(String.format("%1$20s", rset.getString(i)));
			  System.out.print(" ");
		  }
		  else if(i == 3){
			  System.out.print(String.format("%1$30s", rset.getString(i)));
			  System.out.print(" ");
		  }
		  else if(i == 4){
			  System.out.print(String.format("%1$30s", rset.getString(i)));
			  System.out.print(" ");
		  }
		  else if(i == 5){
			  String bdate = rset.getString(i).substring(0,10); //remove time from date object
			  System.out.print(bdate);
			  System.out.print(" ");
		  }
		  else if(i == 6){
			  System.out.print(String.format("%1$3s", rset.getString(i)));
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
