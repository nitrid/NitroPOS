package com.swrd.gmp;

import java.awt.Color;
import javax.swing.JLabel;

public class Utility {

	public static Color colorOK= new Color(0,150,0);;
	public static Color colorNOK= new Color(150,0,0);;
	
	public static boolean isNumeric(String str)  
	{  
	  try  
	  {  
	    @SuppressWarnings("unused")
		double d = Double.parseDouble(str);  
	  }  
	  catch(NumberFormatException nfe)  
	  {  
	    return false;  
	  }  
	  return true;  
	}
	
	
	public static void setLblTxt(JLabel lblName, Color labelColor, String text)
	{
		
		lblName.setForeground(labelColor);
		lblName.setText(text); 
		 
	}
	
	
}
