package com.swrd.gmp;

import javax.swing.JLabel;
import javax.swing.JOptionPane;

public class ErrorClass { 

	public static JLabel lblError;
	public static GmpDll gmpDll;
	
    public static void HandleErrorCode(int errorCode)
    {
         DisplayErrorMessage(errorCode);

         if (errorCode == Defines.APP_ERR_GMP3_INVALID_HANDLE)
         {
        	 if (JOptionPane.showConfirmDialog(null, "ÖKC Fisi Yenilenmis. Yüklemek ister misiniz?", "UYARI", JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION) 
                 return;

             // ÖKC'deki fis bir sebepten yeniden baslamis ve handle degismis
             // Start fonksiyonu guncel handle'i alabilir 
        	 byte[] uniqueId = new byte[10];
        	 byte[] uniqueIdSign = new byte[100]; //datalar alinmak istemedigi için size dummy olarak verilmistir. 
             byte[] userData     = new byte[100];
 
        	 int retcode = gmpDll.FiscalPrinter_Start(uniqueId, uniqueId.length,uniqueIdSign,uniqueIdSign.length,userData,userData.length,300);
        	 
             if (retcode == Defines.APP_ERR_ALREADY_DONE)
                 //retcode = ReloadTransaction();

                 if (retcode == 0)
                     DisplayErrorMessage(retcode);
         }
     }


     private static void DisplayErrorMessage(int errorCode)
     {
         byte[] TempErrorBuffer = new byte[256];

         gmpDll.GetErrorMessage(errorCode, TempErrorBuffer);
         
         lblError.setText("Hata Kodu = 0x" + String.format("%4s",Integer.toHexString(errorCode)).replace(' ', '0') + " : " + new String(TempErrorBuffer).trim());
        
         if(errorCode != 0)
        	 lblError.setForeground(Utility.colorNOK);
         else
        	 lblError.setForeground(Utility.colorOK);
     }
     /**/
}
