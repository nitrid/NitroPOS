package com.swrd.gmp;

import javax.swing.JDialog;
import javax.swing.GroupLayout;
import javax.swing.GroupLayout.Alignment;
import javax.swing.JList;
import javax.swing.JButton;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Font;
import java.text.ParseException;

import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.JFormattedTextField;
import javax.swing.text.MaskFormatter;

@SuppressWarnings("serial")
public class BankList extends JDialog {
	private final JList<String> lstBankList;
	private JFormattedTextField txtInstallment;
	
	public String strInstallment;
	
	/**
	 * Launch the application.
	 */	  
	public int start() {
		try {
			this.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
			this.setModal(true);
			this.setVisible(true); 
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		return lstBankList.getSelectedIndex();
		
	}

	/**
	 * Create the dialog.
	 */
	public BankList(byte numberOfTotalRecordsReceived, GmpDll.ST_PAYMENT_APPLICATION_INFO[] stPaymentApplicationInfo) {
		
		String[] list = new String[numberOfTotalRecordsReceived];
				
		for (int i = 0; i < numberOfTotalRecordsReceived ; i++)
		{

			String bkmid = String.format("%04d", stPaymentApplicationInfo[i].u16BKMId);
			String pri   =String.format("%03d", stPaymentApplicationInfo[i].Priority);
			String name =  String.format("%-10s", new String(stPaymentApplicationInfo[i].name).trim());
			list[i] = name +"(bkmid:"+bkmid + " pri:"+  pri + ")"; 

		}
		
		setBounds(100, 100, 450, 300);
		getContentPane().setLayout(null);
		lstBankList = new JList(list);
		lstBankList.setFont(new Font("Lucida Console", Font.PLAIN, 11));
		lstBankList.setBounds(10, 11, 414, 166); 
		getContentPane().add(lstBankList);
		
		JButton btnOK = new JButton("Tamam");
		btnOK.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) { 
				   
				strInstallment = txtInstallment.getText(); 
				BankList.this.dispose();  
			}
		});
		btnOK.setBounds(10, 224, 414, 23);
		getContentPane().add(btnOK);
		
		JLabel lblTaksitSays = new JLabel("Taksit Say\u0131s\u0131:");
		lblTaksitSays.setBounds(10, 190, 118, 23);
		getContentPane().add(lblTaksitSays);
		
		 
		try {
			txtInstallment = new JFormattedTextField(new MaskFormatter("##"));
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return;
		}
		txtInstallment.setBounds(138, 188, 286, 25);
		getContentPane().add(txtInstallment);
		txtInstallment.setText("00");
	}
}
