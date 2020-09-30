package com.swrd.gmp;

import java.awt.Color;
import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;

import com.swrd.gmp.GmpDll.ST_Echo;

import javax.swing.JComboBox;

import java.awt.Font;

import javax.swing.ImageIcon;
import javax.swing.JTextField;
import javax.swing.JSeparator;

public class MainFrame implements ActionListener {

	private JFrame frame;
	public  JTextField txtTempPane; 
	@SuppressWarnings("rawtypes")
	public  JComboBox cmbCurrency;
	public  JLabel    lblInfo;
	public  JLabel lblIconPair;
	JButton btnK1;
	JButton btnK2;
	JButton btnK3;
	JButton btnK4;
	JButton btnK5;
	JButton btnK6;
	JButton btnK7;
	JButton btnK8;
	JButton btnKalan;
	JButton btnToplam;
	
	GmpDriver gmpDriver;
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					MainFrame window = new MainFrame();
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
	public MainFrame() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	@SuppressWarnings("rawtypes")
	private void initialize() {
		
		
		gmpDriver = new GmpDriver();
		
		try
		{ 
			gmpDriver.initDll();
		}
		catch (Error e)
		{
			JOptionPane.showMessageDialog(null,e.getMessage());			
		}
		
		//init Interface
		frame = new JFrame();
		frame.setBounds(100, 100, 870, 712);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		txtTempPane = new JTextField();
		txtTempPane.setBounds(96, 121, 648, 51);
		
		JButton btnEcho = new JButton("Echo");
		btnEcho.setBounds(561, 278, 183, 51);
		btnEcho.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				 
				try
				{
					int ret = gmpDriver.FiscalPrinter_Echo(gmpDriver.gst_echo, GmpDll.TIMEOUT_ECHO);
					ErrorClass.HandleErrorCode(ret);
					 
				}
				catch(Throwable e)
				{
					Utility.setLblTxt(lblInfo, Utility.colorNOK, "DLL HATASI");
					JOptionPane.showMessageDialog(null,e);
				} 
				
			}
		});
		
		JButton btnPair = new JButton("Eslesme Baslat");
		btnPair.setBounds(561, 338, 183, 51);
		btnPair.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) { 
				
				final JButton[] idDepartmenButtons = { btnK1, btnK2, btnK3, btnK4, btnK5, btnK6, btnK7, btnK8 };
				
				Thread t = new Thread(new Runnable() {
			        @Override
			        public void run() {
			        	Utility.setLblTxt(lblInfo, Color.BLACK, "EÞLEÞME YAPILIYOR. BEKLEYÝN.");
			            //Do the job
			        	int ret ;
			        	try
						{
			        		ret = gmpDriver.PairingTransaction (idDepartmenButtons,cmbCurrency);
			        		 
			        		ErrorClass.HandleErrorCode(ret);

			        		if(ret != 0)
			        			 lblInfo.setForeground(Utility.colorNOK);
							else
								lblIconPair.setIcon(new ImageIcon(System.getProperty("user.dir")+"\\images\\connect_established.png")); 
						}
			        	catch(Throwable e)
						{
			        		Utility.setLblTxt(lblInfo, Utility.colorNOK, "DLL HATASI");
			        		JOptionPane.showMessageDialog(null,e);
						} 
						
			        }     
			    });
			    t.start(); 
				
			}
		});
		
		JButton btn1 = new JButton("1"); 
		btn1.setBounds(209, 183, 47, 23);
		btn1.addActionListener((ActionListener) this);
		btn1.setActionCommand(btn1.getText());
		
		JButton btn2 = new JButton("2");
		btn2.setBounds(266, 183, 47, 23);
		btn2.addActionListener((ActionListener) this);
		btn2.setActionCommand(btn2.getText());
		
		JButton btn3 = new JButton("3");
		btn3.setBounds(323, 184, 47, 23);
		btn3.addActionListener((ActionListener) this);
		btn3.setActionCommand(btn3.getText());
		
		JButton btn4 = new JButton("4");
		btn4.setBounds(209, 224, 47, 23);
		btn4.addActionListener((ActionListener) this);
		btn4.setActionCommand(btn4.getText());
		
		JButton btn5 = new JButton("5");
		btn5.setBounds(266, 224, 47, 23);
		btn5.addActionListener((ActionListener) this);
		btn5.setActionCommand(btn5.getText());
		
		JButton btn6 = new JButton("6");
		btn6.setBounds(323, 224, 47, 23);
		btn6.addActionListener((ActionListener) this);
		btn6.setActionCommand(btn6.getText());
		
		JButton btn7 = new JButton("7");
		btn7.setBounds(209, 265, 47, 23);
		btn7.addActionListener((ActionListener) this);
		btn7.setActionCommand(btn7.getText());
		
		JButton btn8 = new JButton("8");
		btn8.setBounds(266, 265, 47, 23);
		btn8.addActionListener((ActionListener) this);
		btn8.setActionCommand(btn8.getText());
		
		JButton btn9 = new JButton("9");
		btn9.setBounds(323, 265, 47, 23);
		btn9.addActionListener((ActionListener) this);
		btn9.setActionCommand(btn9.getText());
		
		JButton btnx = new JButton("x");
		btnx.setBounds(209, 307, 47, 23);
		btnx.addActionListener((ActionListener) this);
		btnx.setActionCommand(btnx.getText());
		
		JButton btn0 = new JButton("0");
		btn0.setBounds(266, 307, 47, 23);
		btn0.addActionListener((ActionListener) this);
		btn0.setActionCommand(btn0.getText());
		
		JButton btnDot = new JButton(".");
		btnDot.setBounds(323, 307, 47, 23);
		btnDot.addActionListener((ActionListener) this);
		btnDot.setActionCommand(btnDot.getText());
		
		JButton btnF = new JButton("F");
		btnF.setBounds(388, 184, 47, 23);
		btnF.addActionListener((ActionListener) this);
		btnF.setActionCommand(btnF.getText());
		
		JButton btnCancel = new JButton("X");
		btnCancel.setBounds(388, 225, 47, 23);
		btnCancel.setBackground(Color.RED);
		btnCancel.setOpaque(true);
		btnCancel.addActionListener((ActionListener) this);
		btnCancel.setActionCommand(btnCancel.getText());
		
		JButton btnDelete = new JButton("<");
		btnDelete.setBounds(388, 266, 47, 23);
		btnDelete.setOpaque(true);
		btnDelete.setBackground(Color.YELLOW);
		btnDelete.addActionListener((ActionListener) this);
		btnDelete.setActionCommand(btnDelete.getText());
		
		JButton btnOK = new JButton("o");
		btnOK.setBounds(388, 308, 47, 23);
		btnOK.setOpaque(true);
		btnOK.setBackground(Color.GREEN);
		btnOK.addActionListener((ActionListener) this);
		btnOK.setActionCommand(btnOK.getText());
		
		frame.getContentPane().setLayout(null);
		frame.getContentPane().add(btnx);
		frame.getContentPane().add(btn0);
		frame.getContentPane().add(btnDot);
		frame.getContentPane().add(btn1);
		frame.getContentPane().add(btn2);
		frame.getContentPane().add(btn3);
		frame.getContentPane().add(btn4);
		frame.getContentPane().add(btn5);
		frame.getContentPane().add(btn6);
		frame.getContentPane().add(btn7);
		frame.getContentPane().add(btn8);
		frame.getContentPane().add(btn9);
		frame.getContentPane().add(btnF);
		frame.getContentPane().add(btnCancel);
		frame.getContentPane().add(btnDelete);
		frame.getContentPane().add(btnEcho);
		frame.getContentPane().add(btnPair);
		frame.getContentPane().add(btnOK);
		frame.getContentPane().add(txtTempPane);
		
		JLabel lblV = new JLabel("v1.0.0");
		lblV.setBounds(705, 58, 39, 23);
		frame.getContentPane().add(lblV);
		
		JButton btnNakit = new JButton("Nakit");
		btnNakit.setBounds(334, 355, 217, 35);
		frame.getContentPane().add(btnNakit);
		btnNakit.addActionListener((ActionListener) this);
		btnNakit.setActionCommand(btnNakit.getText());
		
		JButton btnKredi = new JButton("Kredi");
		btnKredi.setBounds(96, 355, 217, 35);
		frame.getContentPane().add(btnKredi);
		btnKredi.addActionListener((ActionListener) this);
		btnKredi.setActionCommand(btnKredi.getText());
		
		
		btnK1 = new JButton("K1");
		btnK1.setFont(new Font("Tahoma", Font.PLAIN, 9));
		btnK1.setBackground(Color.CYAN);
		btnK1.setBounds(96, 183, 103, 23);
		frame.getContentPane().add(btnK1);
		btnK1.addActionListener((ActionListener) this);
		btnK1.setActionCommand(btnK1.getText());
		
		
		btnK2 = new JButton("K2");
		btnK2.setFont(new Font("Tahoma", Font.PLAIN, 9));
		btnK2.setBackground(Color.CYAN);
		btnK2.setBounds(96, 224, 103, 23);
		frame.getContentPane().add(btnK2);
		btnK2.addActionListener((ActionListener) this);
		btnK2.setActionCommand(btnK2.getText());
		
		btnK3 = new JButton("K3");
		btnK3.setFont(new Font("Tahoma", Font.PLAIN, 9));
		btnK3.setBackground(Color.CYAN);
		btnK3.setBounds(96, 265, 103, 23);
		frame.getContentPane().add(btnK3);
		btnK3.addActionListener((ActionListener) this);
		btnK3.setActionCommand(btnK3.getText());
		
		btnK4 = new JButton("K4");
		btnK4.setFont(new Font("Tahoma", Font.PLAIN, 9));
		btnK4.setBackground(Color.CYAN);
		btnK4.setBounds(96, 307, 103, 23);
		frame.getContentPane().add(btnK4);
		btnK4.addActionListener((ActionListener) this);
		btnK4.setActionCommand(btnK4.getText());
		
		cmbCurrency = new JComboBox();//GmpDriver.ECurrency.values());
		cmbCurrency.setBounds(561, 183, 183, 20); 
		
		frame.getContentPane().add(cmbCurrency);
		
		lblInfo = new JLabel("SIMULATOR STARTED");
		lblInfo.setFont(new Font("Arial", Font.PLAIN, 15));
		lblInfo.setBounds(96, 58, 496, 23);
		frame.getContentPane().add(lblInfo);
		ErrorClass.lblError = lblInfo;
		
		lblIconPair = new JLabel("");
		lblIconPair.setIcon(new ImageIcon("C:\\Users\\scagdas\\Desktop\\eclipse_pde\\pde_workspace\\GmpSimEclipse\\images\\connect_no.png"));
		lblIconPair.setBounds(642, 47, 53, 34);
		frame.getContentPane().add(lblIconPair);
		
		btnK5 = new JButton("K5");
		btnK5.setFont(new Font("Tahoma", Font.PLAIN, 9));
		btnK5.setBackground(Color.CYAN); 
		btnK5.setBounds(445, 183, 106, 23);
		frame.getContentPane().add(btnK5);
		btnK5.addActionListener((ActionListener) this);
		btnK5.setActionCommand(btnK5.getText());
		
		btnK6 = new JButton("K6");
		btnK6.setFont(new Font("Tahoma", Font.PLAIN, 9));
		btnK6.setBackground(Color.CYAN); 
		btnK6.setBounds(445, 224, 106, 23);
		frame.getContentPane().add(btnK6);
		btnK6.addActionListener((ActionListener) this);
		btnK6.setActionCommand(btnK6.getText());
		
		btnK7 = new JButton("K7");
		btnK7.setFont(new Font("Tahoma", Font.PLAIN, 9));
		btnK7.setBackground(Color.CYAN); 
		btnK7.setBounds(445, 265, 106, 23);
		frame.getContentPane().add(btnK7);
		btnK7.addActionListener((ActionListener) this);
		btnK7.setActionCommand(btnK7.getText());
		
		btnK8 = new JButton("K8");
		btnK8.setFont(new Font("Tahoma", Font.PLAIN, 9));
		btnK8.setBackground(Color.CYAN); 
		btnK8.setBounds(445, 307, 106, 23);
		frame.getContentPane().add(btnK8);
		btnK8.addActionListener((ActionListener) this);
		btnK8.setActionCommand(btnK8.getText());
		
		JButton btnUrunIptal = new JButton("Urun Iptal");
		btnUrunIptal.setActionCommand("Kredi");
		btnUrunIptal.setBounds(96, 447, 150, 35);
		frame.getContentPane().add(btnUrunIptal);
		btnUrunIptal.addActionListener((ActionListener) this);
		btnUrunIptal.setActionCommand(btnUrunIptal.getText());
		
		JButton btnOdemeIptal = new JButton("Odeme Iptal");
		btnOdemeIptal.setActionCommand("Kredi");
		btnOdemeIptal.setBounds(256, 447, 150, 35);
		frame.getContentPane().add(btnOdemeIptal);
		btnOdemeIptal.addActionListener((ActionListener) this);
		btnOdemeIptal.setActionCommand(btnOdemeIptal.getText());
		
		JButton btnFisIptal = new JButton("Fis Iptal");
		btnFisIptal.setActionCommand("Kredi");
		btnFisIptal.setBounds(421, 447, 150, 35);
		frame.getContentPane().add(btnFisIptal);
		btnFisIptal.addActionListener((ActionListener) this);
		btnFisIptal.setActionCommand(btnFisIptal.getText());
		
		JButton btnIndirim = new JButton("Indirim");
		btnIndirim.setActionCommand("Kredi");
		btnIndirim.setBounds(594, 447, 150, 35);
		frame.getContentPane().add(btnIndirim);
		btnIndirim.addActionListener((ActionListener) this);
		btnIndirim.setActionCommand(btnIndirim.getText());
		
		JButton btnAkislar = new JButton("Akislar");
		btnAkislar.setActionCommand("Kredi");
		btnAkislar.setBounds(96, 493, 150, 35);
		frame.getContentPane().add(btnAkislar);
		btnAkislar.addActionListener((ActionListener) this);
		btnAkislar.setActionCommand(btnAkislar.getText());
		
		JButton btnKullaniciMsg = new JButton("Kullanici Mesaj");
		btnKullaniciMsg.setActionCommand("Kullanici Mesaj");
		btnKullaniciMsg.setBounds(256, 493, 150, 35);
		frame.getContentPane().add(btnKullaniciMsg);
		btnKullaniciMsg.addActionListener((ActionListener) this);
		btnKullaniciMsg.setActionCommand(btnKullaniciMsg.getText());
		
		JButton btnFonksiyonlar = new JButton("Fonksiyonlar");
		btnFonksiyonlar.setActionCommand("Kredi");
		btnFonksiyonlar.setBounds(421, 493, 150, 35);
		frame.getContentPane().add(btnFonksiyonlar);
		btnFonksiyonlar.addActionListener((ActionListener) this);
		btnFonksiyonlar.setActionCommand(btnFonksiyonlar.getText());
		
		JButton btnRfu_4 = new JButton("RFU5");
		btnRfu_4.setActionCommand("Kredi");
		btnRfu_4.setBounds(594, 493, 150, 35);
		frame.getContentPane().add(btnRfu_4);
		btnRfu_4.addActionListener((ActionListener) this);
		btnRfu_4.setActionCommand(btnRfu_4.getText());
		
		btnKalan = new JButton("Kalan = 0");
		btnKalan.setBackground(Color.WHITE);
		btnKalan.setBounds(416, 92, 328, 23);
		frame.getContentPane().add(btnKalan);
		btnKalan.addActionListener((ActionListener) this);
		btnKalan.setActionCommand(btnKalan.getText());
		
		btnToplam = new JButton("Toplam = 0");
		btnToplam.setBackground(Color.WHITE);
		btnToplam.setBounds(96, 92, 317, 23);
		frame.getContentPane().add(btnToplam);
		
		JSeparator separator = new JSeparator();
		separator.setBounds(96, 421, 648, 2);
		frame.getContentPane().add(separator);
				 
		ButtonGroup btngrp = new ButtonGroup();
	}
	
	public void actionPerformed(ActionEvent evt) 
	{
		String evtCmd = evt.getActionCommand();
		String txtPaneStr = txtTempPane.getText();
		
		if(Utility.isNumeric(evtCmd))
		{
			
			txtTempPane.setText(txtPaneStr + evtCmd);
			txtTempPane.requestFocus();
		}
		else if(evtCmd.equals("<"))
		{
			if(txtPaneStr.length() != 0)
				txtTempPane.setText(txtPaneStr.substring(0, txtPaneStr.length()-1));
		}
		else if(evtCmd.equals("X"))
		{
			txtTempPane.setText("");
		}
		else if (evtCmd.equals("K1"))
		{
			gmpDriver.DepartmentSale (1, txtTempPane.getText(), cmbCurrency);
			txtTempPane.setText("");
		}
		else if (evtCmd.equals("K2"))
		{ 
			gmpDriver.DepartmentSale (2, txtTempPane.getText(), cmbCurrency);
			txtTempPane.setText("");
		}
		else if (evtCmd.equals("K3"))
		{ 
			gmpDriver.DepartmentSale (3, txtTempPane.getText(), cmbCurrency);
			txtTempPane.setText("");
		}
		else if (evtCmd.equals("K4"))
		{
			gmpDriver.DepartmentSale (4, txtTempPane.getText(), cmbCurrency);
			txtTempPane.setText("");
		}
		else if (evtCmd.equals("K5"))
		{
			gmpDriver.DepartmentSale (5, txtTempPane.getText(), cmbCurrency);
			txtTempPane.setText("");
		}
		else if (evtCmd.equals("K6"))
		{ 
			gmpDriver.DepartmentSale (6, txtTempPane.getText(), cmbCurrency);
			txtTempPane.setText("");
		}
		else if (evtCmd.equals("K7"))
		{ 
			gmpDriver.DepartmentSale (7, txtTempPane.getText(), cmbCurrency);
			txtTempPane.setText("");
		}
		else if (evtCmd.equals("K8"))
		{
			gmpDriver.DepartmentSale (8, txtTempPane.getText(), cmbCurrency);
			txtTempPane.setText("");
		}
		else if (evtCmd.equals("Nakit"))
		{ 
			int amount 						= 0;
			
			try
			{		
				amount = Integer.parseInt(txtPaneStr);
			}
			catch(Throwable t)
			{
				
			}
			short currencyOfPayment 	= Short.valueOf(((String)cmbCurrency.getSelectedItem()).substring(0, 3));
 
			ErrorClass.HandleErrorCode(gmpDriver.cashPaymentTrans(amount, currencyOfPayment));
				 
			 
		}
		else if (evtCmd.equals("Kredi"))
		{
			try { 
				
				int ret = gmpDriver.creditPaymnet(cmbCurrency,txtTempPane.getText());
				ErrorClass.HandleErrorCode(ret); 
			} catch (Exception e) {
				e.printStackTrace();
			} 
		}
		else if(evtCmd.equals("Kalan = 0"))
		{
			txtTempPane.setText(Long.toString(gmpDriver.remainingAmount));		
		}
		else if(evtCmd.equals("Urun Iptal"))
		{
			int ret = gmpDriver.itemVoid(txtTempPane.getText());
			ErrorClass.HandleErrorCode(ret);
		}
		else if(evtCmd.equals("Odeme Iptal"))
		{
			int ret = gmpDriver.paymentVoid(txtTempPane.getText());
			ErrorClass.HandleErrorCode(ret);
		}
		else if(evtCmd.equals("Fis Iptal"))
		{
			gmpDriver.OnBnClickedButtonVoidAll();
		}
		else if(evtCmd.equals("Indirim"))
		{
			Discount disc = new Discount(gmpDriver);
        	int selectedBankInd = disc.start();			
		}
		else if(evtCmd.equals("Akislar"))
		{
			Flow akislar = new Flow(gmpDriver);
			akislar.start();
        	ErrorClass.lblError = lblInfo;
		}
		else if(evtCmd.equals("Kullanici Mesaj"))
		{
			UserMessage um = new UserMessage(gmpDriver);
        	um.start();
        	ErrorClass.lblError = lblInfo;
		}
		else if(evtCmd.equals("Fonksiyonlar"))
		{
			Functions func = new Functions(gmpDriver);
			func.start();
        	ErrorClass.lblError = lblInfo;
		}
		else if(evtCmd.equals("RFU5"))
		{
			
			
		}
		
		gmpDriver.remainingAmount = gmpDriver.gstTicket.TotalReceiptAmount - gmpDriver.gstTicket.TotalReceiptPayment;
		
		if(gmpDriver.remainingAmount != 0)
			btnToplam.setText("Toplam: "+ Long.toString(gmpDriver.gstTicket.TotalReceiptAmount)+ " TL");
		else
			btnToplam.setText("Toplam: "+ Integer.toString(0)+ " TL");
		btnKalan.setText("Kalan: " + Long.toString(gmpDriver.remainingAmount)+ " TL");
		 
	}
}
